#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <stdlib.h>

#include <ugpx.h>

/* game context (state) */
typedef struct clock_s {
    /* origin point */
    coord ox;                           
    coord oy;    
    /* previous origin point */
    coord prevox;
    coord prevoy;
    
    uint8_t page;                       /* current page */
} clock_t;

extern void clock_init();
extern void clock_exit();
extern void clock_loop();

#endif /* __CLOCK_H__ */