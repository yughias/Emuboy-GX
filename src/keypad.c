#include "keypad.h"
#include "memory.h"
#include <SDL2/SDL.h>

#define CHECK_KEY(scancode, bit) \
if(keystate[scancode]) \
    keyinput &= ~(1 << bit)

const Uint8* keystate;

void init_keypad(){
    keystate = SDL_GetKeyboardState(NULL);
}

u16 update_keypad(){
    u16 keyinput = 0xFFFF;
    
    CHECK_KEY(SDL_SCANCODE_X, 0);
    CHECK_KEY(SDL_SCANCODE_Z, 1);
    CHECK_KEY(SDL_SCANCODE_RSHIFT, 2);
    #ifdef EMSCRIPTEN
    CHECK_KEY(SDL_SCANCODE_LSHIFT, 2);
    #endif
    CHECK_KEY(SDL_SCANCODE_RETURN, 3);
    CHECK_KEY(SDL_SCANCODE_RIGHT, 4);
    CHECK_KEY(SDL_SCANCODE_LEFT, 5);
    CHECK_KEY(SDL_SCANCODE_UP, 6);
    CHECK_KEY(SDL_SCANCODE_DOWN, 7);
    CHECK_KEY(SDL_SCANCODE_S, 8);
    CHECK_KEY(SDL_SCANCODE_A, 9);
    
    return keyinput;
}