#include "gfx.h"

// Tile includes

#include "../data/gfx/tiles.inc"
#include "../data/gfx/spriteTiles.inc"

u8 spriteIndexCount = 0;

u8 NextSpriteIndex() {
    return spriteIndexCount++;
}

// Printing Functinos

void PrintVerticalPROGMEM(u8 x, u8 y, const char *str) {
    u8 i = 0, c = pgm_read_byte(&(str[i]));
    while(c) {
        SetTile(x, y++, c - 32);
        c = pgm_read_byte(&(str[++i]));
    }
}

void PrintVerticalRAM(u8 x, u8 y, const char *str) {
    u8 i = 0;
    while(str[i]) {
        SetTile(x, y++, str[i] - 32);
        i++;
    }
}


void PrintVerticalChar(u8 x, u8 y, char ch) {
    SetTile(x, y, ch - 32);
}

void PrintU8Vertical(u8 x, u8 y, u8 val) {
    u8 max = 0xff, first = 1, modVal;

    do {
        modVal = val % 10;
        SetTile(x, y--, !first && modVal == 0 && val == 0 ? 0 : modVal + 16);
        val /= 10;
        max /= 10;
        first = 0;
    } while(max > 0);
}

void PrintU16Vertical(u8 x, u8 y, u16 val, u16 maxVal, u8 padHundredScore) {
    u8 first = 1, modVal;

    if(padHundredScore) {
        SetTile(x, y--, 16);
        SetTile(x, y--, 16);
    }

    do {
        modVal = val % 10;
        SetTile(x, y--, !first && modVal == 0 && val == 0 ? 0 : modVal + 16);
        val /= 10;
        maxVal /= 10;
        first = 0;
    } while(maxVal > 0);
}
