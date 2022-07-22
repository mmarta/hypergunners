#ifndef HG_BULLET_H
#define HG_BULLET_H

#include "defines.h"
#include "gfx.h"

typedef struct {
    u8 active, spriteIndex, playerIndex, depthIndex, reverse;
    PlayerColor color;
} PlayerBullet;

void PlayerBulletInit(PlayerBullet *, u8);
void PlayerBulletActivate(PlayerBullet *, u8, u8, PlayerColor);
void PlayerBulletReverse(PlayerBullet *);
void PlayerBulletUpdate(PlayerBullet *);
void PlayerBulletDeactivate(PlayerBullet *);

#endif
