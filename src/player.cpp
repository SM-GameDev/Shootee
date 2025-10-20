#include "player.h"
#include "functions.h"
#include "camera.h"
#include "sounds.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Player::Player() {
	width = 31;
	height = 31;
	texture = LoadTexture("sprites/player.png");
	gunSprite = LoadTexture("sprites/gun.png");
	if(!IsTextureValid(texture)) {
		exit(2);
	}
	//Animations
	animationBounds[IDLE] = 0b00000000;
	animationBounds[WALKING] = 0b00110001;
	animationBounds[JUMPING] = 0b00000000;
	animationBounds[RAGDOLL] = 0b00000000;
}

Player::~Player() {
	UnloadTexture(texture);
}

void Player::setPosition(Vector2 newPos) {
	Vector2 delta = newPos - position;
	position = newPos;
	armEnd += delta;
}

void Player::logic(const S_Camera& camera) {
	if(grounded && !canShoot) {
		canShoot = true;
	}
	//Movement
	velocity.x *= grounded ? GROUND_FRICTION : AIR_FRICTION;
	velocity.y *= AIR_FRICTION;
	velocity.x += (grounded ? defaultAccel : airAccel) * (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
	if(grounded && IsKeyDown(KEY_W)) {
		velocity.y = -10;
		PlaySound(jump);
	}
	velocity.y += GRAVITY;
	Entity::logic(camera);
	collisionRec = Rectangle{position.x - 8, (float)position.y - 15.5f, 16, 31};
	//Animation
	flipTexture = {false, false};
	if(!grounded) {
		switchState(JUMPING);
	}
	else {
		if(fabs(velocity.x) > 0.2) {
			switchState(WALKING);
			flipTexture.x = velocity.x < 0;
		} else {
			switchState(IDLE);
		}
	}
	updateAnimation();

	//Arm position
	Vector2 deltaArm = Vector2{mouse.getPosX(), mouse.getPosY()} + camera.getPosition() - position;
	if(vectorMagnitude(deltaArm) > 10) {
		deltaArm = 8/vectorMagnitude(deltaArm) * deltaArm;
	}
	armEnd = position + deltaArm;

	//Unground
	grounded = false;
}

void Player::updateAnimation() {
	animationSubFrame++;
	if(animationSubFrame == 6) {
		animationFrame++;
		animationSubFrame = 0;
	}
	if(animationFrame >= (animationBounds[state] >> 4) & 0b1111) {
		animationFrame = animationBounds[state] & 0b1111;
	}
}

void Player::draw(const S_Camera& camera) const {
	Entity::draw(camera);
	//Drawing second arm
	drawArm(camera, position, armEnd);
	drawGun(camera);
}

void Player::drawArm(const S_Camera& camera, const Vector2& start, Vector2 end) const {
	DrawLineEx(start - camera.getPosition(), end - camera.getPosition(), 2, BLACK);
}

void Player::drawGun(const S_Camera& camera) const {
	Vector2 difference = armEnd - position;
	float angle = atan2(difference.y, difference.x);
	Vector2 cameraPos = camera.getPosition();
	DrawTexturePro(gunSprite, Rectangle{0, 0, 8, (difference.x < 0 ? -6.f : 6.f)}, Rectangle{armEnd.x - cameraPos.x, armEnd.y - cameraPos.y, 8, 6}, Vector2{4, 3}, angle * RAD2DEG, WHITE);
}

void Player::switchState(State newState) {
	if(state == newState) {
		return;
	}
	state = newState;
	animationFrame = 0;
	animationSubFrame = 0;
}

bool Player::checkCollisionPlatform(const Platform& platform) const {
	return CheckCollisionRecs(collisionRec, platform.getRec());
} 

void Player::resolveCollisionPlatform(const Platform& platform) {
	Rectangle platformRec = platform.getRec();

	float overlapX = std::min(collisionRec.x + collisionRec.width, platformRec.x + platformRec.width)
                   - std::max(collisionRec.x, platformRec.x);

    float overlapY = std::min(collisionRec.y + collisionRec.height, platformRec.y + platformRec.height)
                   - std::max(collisionRec.y, platformRec.y);

    // Resolve along the smallest overlap
    if (overlapX < overlapY)
    {	
		if(velocity.x > 0 != collisionRec.x < platformRec.x) {
			return;
		}
        // Horizontal resolution
        if (collisionRec.x < platformRec.x)
            collisionRec.x -= overlapX; // push left
        else
            collisionRec.x += overlapX; // push right

        velocity.x = 0;
    }
    else
    {
        // Vertical resolution
		if(velocity.y > 0 != collisionRec.y < platformRec.y) {
			return;
		}
        if (collisionRec.y < platformRec.y)
        {
            collisionRec.y -= overlapY; // push up (land on top)
            grounded = true;
        }
        else
            collisionRec.y += overlapY; // push down (hit ceiling)

        velocity.y = 0;
    }

	position = Vector2{collisionRec.x + 8, collisionRec.y + 15.5f};
}

Vector2 Player::getPos() const {
	return position;
}

Rectangle Player::getCollisionRec() {
	return collisionRec;
}

void Player::addForce(Vector2 force) {
	velocity += (1/mass) * force;
}

Vector2 Player::getGunOffset() const {
	return armEnd - position;
}

void Player::zeroVelocity() {
	velocity = Vector2{0, 0};
}