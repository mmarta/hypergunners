#include "defines.h"
#include "system.h"
#include "gfx.h"
#include "player.h"
#include "alien.h"

int main() {
    u8 i, testTime = 0;
    srand(GetTrueRandomSeed());

    SetTileTable(gfxTiles);
    SetSpritesTileTable(gfxSpriteTiles);
    SetSpriteVisibility(1);
    ClearVram();

    EnableSoundEngine();

    PrintVerticalRAM(31, 0, "BLAHBLAH");

    PlayerInitAll();
    AlienInitAll();

    PlayerStart(&players[0]);
    //PlayerStart(&players[1]);

    while(1) {
        WaitVsync(1);
        ReadInputs();

        testTime++;
        if(testTime == 90) {
            AlienActivate(DIVER, rand() % 216);
            testTime = 0;
        }

        // BG Stuff first
        PlayerUpdateBG(&players[0]);
        PlayerUpdateBG(&players[1]);

        PlayerInput(&players[0]);
        PlayerInput(&players[1]);

        i = ALIEN_COUNT;
        while(i--) AlienUpdate(&aliens[i]);

        PlayerUpdate(&players[0]);
        PlayerUpdate(&players[1]);
    }

    return 0;
}