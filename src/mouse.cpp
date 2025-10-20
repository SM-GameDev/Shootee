#include "mouse.h"
#include <iostream>

Mouse::Mouse(Screen* screen, float visualScale)
	: screen(screen), visualScale(visualScale)
{
	texture = LoadTexture("sprites/cursor.png");
	//SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
}

Mouse::~Mouse() {
	//if(IsTextureValid(texture)) {
	//	UnloadTexture(texture);
	//}
}

float Mouse::getPosX() const {
	return position.x;
}

float Mouse::getPosY() const {
	return position.y;
}

void Mouse::update() {
	position.x = GetMouseX();
	position.y = GetMouseY();
	clipToScreen();
}

void Mouse::clipToScreen() {
	Rectangle screenBounds = screen->getOutputBounds();
	float screenWidth = screen->getDimensions().x;
	float scale = screenBounds.width / screenWidth;
	//X
	if(position.x < screenBounds.x) {
		position.x = screenBounds.x;
	} else if(position.x > screenBounds.x + screenBounds.width) {
		position.x = screenBounds.x + screenBounds.width;
	}
	position.x -= screenBounds.x;
	position.x /= scale;
	//Y
	if(position.y < screenBounds.y) {
		position.y = screenBounds.y;
	} else if(position.y > screenBounds.y + screenBounds.height) {
		position.y = screenBounds.y + screenBounds.height;
	}
	position.y -= screenBounds.y;
	position.y /= scale;
}

void Mouse::draw() const {
	if(!IsCursorOnScreen()) {
		return;
	}
	DrawTextureEx(texture, {position.x - 6, position.y - 2}, 0, visualScale, WHITE);
}

Mouse mouse;