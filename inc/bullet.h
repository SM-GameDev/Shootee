#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include "player.h"

class Bullet {
	public:
	Vector2 position;
	Vector2 velocity;
	Player* target;
	bool active = false;
	float radius = 4;
	
	public:
	Bullet() = default;
	Bullet(Player* target);
	void logic();
	void collisionPlayer();
	void checkCollisionPlatform(const Platform& platform);
	void draw(const S_Camera& camera) const;
};

#endif