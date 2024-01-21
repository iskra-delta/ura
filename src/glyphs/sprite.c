#include <stdint.h>
#include <stdbool.h>

#include <ugpx.h>

#include <glyphs/sprite.h>

void gputsprite(uint8_t *sprite, coord x, coord y, color c) {
    /* get sprite coordinates */
    uint8_t w=sprite[1], h=sprite[2];
    int datandx=4;  /* data starts at 4 */
    uint8_t row=0;
    int pcount;
    while (row<h) {
        gxy(x,y+row);   /* goto x,y */
        pcount=0;
        bool black=false;
        while(pcount < w) {
            if (sprite[datandx]!=0xff)
            {
                if (black) {
                    gsetcolor(c);
                    gdrawd(sprite[datandx],0);
                }
                else {
                    gsetcolor(CO_NONE);
                    gdrawd(sprite[datandx],0);
                }
                pcount += (sprite[datandx]);
            } 
            black = !black;
            datandx++;
        }
        row++;
    }
    /* restore color */
    gsetcolor(c);
}

dim_t* gmesprite(uint8_t *sprite, dim_t* m) {
    m->w=sprite[1]; 
    m->h=sprite[2];
    return m;
}