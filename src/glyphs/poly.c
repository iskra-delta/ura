#include "poly.h"

/* line states */
#define BR_ST_INIT          ((uint8_t)0)
#define BR_ST_FIRST_PX      ((uint8_t)1)
#define BR_ST_CURRENT_PX    ((uint8_t)2)
#define BR_ST_LAST_PX       ((uint8_t)3)

typedef struct _bresenham_s {
    int x0, y0, x1, y1;     /* coordinates */
    int8_t sx, sy;          /* step direction, can be -1 or 1 */
    int dx, dy;             /* delta x and y, need to be int */
    int err;                /* current error, can be negative */
    uint8_t state;          /* line state */
} _bresenham_t;

static _bresenham_t* _bresenham_init(
    coord x0, coord y0, coord x1, coord y1
) {
    _bresenham_t *br_data = malloc(sizeof(_bresenham_t));
    br_data->x0 = x0;
    br_data->y0 = y0;
    br_data->x1 = x1;
    br_data->y1 = y1;

    br_data->dx = abs(x1 - x0);
    br_data->dy = abs(y1 - y0);
    br_data->sx = x0 < x1 ? 1 : -1;
    br_data->sy = y0 < y1 ? 1 : -1;
    br_data->err = (br_data->dx > br_data->dy ? 
        br_data->dx : -br_data->dy) / 2;
    
    br_data->state=BR_ST_INIT;

    return br_data;
}

static bool _bresenham_next(
    _bresenham_t *br_data,
    int scany,
    horz_line_t *hline) {

    coord tmp;

    /* no intersection with the scanline */
    if (scany < br_data->y0 || scany > br_data->y1)
        return false;

    /* remember y and starting position */
    hline->y=br_data->y0, hline->x0=hline->x1=br_data->x0;
    int e2;

    while (br_data->y0 == hline->y) {  /* loop until y changes or end */
        /* are we at the last point? */
        if (br_data->x0 == br_data->x1 
            && br_data->y0 == br_data->y1) {
            if (br_data->sx > 0) { /* if sx < 0 it's the first point*/
                tmp=hline->x1;
                hline->x1=hline->x0;
                hline->x0=tmp;
            }
            br_data->state=BR_ST_LAST_PX;  /* end of line */
            goto br_exit;
        }

        e2 = br_data->err;
        if (e2 < br_data->dy) {
            br_data->err += br_data->dx;
            br_data->y0 += br_data->sy;
        }
        if (e2 > -br_data->dx) {
            br_data->err -= br_data->dy;
            br_data->x0 += br_data->sx;
            if (br_data->y0 == hline->y)
                hline->x1=br_data->x0;
        }
    }

    if (br_data->sx > 0) { /* if sx < 0 it's the first point*/
        tmp=hline->x1;
        hline->x1=hline->x0;
        hline->x0=tmp; 
    }

    /* it's not over yet... */
    if (br_data->state==BR_ST_INIT)
        br_data->state=BR_ST_FIRST_PX;
    else
        br_data->state=BR_ST_CURRENT_PX;
    
br_exit:
    return true;
}


/* allocation table is a table of this type */
#define ATBL_TYPE   int8_t
#define ATBL_MAXLEN 127

/* we are using allocation table to sort points,
   each member of the atbl points to the next member
   and the index of allocation table is the index in the
   poligon points structure, the function returns first index
   into the table */
static ATBL_TYPE _atbl_insert(
    ATBL_TYPE* atbl,    /* allocation table */
    ATBL_TYPE first,    /* index of first member */ 
    ATBL_TYPE i,        /* index of point we are inserting */           
    void* pts,       /* points */
    /* sortkey function to return member of point structure */
    coord(*sortkey)(void*, ATBL_TYPE index) 
) {
    if (first == -1)  { atbl[0] = -1; return 0; } /* empty list */
    else if (sortkey(pts,first) > sortkey(pts,i)) { 
        /* we have a new first! */
        atbl[i] = first; 
        return i; 
    } 
    else { /* find a place to insert */
        ATBL_TYPE ii = first;
        while (atbl[ii] >= 0 && sortkey(pts,i) > sortkey(pts,ii)) 
            ii = atbl[ii];
        atbl[i] = atbl[ii]; atbl[ii] = i;
        return first;
    }
}

/* sortkey function to return x of first point of the line 
  (sort lines by x) */
static coord _edge_x(void *edge, ATBL_TYPE i) {
    return ((_bresenham_t **)edge)[i]->x0;
}

/* sortkey function to return y (i.e. sort by y) */
static coord _pt_y(void *pts, ATBL_TYPE i) {
    return ((point_t *)pts)[i].y;
}

static int8_t _atbl_delete(
    ATBL_TYPE* atbl,    /* allocation table */
    ATBL_TYPE first,    /* index of first member */ 
    ATBL_TYPE i,        /* index of current point */ 
    ATBL_TYPE prev,     /* index of first member */ 
    ATBL_TYPE next      /* index of current point */ 
) {
    if (i == first) return next; /* remove from start? */
    else { atbl[prev] = next; atbl[i] = -1; }
    return first;
}

/* max. number of points in polygon */
void gpx_fill_polygon(point_t *pts, int n, color c) {

    if (n < 3)
        return; /* no polygon */

    /* first sort points by y and extract largest y */
    ATBL_TYPE i;
    coord ymax = 0;
    ATBL_TYPE* iysort = malloc(ATBL_MAXLEN*sizeof(ATBL_TYPE));
    ATBL_TYPE iyfirst=-1;
    for (i = 0; i < n; i++)
    {
        if (pts[i].y > ymax) ymax = pts[i].y;
        iyfirst = _atbl_insert(iysort, iyfirst, i, pts, _pt_y);
    }

    /* now x sort table */
    ATBL_TYPE* ixsort = malloc(ATBL_MAXLEN*sizeof(ATBL_TYPE));
    ATBL_TYPE ixfirst=-1;

    /* and generate pointers to bresenham lines */
    _bresenham_t** edges=malloc(ATBL_MAXLEN*sizeof(_bresenham_t*));
    ATBL_TYPE edges_count=0;

    /*  generate all polygon lines, each point should generate 
        2 lines with 2nd point bellow our point minus the lines on 
        the same level! 
        and sort them by x!*/
    i = iyfirst;
    while (i >= 0)
    {
        /* line left of top pixel? */
        point_t *pleft = &(pts[i == 0 ? n - 1 : i - 1]);
        if (pts[i].y < pleft->y)
        {
            /* first add to collection */
            edges[edges_count] = _bresenham_init(
                pts[i].x, pts[i].y, pleft->x, pleft->y);
            ixfirst = _atbl_insert(ixsort, ixfirst, edges_count, edges, _edge_x);
            /* proceed to the next edge */
            edges_count++;
        }

        /* line right of top pixel */
        point_t *pright = &(pts[(i + 1) % n]);
        if (pts[i].y <= pright->y)
        {
            edges[edges_count] = _bresenham_init(pts[i].x, pts[i].y, 
                pright->x, pright->y);
            /* now sort by index table */
            ixfirst = _atbl_insert(ixsort, ixfirst, edges_count, edges, _edge_x);
            /* proceed to the next edge */
            edges_count++;
        }
        /* remember max */
        i = iysort[i];
    }

    /* start scan line algorithm from top point */
    int y = pts[iyfirst].y;
    _bresenham_t* ae[2]; /* active edges */
    horz_line_t ehl[2];
    int8_t aelast;

    do {
        /* first edge */
        ATBL_TYPE ixedge = ixfirst;
        /* index */
        aelast=0;

        while(ixedge >= 0) {

            /* get current edge */
            _bresenham_t* e= edges[ixedge];

            /* if active edge, add to edges */
            if (_bresenham_next(e,y,&(ehl[aelast]))) 
                ae[aelast++]=e;

            /* do we have two edges? */
            if (aelast==2) {

                /* and draw a line */
                gsetcolor(c);
                gdrawline(
                    ehl[0].x0, y, 
                    ehl[1].x0, y
                );

                /* special case if maximum or minimum,
                   count it twice */
                if (ae[0]->state!=ae[1]->state
                    && (
                        ehl[0].x0==ehl[1].x0
                        || ehl[0].x1==ehl[1].x1
                        || ehl[0].x0==ehl[1].x1
                        || ehl[0].x1==ehl[1].x0
                    )
                ) {
                    ae[0]=ae[1];
                    ehl[0]=ehl[1];
                    aelast=1;
                }
                else
                    aelast=0;
            }

            /* next edge */
            ixedge = ixsort[ixedge];
        }

        /* move to the next scanline */
        y++;
    } while (y <= ymax);


    /* release allocated memory for both index tables... */
    free(ixsort);
    free(iysort);
    /* ...and all bresenham lines */
    for(i=0;i<edges_count;i++) free(edges[i]);
    free(edges);
}


void gpx_draw_polygon(
    point_t pts[], int n,
    color c)
{
    if (n < 2)
        return; /* no polygon */
    /* draw lines */
    for (int i = 1; i < n; i++)
    {
        gdrawline(pts[i - 1].x, pts[i - 1].y,
                      pts[i].x, pts[i].y);
    }
    /* last point back to first point */
    gdrawline(pts[n - 1].x, pts[n - 1].y,
                  pts[0].x, pts[0].y);
}