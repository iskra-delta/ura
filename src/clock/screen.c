#include <stdlib.h>
#include <io.h>

#include <ugpx.h>

#include <glyphs/glyphs.h>
#include <glyphs/sprite.h>
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
    int angle=30 * gpynum;
    float x=fastsin(angle)*radius;
    float y=-fastcos(angle)*radius;   

    gputsprite(
        glyphs[gpynum-1], 
        SCREEN_CENTER_X+x, 
        SCREEN_CENTER_Y+y, 
        CO_FORE);
}