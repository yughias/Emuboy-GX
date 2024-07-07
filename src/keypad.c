#include "keypad.h"
#include "memory.h"
#include <SDL2/SDL.h>

#define CHECK_KEY(scancode, bit) \
if(keystate[scancode]) \
    keyinput &= ~(1 << bit)

#define CHECK_CONTROLLER(code, bit) \
if(gameController && SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_ ## code))  \
    keyinput &= ~(1 << bit)

const Uint8* keystate;
SDL_GameController* gameController;

void init_keypad(){
    keystate = SDL_GetKeyboardState(NULL);
    gameController = SDL_GameControllerOpen(0);
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

    CHECK_CONTROLLER(B, 0);
    CHECK_CONTROLLER(A, 1);
    CHECK_CONTROLLER(BACK, 2);
    CHECK_CONTROLLER(START, 3);
    CHECK_CONTROLLER(DPAD_RIGHT, 4);
    CHECK_CONTROLLER(DPAD_LEFT, 5);
    CHECK_CONTROLLER(DPAD_UP, 6);
    CHECK_CONTROLLER(DPAD_DOWN, 7);
    CHECK_CONTROLLER(RIGHTSHOULDER, 8);
    CHECK_CONTROLLER(LEFTSHOULDER, 9);

    return keyinput;
}