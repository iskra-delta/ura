#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <stdint.h>

#include <ugpx.h>

/* draw sprite */
extern void gputsprite(uint8_t *sprite, coord x, coord y, color c);

/* measure sprite */
extern dim_t* gmesprite(uint8_t *sprite, dim_t* m);

#endif /* __SPRITE_H__ */