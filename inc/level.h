#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include "platform.h"
#include "player.h"
#include "billboard.h"
#include "bullet.h"
#include "stopwatch.h"

using std::ifstream;

class Level {
	Stopwatch currentTime = Stopwatch("Current");
	Stopwatch bestTime = Stopwatch("Best");
	Player player;
	Vector2 spawn = {0, 0};
	std::list<Platform> platforms;
	std::list<Billboard> billboards;
	Bullet bullet;
	Texture background;
	S_Camera camera;
	bool showTimers = false;
	bool gameBeat = false;

	public:
	Level();
	Level(const char* levelData);
	~Level();
	void update();
	void draw() const;
};

#endif