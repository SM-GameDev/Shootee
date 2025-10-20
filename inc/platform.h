#ifndef PLATFORM_H
#define PLATFORM_H

#include "raylib.h"
#include "camera.h"
#include <sstream>

class Platform {
	Rectangle rec = {0, 0, 100, 100};
	const Color color = Color{140, 140, 140, 255};

	public:
	Platform() = default;
	Platform(Rectangle rec, Color color = WHITE);
	Platform(std::stringstream& input);
	Rectangle getRec() const;
	void draw(const S_Camera& camera) const;
};

class MovingPlatform {
	
};

#endif