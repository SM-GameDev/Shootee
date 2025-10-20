#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "screen.h"
#include "mouse.h"
#include "platform.h"

typedef enum State {
	IDLE,
	WALKING,
	JUMPING,
	RAGDOLL,
} State;

class Player : public Entity {
	public:
	bool canShoot = false;

	private:
	bool hasGun = false;
	Texture gunSprite;
	Rectangle collisionRec;
	bool grounded = false;
	bool ragdoll = false;
	float defaultAccel = 0.5;
	float airAccel = 0.15;
	State state = IDLE;
	int animationBounds[4];
	Vector2 armEnd = position;
	float mass = 1;

	public:
	Player();
	~Player();
	void setPosition(Vector2 newPos);
	virtual void logic(const S_Camera& camera) override;
	void updateAnimation();
	void draw(const S_Camera& camera) const;
	void drawArm(const S_Camera& camera, const Vector2& start, Vector2 end) const;
	void drawGun(const S_Camera& camera) const;
	void switchState(State newState);
	bool checkCollisionPlatform(const Platform& platform) const;
	void resolveCollisionPlatform(const Platform& platform);
	Vector2 getPos() const;
	Rectangle getCollisionRec();
	void addForce(Vector2 force);
	Vector2 getGunOffset() const;
	void zeroVelocity();

};

#endif