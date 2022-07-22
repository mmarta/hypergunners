#ifndef HG_GFX_H
#define HG_GFX_H

#include "defines.h"

#define SPRITE_SIZE 8

#define CENTER_SPRITE_Y 108

#define MID_POINT_X 100
#define FAR_POINT_X 150
#define END_POINT_X 180

typedef enum {
    WHITE_RED,
    BLACK_BLUE
} PlayerColor;

extern const char gfxTiles[];
extern const char gfxSpriteTiles[];

extern u8 spriteIndexCount;

/**
 * NOTE:
 * We cannot organize these maps the way we would like, where we can index them in arrays/pointers of arrays.
 * There seems to be a problem with addressing them if there are too many of them with the AVR C compiler.
 * Therefore, we have to keep the maps as individual single-dimesion arrays.
 */

extern const char mapBlank[];

extern const char mapLeftWhitePlayerStatic[];
extern const char mapLeftWhitePlayerA[];
extern const char mapLeftWhitePlayerB[];
extern const char mapLeftWhitePlayerC[];
extern const char mapLeftBlackPlayerStatic[];
extern const char mapLeftBlackPlayerA[];
extern const char mapLeftBlackPlayerB[];
extern const char mapLeftBlackPlayerC[];

extern const char mapRightWhitePlayerStatic[];
extern const char mapRightWhitePlayerA[];
extern const char mapRightWhitePlayerB[];
extern const char mapRightWhitePlayerC[];
extern const char mapRightBlackPlayerStatic[];
extern const char mapRightBlackPlayerA[];
extern const char mapRightBlackPlayerB[];
extern const char mapRightBlackPlayerC[];

extern const char mapPlayerKillA[];
extern const char mapPlayerKillB[];
extern const char mapPlayerKillC[];
extern const char mapPlayerKillD[];

extern const char mapRedPlayerBulletA[];
extern const char mapRedPlayerBulletB[];
extern const char mapRedPlayerBulletC[];
extern const char mapBluePlayerBulletA[];
extern const char mapBluePlayerBulletB[];
extern const char mapBluePlayerBulletC[];
extern const char mapReverseBulletA[];
extern const char mapReverseBulletB[];
extern const char mapReverseBulletC[];

extern const char mapAlienDiverNear[];
extern const char mapAlienDiverMid[];
extern const char mapAlienDiverFar[];
extern const char mapAlienDiverFarLeftA[];
extern const char mapAlienDiverFarLeftB[];
extern const char mapAlienDiverFarRightA[];
extern const char mapAlienDiverFarRightB[];

extern const char mapAlienDiverWhiteRedNear[];
extern const char mapAlienDiverWhiteRedMid[];
extern const char mapAlienDiverWhiteRedFar[];
extern const char mapAlienDiverWhiteRedFarLeftA[];
extern const char mapAlienDiverWhiteRedFarLeftB[];
extern const char mapAlienDiverWhiteRedFarRightA[];
extern const char mapAlienDiverWhiteRedFarRightB[];

extern const char mapAlienDiverBlackBlueNear[];
extern const char mapAlienDiverBlackBlueMid[];
extern const char mapAlienDiverBlackBlueFar[];
extern const char mapAlienDiverBlackBlueFarLeftA[];
extern const char mapAlienDiverBlackBlueFarLeftB[];
extern const char mapAlienDiverBlackBlueFarRightA[];
extern const char mapAlienDiverBlackBlueFarRightB[];

extern const char mapAlienKillNearA[];
extern const char mapAlienKillNearB[];
extern const char mapAlienKillNearC[];
extern const char mapAlienKillMidA[];
extern const char mapAlienKillMidB[];
extern const char mapAlienKillMidC[];
extern const char mapAlienKillFarA[];
extern const char mapAlienKillFarB[];
extern const char mapAlienKillFarC[];

u8 NextSpriteIndex();

void PrintVerticalPROGMEM(u8, u8, const char *);
void PrintVerticalRAM(u8, u8, const char *);
void PrintVerticalChar(u8, u8, char);
void PrintU8Vertical(u8, u8, u8);
void PrintU16Vertical(u8, u8, u16, u16, u8);

#endif
