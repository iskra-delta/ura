#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdlib.h>

#include <ugpx.h>

#define RADIUS 200

/* game context (state) */
#define HAND_PTS 6
typedef struct clock_s {
    point_t hhand[HAND_PTS];
    point_t mhand[HAND_PTS];
    point_t prevhhand[HAND_PTS];
    point_t prevmhand[HAND_PTS];
    uint8_t page;                       /* current page */
} clock_t;

extern void clock_init();
extern void clock_exit();
extern void clock_loop();

#endif /* __CLOCK_H__ */