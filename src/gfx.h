#ifndef HG_GFX_H
#define HG_GFX_H

#include "defines.h"

#define SPRITE_SIZE 8

#define CENTER_SPRITE_Y 108

#define MID_POINT_X 100
#define FAR_POINT_X 150
#define END_POINT_X 180

extern const char gfxTiles[];
extern const char gfxSpriteTiles[];

extern u8 spriteIndexCount;

extern const char *mapLeftPlayer[];
extern const char *mapRightPlayer[];
extern const char *mapLeftPlayerBullet[];
extern const char *mapRightPlayerBullet[];

extern const char mapAlienDiverNear[];
extern const char mapAlienDiverMid[];
extern const char mapAlienDiverFar[];
extern const char mapAlienDiverFarLeftA[];
extern const char mapAlienDiverFarLeftB[];
extern const char mapAlienDiverFarRightA[];
extern const char mapAlienDiverFarRightB[];
extern const char *mapAlienKillA[];
extern const char *mapAlienKillB[];
extern const char *mapAlienKillC[];

u8 NextSpriteIndex();

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintVerticalChar(u8, u8, char);
void PrintU8Vertical(u8, u8, u8);
void PrintU16Vertical(u8, u8, u16, u16, u8);

#endif
