#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdlib.h>

#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   512

#define SCREEN_CENTER_X (SCREEN_WIDTH/2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT/2)

#define RAD (2 * 3.141592f)

typedef struct point_s {
    coord x;
    coord y;
} point_t;

extern void scr_clear();
extern void scr_draw_num(int gpynum, int radius);
extern void scr_draw_pointer(
    int angle,
    int radius,
    int d1, int d2, int h1, int h2);

#endif /* __SCREEN_H__ */