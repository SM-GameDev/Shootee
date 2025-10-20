#include "level.h"
#include "functions.h"
#include "sounds.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using std::string;

Level::Level() {}

Level::Level(const char* levelData) {
	currentTime.resume();
	bullet = Bullet(&player);
	background = LoadTexture("sprites/background.png");
	std::ifstream inputFile;
	inputFile.open(levelData);
	if(!inputFile) {
		std::cout << "failed to open file" << std::endl;
		return;
	}
	
	string currLine;
	//Getting basic level info
	getline(inputFile, currLine);
	std::stringstream ss(currLine);
	ss >> spawn.x >> spawn.y;
	player.setPosition(spawn);
	Vector2 cameraMin;
	Vector2 cameraMax;
	ss >> cameraMin.x >> cameraMin.y >> cameraMax.x >> cameraMax.y;
	camera = S_Camera(cameraMin, cameraMax);

	while(getline(inputFile, currLine)) {
		std::stringstream ss(currLine);
		int type;
		ss >> type;
		switch(type) {
			case 0:
				platforms.emplace_back(Platform(ss));
				break;
			case 1:
				billboards.emplace_back(Billboard(ss));
			default:
				break;
		}
	}
}

Level::~Level() {
	UnloadTexture(background);
}

void Level::update() {
	player.logic(camera);
	//Respawn player
	if(player.getPos().y > 500 || IsKeyPressed(KEY_R)) {
		player.setPosition(spawn);
		player.zeroVelocity();
		bullet.active = false;
		if(gameBeat) {
			gameBeat = false;
			currentTime.reset();
			currentTime.resume();
		}
	}
	camera.update();
	camera.setTarget(player.getPos());

	for(Platform& p : platforms) {
		if(player.checkCollisionPlatform(p)) {
			player.resolveCollisionPlatform(p);
		}
	}
	//Bullet
	if(!bullet.active) {
		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			if(player.canShoot) {
				Vector2 gunVector = player.getGunOffset();
				bullet.position = player.getPos() + gunVector;
				bullet.velocity = 40 / vectorMagnitude(gunVector) * gunVector;
				bullet.active = true;
				player.canShoot = false;
				PlaySound(shoot);
			} else {
				PlaySound(noAmmo);
			}
			
		}
	}
	bullet.logic();

	//Timers
	if(player.getPos().x >=  6440) {
		currentTime.pause();
		if(currentTime < bestTime || bestTime.isEmpty()) {
			bestTime = currentTime;
		}
		if(!gameBeat) {
			showTimers = true;
			gameBeat = true;
			PlaySound(fanfare);
		}
		
	}
	currentTime.update();
}

void Level::draw() const {
	Vector2 backgroundPos = Vector2{-50, -50};
	Vector2 backgroundOffsets = Vector2{(float)(-(int)camera.getPosition().x % 32), (float)(-(int)camera.getPosition().y % 32)};
	backgroundPos = backgroundPos + backgroundOffsets;
	DrawTexture(background, backgroundPos.x, backgroundPos.y, WHITE);
	for(const Platform& p : platforms) {
		p.draw(camera);
	}
	for(const Billboard& b : billboards) {
		b.draw(camera);
	}
	player.draw(camera);
	bullet.draw(camera);

	if(showTimers) {
		std::string currentTimeStr = this->currentTime.getCurrentTime();
		std::string bestTimeStr = this->bestTime.getCurrentTime();
		DrawText(currentTimeStr.c_str(), 10, 10, 20, BLACK);
		DrawText(bestTimeStr.c_str(), 10, 32, 20, BLACK);
	}
	if(gameBeat) {
		DrawText("Press R to Reset", 320 - MeasureText("Press R to Reset", 20) / 2, 230, 20, BLACK);
	}
}