#include "entity.h"
#include "functions.h"
#include "iostream"


void Entity::logic(const S_Camera& camera) {
	position += velocity;
}

Entity::~Entity() {
	UnloadTexture(texture);
}

bool Entity::checkCollisionPlatform(Platform& platform) const {
	return CheckCollisionRecs(Rectangle{position.x, position.y, (float)width, (float)height}, platform.getRec());
}

void Entity::draw(const S_Camera& camera) const {
	Vector2 offsetPos = Vector2{position.x - width/2, position.y - height/2};
	Vector2 visualPos = offsetPos - camera.getPosition();

	DrawTextureRec(texture, Rectangle{(float)width * animationFrame, 0, (float)width * (flipTexture.x ? -1 : 1), (float)height * (flipTexture.y ? -1 : 1)}, Vector2{visualPos.x, visualPos.y}, WHITE);
}