/*
 *  Timer.cpp
 *  intersect
 *
 *  Created by Ben Jones on 07/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Timer.h"

Timer::Timer() {
	totalTime = 10000;
}

void Timer::start() {
	// When timer starts store current time in savedTime
	savedTime = ofGetElapsedTimeMillis();
}

// Check when timer reaches timer length (totalTime)
bool Timer::finished() {
	int passedTime = ofGetElapsedTimeMillis() - savedTime;
	if(passedTime > totalTime) {
		return true;
	} else {
		return false;
	}
}



	

