#include "bullet.h"

void PlayerBulletInit(PlayerBullet *bullet, u8 playerIndex) {
    bullet->spriteIndex = NextSpriteIndex();
    bullet->playerIndex = playerIndex;
    MoveSprite(bullet->spriteIndex, 0, 224, 1, 1);
}

void PlayerBulletActivate(PlayerBullet *bullet, u8 x, u8 y) {
    bullet->active = 1;
    bullet->depthIndex = 0;
    MapSprite(bullet->spriteIndex, bullet->playerIndex ? mapRightPlayerBullet[0] : mapLeftPlayerBullet[0]);
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

    if(sprites[bullet->spriteIndex].x >= FAR_POINT_X && bullet->depthIndex == 1) {
        bullet->depthIndex = 2;
        MapSprite(
            bullet->spriteIndex,
            bullet->playerIndex
                ? mapRightPlayerBullet[bullet->depthIndex]
                : mapLeftPlayerBullet[bullet->depthIndex]
        );
    } else if(sprites[bullet->spriteIndex].x >= MID_POINT_X && bullet->depthIndex == 0) {
        bullet->depthIndex = 1;
        MapSprite(
            bullet->spriteIndex,
            bullet->playerIndex
                ? mapRightPlayerBullet[bullet->depthIndex]
                : mapLeftPlayerBullet[bullet->depthIndex]
        );
    }
}

void PlayerBulletDeactivate(PlayerBullet *bullet) {
    MoveSprite(bullet->spriteIndex, 0, 224, 1, 1);
    bullet->active = 0;
}
