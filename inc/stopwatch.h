#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <string>	//std::string

using std::string;

class Stopwatch {
	string name;
	unsigned int framesElapsedThisSecond = 0;
	unsigned int hours = 0;
	unsigned int minutes = 0;
	unsigned int seconds = 0;
	unsigned int milliseconds = 0;
	bool paused = false;

	public:
	Stopwatch(string name);
	void update();
	void pause();
	void resume();
	void reset();
	string getCurrentTime() const;
	bool isEmpty() const;

	Stopwatch& operator=(const Stopwatch& stopwatch);
	bool operator<(const Stopwatch& stopwatch1) const;
};

#endif