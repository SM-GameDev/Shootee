#include "functions.h"
#include <cmath>

Rectangle operator+(const Rectangle& rec, const Vector2& vec) {
	return Rectangle{rec.x + vec.x, rec.y + vec.y, rec.width, rec.height};
}

Rectangle operator-(const Rectangle& rec, const Vector2& vec) {
	return Rectangle{rec.x - vec.x, rec.y - vec.y, rec.width, rec.height};
}

Rectangle recFromCenter(const float posX, const float posY, const float width, const float height) {
	float newPosX = posX - width/2;
	float newPosY = posY - width/2;
	return Rectangle{newPosX, newPosY, width, height};
}

Vector2 operator+(const Vector2& vec1, const Vector2& vec2) {
	float xComponent = vec1.x + vec2.x;
	float yComponent = vec1.y + vec2.y;
	return Vector2{xComponent, yComponent};
}

Vector2 operator+=(Vector2& vec1, const Vector2& vec2) {
	vec1 = vec1 + vec2;
	return vec1;
}

Vector2 operator-(const Vector2& vec1, const Vector2& vec2) {
	float xComponent = vec1.x - vec2.x;
	float yComponent = vec1.y - vec2.y;
	return Vector2{xComponent, yComponent};
}

Vector2 operator*(const float scalar, const Vector2& vec) {
	return Vector2{scalar * vec.x, scalar * vec.y};
};

float vectorMagnitude(const Vector2& vec) {
	float xComponent = vec.x * vec.x;
	float yComponent = vec.y * vec.y;
	return sqrt(xComponent + yComponent);
}