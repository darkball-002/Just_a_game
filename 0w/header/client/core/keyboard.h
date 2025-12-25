#define Keyboard_CLASS

#include "core/value.h"

typedef enum KeyState__ {
    Keyboard_Released, Keyboard_Pressed, Keyboard_Repeat
} KeyState[7];

enum {
    Keyboard_T, Keyboard_W, Keyboard_A, Keyboard_S, Keyboard_D, Keyboard_Space, Keyboard_Shift
};

void keyboard_getKey(void* window, KeyState turnback);

void keyboard_getMouseKey(void* window, double feedback[2]);