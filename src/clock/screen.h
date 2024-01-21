#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdlib.h>

#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   512

#define SCREEN_CENTER_X (SCREEN_WIDTH/2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT/2)

#define RAD (2 * 3.141592f)

extern void scr_clear();
extern void scr_draw_num(int gpynum, int radius);

#endif /* __SCREEN_H__ */