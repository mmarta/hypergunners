#ifndef HG_COLLISION_H
#define HG_COLLISION_H

#include "defines.h"
#include "gfx.h"
#include "bullet.h"
#include "alien.h"

u8 SpriteCollision(struct SpriteStruct *, struct SpriteStruct *);
void ProcessAlienBulletCollisions();

#endif