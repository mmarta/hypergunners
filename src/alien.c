#include "alien.h"

Alien aliens[ALIEN_COUNT];

void AlienActivateSingle(Alien *, AlienType, u8);

void AlienInitAll() {
    u8 i = ALIEN_COUNT;
    while(i--) {
        aliens[i].active = 0;
        aliens[i].spriteIndex = NextSpriteIndex();
    }
}

void AlienActivate(AlienType type, u8 yTarget) {
    u8 i = ALIEN_COUNT;
    while(i--) {
        if(!aliens[i].active) {
            AlienActivateSingle(&aliens[i], type, yTarget);
            return;
        }
    }
}

void AlienActivateSingle(Alien *alien, AlienType type, u8 yTarget) {
    alien->yTarget = yTarget;
    u8 direction = yTarget < CENTER_SPRITE_Y ? 0 : 1;
    alien->type = type;
    alien->time = 0;
    alien->score = 1;
    alien->killTime = 0;
    alien->active = 1;

    MoveSprite(alien->spriteIndex, END_POINT_X, CENTER_SPRITE_Y, 1, 1);
    alien->distance = 2;

    if(direction) {
        if(sprites[alien->spriteIndex].x == yTarget) {
            MapSprite(alien->spriteIndex, mapAlienDiverFar);
            alien->dirPos = 0;
        } else if(yTarget - sprites[alien->spriteIndex].y < 20) {
            MapSprite(alien->spriteIndex, mapAlienDiverFarRightB);
            alien->dirPos = 1;
        } else {
            MapSprite(alien->spriteIndex, mapAlienDiverFarRightA);
            alien->dirPos = 2;
        }
    } else {
        if(sprites[alien->spriteIndex].y - yTarget < 20) {
            MapSprite(alien->spriteIndex, mapAlienDiverFarLeftB);
            alien->dirPos = -1;
        } else {
            MapSprite(alien->spriteIndex, mapAlienDiverFarLeftA);
            alien->dirPos = -2;
        }
    }
}

void AlienFire(Alien *alien) {

}

u8 AlienIsCollidable(Alien *alien) {
    return alien->active && !alien->killTime;
}

void AlienUpdate(Alien *alien) {
    if(!alien->active) return;

    // Alien in kill?
    if(alien->killTime) {
        switch(alien->killTime) {
            case 1:
                MapSprite(alien->spriteIndex, mapAlienKillA[alien->distance]);
                break;
            case 4:
                MapSprite(alien->spriteIndex, mapAlienKillB[alien->distance]);
                break;
            case 7:
                MapSprite(alien->spriteIndex, mapAlienKillC[alien->distance]);
                break;
            case 10:
                AlienDeactivate(alien);
                return;
        }
        alien->killTime++;
        return;
    }

    // Standard update
    if(sprites[alien->spriteIndex].x <= 16) {
        AlienDeactivate(alien);
    } else {
        switch(alien->dirPos) {
            case 1:
                MoveSprite(
                    alien->spriteIndex,
                    sprites[alien->spriteIndex].x - 1,
                    sprites[alien->spriteIndex].y + 1,
                    1, 1
                );
                if(sprites[alien->spriteIndex].y == alien->yTarget) {
                    MapSprite(alien->spriteIndex, mapAlienDiverFar);
                    alien->dirPos = 0;
                }
                break;
            case 2:
                MoveSprite(
                    alien->spriteIndex,
                    sprites[alien->spriteIndex].x,
                    sprites[alien->spriteIndex].y + 2,
                    1, 1
                );
                if(alien->yTarget - sprites[alien->spriteIndex].y < 20) {
                    MapSprite(alien->spriteIndex, mapAlienDiverFarRightB);
                    alien->dirPos = 1;
                }
                break;
            case -1:
                MoveSprite(
                    alien->spriteIndex,
                    sprites[alien->spriteIndex].x - 1,
                    sprites[alien->spriteIndex].y - 1,
                    1, 1
                );
                if(sprites[alien->spriteIndex].y == alien->yTarget) {
                    MapSprite(alien->spriteIndex, mapAlienDiverFar);
                    alien->dirPos = 0;
                }
                break;
            case -2:
                MoveSprite(
                    alien->spriteIndex,
                    sprites[alien->spriteIndex].x,
                    sprites[alien->spriteIndex].y - 2,
                    1, 1
                );
                if(sprites[alien->spriteIndex].y - alien->yTarget < 20) {
                    MapSprite(alien->spriteIndex, mapAlienDiverFarLeftB);
                    alien->dirPos = -1;
                }
                break;
            default: // 0
                MoveSprite(
                    alien->spriteIndex,
                    sprites[alien->spriteIndex].x - 2,
                    sprites[alien->spriteIndex].y,
                    1, 1
                );
                if(alien->distance == 2 && sprites[alien->spriteIndex].x < FAR_POINT_X) {
                    MapSprite(alien->spriteIndex, mapAlienDiverMid);
                    alien->distance = 1;
                } else if(alien->distance == 1 && sprites[alien->spriteIndex].x < MID_POINT_X) {
                    MapSprite(alien->spriteIndex, mapAlienDiverNear);
                    alien->distance = 0;
                }
                break;
        }
    }
}

void AlienKill(Alien *alien) {
    alien->killTime = 1;
}

void AlienDeactivate(Alien *alien) {
    MoveSprite(alien->spriteIndex, 0, 224, 1, 1);
    alien->active = 0;
}
