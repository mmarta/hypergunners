#ifndef HG_PLAYER_H
#define HG_PLAYER_H

#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "bullet.h"

#define PLAYER_COUNT 2
#define PLAYER_BULLET_COUNT 2

typedef struct {
    u8 index, active, animTime, updateScore, spriteIndex, fireButton, colorButton;
    u16 score;
    PlayerBullet bullets[PLAYER_BULLET_COUNT];
    PlayerColor color;
} Player;

extern Player players[];

void PlayerInitAll();
void PlayerStart(Player *);
void PlayerInput(Player *);
void PlayerAddScore(Player *, u8);
void PlayerUpdateBG(Player *);
void PlayerUpdate(Player *);

#endif
