#ifndef MOUSE_H
#define MOUSE_H

#include "raylib.h"
#include "screen.h"

class Mouse {
	public:
	Vector2 position;
	Texture texture;
	Screen* screen;
	float visualScale;
	

	public:
	Mouse() = default;
	Mouse(Screen* screen, float visualScale = 1.f);
	~Mouse();
	float getPosX() const;
	float getPosY() const;
	void update();
	void clipToScreen();
	void draw() const;
};

extern Mouse mouse;

#endif
