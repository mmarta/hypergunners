#include "collision.h"

u8 SpriteCollision(struct SpriteStruct *spriteA, struct SpriteStruct *spriteB) {
    if(
        spriteA->x < SPRITE_SIZE + spriteB->x && spriteB->x < SPRITE_SIZE + spriteA->x
        && spriteA->y < SPRITE_SIZE + spriteB->y && spriteB->y < SPRITE_SIZE + spriteA->y
    ) {
        return 1;
    }

    return 0;
}

void ProcessAlienBulletCollisions() {
    u8 i = ALIEN_COUNT, j, k;
    while(i--) {
        j = PLAYER_COUNT;
        while(j--) {
            k = PLAYER_BULLET_COUNT;
            while(k--) {
                if(
                    players[j].bullets[k].active
                    && AlienIsCollidable(&aliens[i])
                    && SpriteCollision(&sprites[aliens[i].spriteIndex], &sprites[players[j].bullets[k].spriteIndex])
                    && !players[j].bullets[k].reverse
                ) {
                    // Only do something if the proper colors match
                    if(
                        (aliens[i].type == DIVER_WHITE_RED && players[j].bullets[k].color == BLACK_BLUE)
                        || (aliens[i].type == DIVER_BLACK_BLUE && players[j].bullets[k].color == WHITE_RED)
                    ) {
                        PlayerBulletReverse(&players[j].bullets[k]);
                        AlienPause(&aliens[i]);
                    } else {
                        PlayerBulletDeactivate(&players[j].bullets[k]);
                        AlienKill(&aliens[i]);
                        PlayerAddScore(&players[j], aliens[i].score);
                    }
                }
            }
        }
    }
}

void ProcessPlayerBulletCollisions() {
    u8 i = PLAYER_COUNT, j, k;
    while(i--) {
        j = PLAYER_COUNT;
        while(j--) {
            k = PLAYER_BULLET_COUNT;
            while(k--) {
                if(
                    players[j].bullets[k].active
                    && PlayerIsCollidable(&players[i])
                    && SpriteCollision(&sprites[players[i].spriteIndex], &sprites[players[j].bullets[k].spriteIndex])
                    && players[j].bullets[k].reverse
                ) {
                    PlayerBulletDeactivate(&players[j].bullets[k]);
                    PlayerKill(&players[i]);
                }
            }
        }
    }
}

void ProcessPlayerAlienCollisions() {
    u8 i = ALIEN_COUNT, j;
    while(i--) {
        j = PLAYER_COUNT;
        while(j--) {
            if(
                AlienIsCollidable(&aliens[i])
                && PlayerIsCollidable(&players[j])
                && SpriteCollision(&sprites[aliens[i].spriteIndex], &sprites[players[j].spriteIndex])
            ) {
                AlienKill(&aliens[i]);
                PlayerKill(&players[j]);
                PlayerAddScore(&players[j], aliens[i].score);
            }
        }
    }
}