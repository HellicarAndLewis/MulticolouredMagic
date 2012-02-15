/*
 *  Timer.h
 *  intersect
 *
 *  Created by Ben Jones on 07/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _TIMER
#define _TIMER

#include "ofMain.h"

class Timer {

public:
	
	int totalTime; // Length of timer
	int savedTime; // When timer began
	
	Timer();
	
	void start();
	bool finished();
	
};

#endif
