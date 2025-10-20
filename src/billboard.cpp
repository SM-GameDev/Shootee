#include "billboard.h"
#include "functions.h"
#include <string>
#include <iostream>

Billboard::Billboard(const char* fileName, Vector2 position)
	: position(position)
{
	texture = LoadTexture(fileName);
}

Billboard::Billboard(std::stringstream& ss) {
	ss >> position.x >> position.y;
	std::string textureLocation;
	std::getline(ss, textureLocation);
	textureLocation.erase(0, textureLocation.find_first_not_of(' '));
	texture = LoadTexture(textureLocation.c_str());
	if(!IsTextureValid(texture)) {
		exit(1);
	}
}

Billboard::~Billboard() {
	//UnloadTexture(texture);
}

void Billboard::draw(const S_Camera& camera) const {
	Vector2 newVec = position - camera.getPosition();
	DrawTexture(texture, newVec.x, newVec.y, WHITE);
}