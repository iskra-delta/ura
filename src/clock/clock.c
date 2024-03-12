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
    gsetpage(PG_WRITE,1);
    /* numbers and iskra logo */
    for (int i=1;i<=12;i++)
        scr_draw_num(i,RADIUS);
    scr_draw_logo();
    gsetpage(PG_DISPLAY,1);
    gsetpage(PG_WRITE,0);
    /* numbers and iskra logo */
    for (int i=1;i<=12;i++)
        scr_draw_num(i,RADIUS);
    scr_draw_logo();
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

    clk.page=0;
    bool has_prev_state=false;
    int minute, hour, prevminute=0, prevhour=0;

    /* until key press */
    while(1) {

        /* get hour and minut and calculate hour hands */
        minute=6 * bcd2bin(MINUTE);
        hour=30 * bcd2bin(HOUR) + bcd2bin(MINUTE) / 2;
        
        /* only draw if changed */
        if (has_prev_state
            && prevminute==minute
            && prevhour==hour)
            goto enddraw;

        scr_calc_hands(hour, 140, 20, 20, 4, 12, clk.hhand);
        scr_calc_hands(minute, 160, 20, 50, 4, 10, clk.mhand);

        /* draw to write page:
           first redraw number and logo then hands */
        scr_draw_num((minute+15)/30,RADIUS);
        if (minute>90 && minute<150)
            scr_draw_logo();
        gpx_fill_polygon(clk.hhand, HAND_PTS, CO_FORE);
        gpx_fill_polygon(clk.mhand, HAND_PTS, CO_FORE);

        /* switch pages */
        gsetpage(PG_DISPLAY,clk.page);
        clk.page = clk.page ? 0 : 1;
        gsetpage(PG_WRITE,clk.page);

        /* delete previous clock hands */
        if (has_prev_state) {
            /* setting color to CO_BACK will delete everything
               drawn previously. */
            gsetcolor(CO_BACK);
            /* and erase using previous coordinates */
            gpx_fill_polygon(clk.prevhhand, HAND_PTS, CO_BACK);
            gpx_fill_polygon(clk.prevmhand, HAND_PTS, CO_BACK);
        } else 
            has_prev_state=true;

        /* store prev coordinates */
        for(int i=0;i<HAND_PTS;i++) {
            clk.prevhhand[i]=clk.hhand[i];
            clk.prevmhand[i]=clk.mhand[i];
        }
        prevminute=minute;
        prevhour=hour;

        /* keypress aborts */
enddraw:
        if (bdos(C_RAWIO,0xff)) break;
    }

    /* and exit */
    scr_clear();
}