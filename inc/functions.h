#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "raylib.h"

//Shapes
Rectangle operator+(const Rectangle& rec, const Vector2& vec);
Rectangle operator-(const Rectangle& rec, const Vector2& vec);
Rectangle recFromCenter(const float posX, const float posY, const float width, const float height);

//Vectors
Vector2 operator+(const Vector2& vec1, const Vector2& vec2);
Vector2 operator+=(Vector2& vec1, const Vector2& vec2);
Vector2 operator-(const Vector2& vec1, const Vector2& vec2);
Vector2 operator*(const float scalar, const Vector2& vec);
float vectorMagnitude(const Vector2& vec);

#endif
