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
                ) {
                    PlayerBulletDeactivate(&players[j].bullets[k]);
                    
                    // Only do something if the proper colors match
                    if(
                        (aliens[i].type == DIVER_WHITE_RED && players[j].bullets[k].color == BLACK_BLUE)
                        || (aliens[i].type == DIVER_BLACK_BLUE && players[j].bullets[k].color == WHITE_RED)
                    );
                    else {
                        AlienKill(&aliens[i]);
                        PlayerAddScore(&players[j], aliens[i].score);
                    }
                }
            }
        }
    }
}