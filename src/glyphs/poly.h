#ifndef __POLY_H__
#define __POLY_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <ugpx.h>

typedef struct point_s {
    coord x;
    coord y;
} point_t;

typedef struct horz_line_s {
    coord x0;
    coord x1;
    coord y;
} horz_line_t;

extern void gpx_fill_polygon(
    point_t *pts, int n,
    color c);

extern void gpx_draw_polygon(
    point_t pts[], int n,
    color c);

#endif /* __POLY_H__ */