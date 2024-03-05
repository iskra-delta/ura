#include <stdlib.h>
#include <io.h>

#include <ugpx.h>

#include <glyphs/glyphs.h>
#include <glyphs/sprite.h>
#include <glyphs/poly.h>
#include <clock/screen.h>
#include <clock/trig.h>

void scr_clear() {
    gsetpage(PG_DISPLAY,1);
    gcls();
    gsetpage(PG_DISPLAY,0);
    gcls();
}

static uint8_t* glyphs[]={ 
    &g01, &g02, &g03, &g04, &g05, &g06,
    &g07, &g08, &g09, &g10, &g11, &g12
};
void scr_draw_num(int gpynum, int radius) {
    
    /* calculate sprite center position */
    int angle=30 * gpynum;
    float x=fastsin(angle)*radius;
    float y=-fastcos(angle)*radius;   

    /* measure sprite */
    dim_t sdim;
    gmesprite(glyphs[gpynum-1],&sdim);

    /* and draw it */
    gputsprite(
        glyphs[gpynum-1], 
        SCREEN_CENTER_X + x - sdim.w/2, 
        SCREEN_CENTER_Y + y - sdim.h/2, 
        CO_FORE);
}

void scr_draw_logo() {
    /* and draw it */
    gputsprite(
        &iskra, 
        586, 
        270, 
        CO_FORE);
}

static point_t* _rotate(int angle, point_t* point) {
    
    /* cache */
    float s=fastsin(angle);
    float c=fastcos(angle);

    float newx = point->x * c - point->y * s;
    float newy = point->x * s + point->y * c;

    point->x = newx;
    point->y = newy;

    return point;
}

void scr_draw_pointer(
    int angle,
    int r,
    int d1, int d2, int h1, int h2) {

    /* define points */
    point_t pts[]= {
        {-h1,d1},
        {-h1,-r-d2},
        {0,-r-d2},
        {0,-r},
        {h2,-r},
        {h2,d1}
    };

    /* iterate points*/
    for(int i=0;i<sizeof(pts)/sizeof(point_t);i++) {
        /* rotate next */
        _rotate(angle,&(pts[i]));
        pts[i].x=pts[i].x+SCREEN_CENTER_X;
        pts[i].y=pts[i].y+SCREEN_CENTER_Y;    
    }

    /* draw polygon */
    gpx_fill_polygon(pts, sizeof(pts)/sizeof(point_t), CO_FORE); 
}