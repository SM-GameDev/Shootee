#ifndef SOUNDS_H
#define SOUNDS_H

#include "raylib.h"

extern Sound shoot;
extern Sound hit;
extern Sound noAmmo;
extern Sound jump;
extern Sound fanfare;

void loadSounds();
void unloadSounds();

#endif