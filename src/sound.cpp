#include "sounds.h"

Sound shoot;
Sound hit;
Sound noAmmo;
Sound jump;
Sound fanfare;

void loadSounds() {
	shoot = LoadSound("sounds/shot_heavy.wav");
	hit = LoadSound("sounds/shot_light.wav");
	noAmmo = LoadSound("sounds/no_ammo.wav");
	jump = LoadSound("sounds/jump.wav");
	fanfare = LoadSound("sounds/fanfare.wav");
}

void unloadSounds() {
	UnloadSound(shoot);
	UnloadSound(hit);
	UnloadSound(noAmmo);
	UnloadSound(jump);
	UnloadSound(fanfare);
}