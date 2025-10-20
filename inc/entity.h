#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"
#include "platform.h"
#include "mouse.h"
#include "camera.h"

#define GRAVITY 0.3
#define AIR_FRICTION 0.96
#define GROUND_FRICTION 0.85

class Entity {
	protected:
	Vector2 position = {0, 0};
	Vector2 velocity = {0, 0};
	Vector2 flipTexture = {false, false};
	Texture texture;
	unsigned int width = 1;
	unsigned int height = 1;
	unsigned int animationFrame = 0;
	unsigned int animationSubFrame = 0;


	public:
	Entity() = default;
	virtual ~Entity();
	virtual void logic(const S_Camera& camera);
	virtual bool checkCollisionPlatform(Platform& platform) const;
	void draw(const S_Camera& camera) const;
};

#endif