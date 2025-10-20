#include "camera.h"
#include <algorithm>
#include <iostream>

S_Camera::S_Camera()
	: position(Vector2{0, 0}), target(Vector2{0, 0}) {}

S_Camera::S_Camera(Vector2 min, Vector2 max) 
	: S_Camera()
{
	this->min = min;
	this->max = max;
}

void S_Camera::update() {
	//
	// Set target here
	//
	position = target;
	return;
}

Vector2 S_Camera::getPosition() const {
	return position;
}

void S_Camera::setTarget(const Vector2& newTarget) {
	float x = newTarget.x - 320;
	float y = newTarget.y - 320;
	x = std::max(x, min.x);
	x = std::min(x, max.x);
	y = std::max(y, min.y);
	y = std::min(y, max.y);
	target = {x, y};
}