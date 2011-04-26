/*
 *  Catcher.cpp
 *  intersect
 *
 *  Created by Ben Jones on 07/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Catcher.h"

Catcher::Catcher() {
	r = 20;
}

void Catcher::setLocation(float x_, float y_) {
	x = x_;
	y = y_;
}

void Catcher::display() {
	if(intersecting) {
		ofSetColor(255, 255, 255);
		ofEllipse(x, y, r*2, r*2);
		intersecting = false;
	} else {
		catcherColor.r = x/3;
		catcherColor.g = y/3;
		catcherColor.b = x+y/4;
		ofSetColor(catcherColor.r, catcherColor.g, catcherColor.b);
		ofEllipse(x, y, r*2, r*2);
	}
	
}

bool Catcher::intersect(Ball b) {
	float distance = ofDist(x, y, b.position.x, b.position.y);
	if(distance < r + b.radius) {
		return true;
	} else {
		return false;
	}
}
	
	

