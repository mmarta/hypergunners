#include "bullet.h"

void PlayerBulletInit(PlayerBullet *bullet, u8 playerIndex) {
    bullet->spriteIndex = NextSpriteIndex();
    bullet->playerIndex = playerIndex;
    MoveSprite(bullet->spriteIndex, 0, 224, 1, 1);
}

void PlayerBulletActivate(PlayerBullet *bullet, u8 x, u8 y, PlayerColor color) {
    bullet->active = 1;
    bullet->depthIndex = 0;
    bullet->color = color;
    bullet->reverse = 0;
    MapSprite(bullet->spriteIndex, bullet->color == BLACK_BLUE ? mapBluePlayerBulletA : mapRedPlayerBulletA);
    MoveSprite(bullet->spriteIndex, x, y, 1, 1);
}

void PlayerBulletUpdate(PlayerBullet *bullet) {
    if(!bullet->active) return;

    if(sprites[bullet->spriteIndex].x >= END_POINT_X) {
        PlayerBulletDeactivate(bullet);
        return;
    }

    MoveSprite(
        bullet->spriteIndex,
        sprites[bullet->spriteIndex].x + 4,
        sprites[bullet->spriteIndex].y,
        1, 1
    );

    if(!bullet->reverse) {    
        
    } else {
        if(sprites[bullet->spriteIndex].x >= FAR_POINT_X && bullet->depthIndex == 1) {
            bullet->depthIndex = 2;
            MapSprite(
                bullet->spriteIndex,
                bullet->color == BLACK_BLUE
                    ? mapBluePlayerBulletC
                    : mapRedPlayerBulletC
            );
        } else if(sprites[bullet->spriteIndex].x >= MID_POINT_X && bullet->depthIndex == 0) {
            bullet->depthIndex = 1;
            MapSprite(
                bullet->spriteIndex,
                bullet->color == BLACK_BLUE
                    ? mapBluePlayerBulletB
                    : mapRedPlayerBulletB
            );
        }
    }
}

void PlayerBulletDeactivate(PlayerBullet *bullet) {
    MoveSprite(bullet->spriteIndex, 0, 224, 1, 1);
    bullet->active = 0;
}
