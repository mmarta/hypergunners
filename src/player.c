#include "player.h"

Player players[PLAYER_COUNT];

void PlayerFire(Player *);
void PlayerSwitchColor(Player *);
void PlayerDraw(Player *player);

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
    player->color = WHITE_RED;

    MapSprite(player->spriteIndex, player->index ? mapRightWhitePlayerA : mapLeftWhitePlayerA);
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

    if(inputs[player->index] & BTN_B) {
        if(!player->colorButton) {
            PlayerSwitchColor(player);
            player->colorButton = 1;
        }
    } else if(player->colorButton) {
        player->colorButton = 0;
    }
}

void PlayerSwitchColor(Player *player) {
    if(player->color == BLACK_BLUE)
        player->color = WHITE_RED;
    else
        player->color = BLACK_BLUE;

    PlayerDraw(player);
}

void PlayerFire(Player *player) {
    u8 i = PLAYER_BULLET_COUNT;
    while(i--) {
        if(!player->bullets[i].active) {
            PlayerBulletActivate(
                &player->bullets[i],
                sprites[player->spriteIndex].x,
                sprites[player->spriteIndex].y,
                player->color
            );
            return;
        }
    }
}

void PlayerAddScore(Player *player, u8 score) {
    player->score += score;
    player->updateScore = 1;
}

void PlayerUpdateBG(Player *player) {
    if(player->updateScore) {
        PrintU16Vertical(30, player->index ? 27 : 7, player->score, 50000, 1);
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
        case 3:
        case 6:
        case 9:
            PlayerDraw(player);
            break;
    }

    player->animTime++;
    if(player->animTime >= 12) {
        player->animTime = 0;
    }
}

void PlayerDraw(Player *player) {
    if(player->color == WHITE_RED) {
        if(player->animTime < 3)
            MapSprite(player->spriteIndex, player->index ? mapRightWhitePlayerA : mapLeftWhitePlayerA);
        else if(player->animTime < 6 || player->animTime >= 9)
            MapSprite(player->spriteIndex, player->index ? mapRightWhitePlayerB : mapLeftWhitePlayerB);
        else
            MapSprite(player->spriteIndex, player->index ? mapRightWhitePlayerC : mapLeftWhitePlayerC);
    } else {
        if(player->animTime < 3)
            MapSprite(player->spriteIndex, player->index ? mapRightBlackPlayerA : mapLeftBlackPlayerA);
        else if(player->animTime < 6 || player->animTime >= 9)
            MapSprite(player->spriteIndex, player->index ? mapRightBlackPlayerB : mapLeftBlackPlayerB);
        else
            MapSprite(player->spriteIndex, player->index ? mapRightBlackPlayerC : mapLeftBlackPlayerC);
    }
    
}