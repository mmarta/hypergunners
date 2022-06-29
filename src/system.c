#include "system.h"

int inputs[INPUT_COUNT];

void ReadInputs() {
    inputs[0] = ReadJoypad(0);
    inputs[1] = ReadJoypad(1);
}
