/*
 *  Catcher.h
 *  intersect
 *
 *  Created by Ben Jones on 07/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _CATCHER
#define _CATCHER

#include "ofMain.h"
#include "Ball.h"

class Catcher {
	
public:
	
	float x, y, r;
	ofColor catcherColor;
	bool intersecting;
	
	Catcher();
	
	void setLocation(float, float); // No need for argument identifiers
	void display();
	bool intersect(Ball);
	
};

#endif


