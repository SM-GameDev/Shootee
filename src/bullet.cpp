#include "bullet.h"
#include "functions.h"
#include "sounds.h"
#include <iostream>

Bullet::Bullet(Player* target)
	: target(target)
{
	position = {400, 400};
}

void Bullet::logic() {
	if(!active)
		return;
	//Updating position
	velocity = 0.8 * velocity;
	position += velocity;

	//Gravity
	Vector2 targetPos = target->getPos();
	Vector2 difference = targetPos - position;
	float distance = vectorMagnitude(difference);
	if(distance < 20) {
		distance = 20;
	}
	Vector2 direction = (1/distance) * difference;
	float strength = (1.0f + distance * 0.02f);
	velocity += (strength * 6.0f) * direction;

	collisionPlayer();
}

void Bullet::checkCollisionPlatform(const Platform& platform) {
	if(!active)
		return;
	if(CheckCollisionCircleRec(position, radius, platform.getRec())) {
		active = false;
	}
}

void Bullet::collisionPlayer() {
	if(CheckCollisionCircleRec(position, radius, target->getCollisionRec())) {
		//Vector2 targetPos = target->getPos();
		//Vector2 difference = targetPos - position;
		//difference = (1/vectorMagnitude(difference)) * difference;
		target->addForce(10/vectorMagnitude(velocity) * velocity);
		active = false;
		PlaySound(hit);
	}
}

void Bullet::draw(const S_Camera& camera) const {
	if(!active)
		return;
	Vector2 newPos = position - camera.getPosition();
	DrawCircle(newPos.x, newPos.y, radius, Color{200, 160, 0, 255});
}

