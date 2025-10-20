#include "platform.h"
#include "functions.h"
#include <iostream>


Platform::Platform(Rectangle rec, Color color)
	: rec(rec), color(color) {}

Platform::Platform(std::stringstream& input) {
	input >> rec.x;
	input >> rec.y;
	input >> rec.width;
	input >> rec.height;
}

Rectangle Platform::getRec() const {
	return rec;
}

void Platform::draw(const S_Camera& camera) const {
	Rectangle visualRec = rec - camera.getPosition();
	DrawRectangleRec(visualRec, color);
}