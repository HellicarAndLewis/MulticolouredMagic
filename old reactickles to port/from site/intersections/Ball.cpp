/*
 *  Ball.cpp
 *  intersect
 *
 *  Created by Ben Jones on 07/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ball.h"

Ball::Ball() {
	
	// Set each ball up to have random colour, size,
	// starting location and speed
	color.r = ofRandom(0,255); color.g = ofRandom(0,255); color.b = ofRandom(0,255);
	position.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
	radius = ofRandom(10, 20);
	xspeed = ofRandom(0.01, 0.1);
	yspeed = ofRandom(0.01, 0.1);
}

void Ball::move() {
	position.x += xspeed;
	position.y += yspeed;
	
	// If beyond bounds of window, change direction
	if((position.x < 0 + radius/2) || (position.x > ofGetWidth() - radius/2)) {
		xspeed *= -1;
	}
	if((position.y < 0 + radius/2) || (position.y > ofGetHeight() - radius/2)) {
		yspeed *= -1;
	}
	
	
	
}

void Ball::display() {
	
	if(intersecting) {
		ofSetColor(color.r-20, color.g-20, color.b-20);
		intersecting = false;
	} else {
		ofSetColor(color.r, color.g, color.b);
	}
	//ofSetColor(color.r, color.g, color.b);
	ofEllipse(position.x, position.y, radius*2, radius*2);
}

bool Ball::intersect(Ball b) {
	float distance = ofDist(position.x, position.y, b.position.x, b.position.y);
	if(distance < radius + b.radius) {
		return true;
	} else {
		return false;
	}
}

void Ball::end() {
	position.x = ofGetWidth() + 100;
	xspeed = yspeed = 0;
}



