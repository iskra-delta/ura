#include <stdio.h>
#include <stdbool.h>

#include <ugpx.h>

#include <glyphs/glyphs.h>
#include <glyphs/sprite.h>

#include <clock/screen.h>
#include <clock/clock.h>

static clock_t g;

void clock_init() {
    /* init graphics */
    ginit(RES_1024x512);
    /* clear screen */
    scr_clear();
    /* now draw all the sprites */
    for (int i=1;i<=12;i++)
        scr_draw_num(i,200);
    
}

void clock_exit() {
    /* clear screen */
    //scr_clear();
    /* exit */
    gexit();
}

void clock_loop() {

}