#include "player.h"

Player players[PLAYER_COUNT];

void PlayerInitAll() {
    u8 i = PLAYER_COUNT, j;
    while(i--) {
        players[i].index = i;
        players[i].active = 0;
        players[i].spriteIndex = NextSpriteIndex();
        j = PLAYER_BULLET_COUNT;
        while(j--) {
            PlayerBulletInit(&players[i].bullets[j], i);
        }
    }
}

void PlayerStart(Player *player) {
    player->active = 1;

    player->animTime = 0;
    player->score = 0;
    player->updateScore = 1;

    MapSprite(player->spriteIndex, player->index ? mapRightPlayer[0] : mapLeftPlayer[0]);
    MoveSprite(player->spriteIndex, 16, CENTER_SPRITE_Y, 1, 1);
}

void PlayerInput(Player *player) {
    if(!player->active) return;
    
    if(inputs[player->index] & BTN_LEFT) {
        MoveSprite(
            player->spriteIndex,
            sprites[player->spriteIndex].x,
            sprites[player->spriteIndex].y - 2,
            1, 1
        );
    } else if(inputs[player->index] & BTN_RIGHT) {
        MoveSprite(
            player->spriteIndex,
            sprites[player->spriteIndex].x,
            sprites[player->spriteIndex].y + 2,
            1, 1
        );
    }

    if(inputs[player->index] & BTN_A) {
        if(!player->fireButton) {
            PlayerFire(player);
            player->fireButton = 1;
        }
    } else if(player->fireButton) {
        player->fireButton = 0;
    }
}

void PlayerFire(Player *player) {
    u8 i = PLAYER_BULLET_COUNT;
    while(i--) {
        if(!player->bullets[i].active) {
            PlayerBulletActivate(
                &player->bullets[i],
                sprites[player->spriteIndex].x,
                sprites[player->spriteIndex].y
            );
            return;
        }
    }
}

void PlayerUpdateBG(Player *player) {
    if(player->updateScore) {
        PrintU16Vertical(30, 7, player->score, 50000, 1);
        player->updateScore = 0;
    }
}

void PlayerUpdate(Player *player) {
    // Bullet updates
    u8 i = PLAYER_BULLET_COUNT;
    while(i--) {
        PlayerBulletUpdate(&player->bullets[i]);
    }

    if(!player->active) return;

    switch(player->animTime) {
        case 0:
            MapSprite(player->spriteIndex, player->index ? mapRightPlayer[0] : mapLeftPlayer[0]);
            break;
        case 3:
        case 9:
            MapSprite(player->spriteIndex, player->index ? mapRightPlayer[1] : mapLeftPlayer[1]);
            break;
        case 6:
            MapSprite(player->spriteIndex, player->index ? mapRightPlayer[2] : mapLeftPlayer[2]);
            break;
    }

    player->animTime++;
    if(player->animTime >= 12) {
        player->animTime = 0;
    }
}
