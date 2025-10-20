#include "stopwatch.h"
#include <cstring>		// std::memset


Stopwatch::Stopwatch(string name)
	: name(name) {}

void Stopwatch::update() {
	if(paused) {
		return;
	}
	//Frames
	if(++framesElapsedThisSecond == 60) {
		framesElapsedThisSecond = 0;
		//Seconds
		if(++seconds == 60) {
			seconds = 0;
			//Minutes
			if(++minutes == 60) {
				minutes = 0;
				//Hours
				hours++;
			}
		}
	}
	//Milliseconds
	milliseconds = 100 * framesElapsedThisSecond / 60;
}

void Stopwatch::pause() {
	paused = true;
}

void Stopwatch::resume() {
	paused = false;
}

void Stopwatch::reset() {
	hours = 0;
	minutes = 0;
	seconds = 0;
	milliseconds = 0;
	framesElapsedThisSecond = 0;
}

string Stopwatch::getCurrentTime() const {
	char output[12];
	string outputStr;

	std::memset(output, 0, 12);
	sprintf(output, "%02d:%02d:%02d:%02d", hours, minutes, seconds, milliseconds);
	outputStr = name + ": " + string(output);
	return outputStr;
}

bool Stopwatch::isEmpty() const {
	return framesElapsedThisSecond == 0 && milliseconds == 0 && seconds == 0 && minutes == 0 && hours == 0;
}

Stopwatch& Stopwatch::operator=(const Stopwatch& stopwatch) {
	framesElapsedThisSecond = stopwatch.framesElapsedThisSecond;
	milliseconds = stopwatch.milliseconds;
	seconds = stopwatch.seconds;
	minutes = stopwatch.minutes;
	hours = stopwatch.hours;
	return *this;
}

bool Stopwatch::operator<(const Stopwatch& stopwatch) const {
	if(hours < stopwatch.hours) {
		return true;
	} else if(minutes < stopwatch.minutes) {
		return true;
	} else if(seconds < stopwatch.seconds) {
		return true;
	} else if(milliseconds < stopwatch.milliseconds) {
		return true;
	} else {
		return false;
	}
}