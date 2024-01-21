#include <stdio.h>
#include <stdbool.h>

#include <sys/bdos.h>

#include <ugpx.h>

#include <glyphs/glyphs.h>
#include <glyphs/sprite.h>

#include <clock/bcd.h>
#include <clock/screen.h>
#include <clock/clock.h>

static clock_t clk;

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

/* partner RT clock ports */
__sfr __at 0xA2 SECOND;
__sfr __at 0xA3 MINUTE;
__sfr __at 0xA4 HOUR;
void clock_loop() {

    while(!bdos(C_RAWIO,0xff)) {

        int minute=6 * bcd2bin(MINUTE);
        int hour=30 * bcd2bin(HOUR) + bcd2bin(MINUTE) / 2;

        scr_draw_pointer(hour, 140, 20, 20, 4, 12);
        scr_draw_pointer(minute, 160, 20, 50, 4, 10);
    }

}
