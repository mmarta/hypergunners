#ifndef HG_ALIEN_H
#define HG_ALIEN_H

#include "defines.h"
#include "gfx.h"
#include "bullet.h"
#include "player.h"

#define ALIEN_COUNT 6

typedef enum {
    DIVER
} AlienType;

typedef struct {
    u8 active, animTime, spriteIndex, score, time, yTarget, distance;
    char dirPos;
    AlienType type;
} Alien;

extern Alien aliens[];

void AlienInitAll();
void AlienActivate(AlienType, u8);
void AlienFire(Alien *);
void AlienUpdate(Alien *);
void AlienDeactivate(Alien *);

#endif
