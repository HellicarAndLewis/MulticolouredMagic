/*
 *  Ball.h
 *  intersect
 *
 *  Created by Ben Jones on 07/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _BALL
#define _BALL

#include "ofMain.h"

class Ball {

public:
	
	ofColor color;
	//int r, g, b;
	
	ofPoint position;
	//float x, y;
	
	float radius;
	float xspeed, yspeed;
	bool intersecting;
	
	Ball();
	
	void move();
	void display();
	bool intersect(Ball b);
	void end();

	
};

#endif

