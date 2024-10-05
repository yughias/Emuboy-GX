#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include <SDL2/SDL.h>

#include "integer.h"

extern const Uint8* keystate;
extern SDL_GameController* gameController;

void init_keypad();
u16 update_keypad();
void check_controller_connection();

#endif