#ifndef HG_BULLET_H
#define HG_BULLET_H

#include "defines.h"
#include "gfx.h"

typedef struct {
    u8 active, spriteIndex, playerIndex, depthIndex;
} PlayerBullet;

void PlayerBulletInit(PlayerBullet *, u8);
void PlayerBulletActivate(PlayerBullet *, u8, u8);
void PlayerBulletUpdate(PlayerBullet *);
void PlayerBulletDeactivate(PlayerBullet *);

#endif
