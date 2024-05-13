#include "keypad.h"
#include "memory.h"
#include <SDL2/SDL.h>

#define CHECK_KEY(scancode, bit) \
if(keystate[scancode]) \
    KEYINPUT &= ~(1 << bit)

const Uint8* keystate;

void init_keypad(){
    keystate = SDL_GetKeyboardState(NULL);
}

void update_keypad(){
    KEYINPUT = 0xFFFF;
    
    CHECK_KEY(SDL_SCANCODE_X, 0);
    CHECK_KEY(SDL_SCANCODE_Z, 1);
    CHECK_KEY(SDL_SCANCODE_RSHIFT, 2);
    CHECK_KEY(SDL_SCANCODE_RETURN, 3);
    CHECK_KEY(SDL_SCANCODE_RIGHT, 4);
    CHECK_KEY(SDL_SCANCODE_LEFT, 5);
    CHECK_KEY(SDL_SCANCODE_UP, 6);
    CHECK_KEY(SDL_SCANCODE_DOWN, 7);
    CHECK_KEY(SDL_SCANCODE_S, 8);
    CHECK_KEY(SDL_SCANCODE_A, 9);
    
}