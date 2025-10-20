#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

class S_Camera {
	Vector2 position;
	Vector2 target;
	Vector2 min;
	Vector2 max;

	public:
	S_Camera();
	S_Camera(Vector2 min, Vector2 max);
	void update();
	Vector2 getPosition() const;
	void setTarget(const Vector2& newTarget);
};

#endif