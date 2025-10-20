#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "raylib.h"
#include "camera.h"
#include <sstream>

class Billboard {
	Texture texture;
	Vector2 position;

	public:
	Billboard(const char* fileName, Vector2 position);
	Billboard(std::stringstream& ss);
	~Billboard();
	void draw(const S_Camera& camera) const;
};

#endif