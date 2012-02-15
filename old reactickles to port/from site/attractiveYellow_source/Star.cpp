/*
 *  Star.cpp
 *  openFrameworks
 */

#include "Star.h"
ofImage Star::image;

Star::Star() {
	reset();
}
void Star::setup() {
	//font.loadFont("frabk.ttf", 12);

	if(image.width==0) {
		image.loadImage("leaf2.png");
		image.setAnchorPercent(0.5, 0.5);
	}
	//
}
void Star::reset() {
	
	// put the star in a random
	// place with a random speed,
	// a random radius, and a 
	// random colour
	x = ofRandom(0, ofGetWidth());
	y = ofRandom(0, ofGetHeight());
	
	dx = 1.f/ofRandom(-5, 5);
	dy = 1.f/ofRandom(-5, 5);
	
	radius	= ofRandom(20, 80);

}

void Star::update() {

	// increment the position by the speed
	x += dx;
	y += dy;

	
	// alter speeds to take into account
	// forces acting on the star
	
	dx *= 0.996; // air resistance
	dy += 0.0f; // gravity

	
	// have we hit the floor?
	if(y>ofGetHeight()) {
		// if so, bounce (invert the y speed)
		dy *= -1.0f;
	}
	if(y<0) {
		// if so, bounce (invert the y speed)
		dy *= -1.0f;
	}
	
	// same thing for the walls
	if(x<0 || x>ofGetWidth()) dx *= -1.0f;

}
void Star::attract(int fx, int fy) {

	// work out how far away the force is
	float distX = x - fx;
	float distY = y - fy;
	
	
	// work out the scalar distance of
	// how far the force is
	float dist = sqrt(distX*distX + distY*distY);
	
	// normalize the force, reverse it, times by 20
	
	distX *= -20.0f/dist;
	distY *= -20.0f/dist;
	
	// blend the current speed with
	// the new applied force from 
	// the attraction
	dx = dx*0.9 + 0.1*distX;
	dy = dy*0.9 + 0.1*distY;
}
void Star::draw(int red, int green, int blue, int alpha) {
	alpha = 255;//MAX(255 - age, 0);
	
	
	
	ofSetColor(red, green, blue, 200);
	ofPushMatrix();
	
	ofEllipse(x, y, 200, 200);
	//ofRotateZ(ofGetFrameNum()*0.1);
	//image.draw(x, y, radius, radius);
	//	ofSetColor(red, green, blue, 40);
	//image.draw(x, y, radius*5, radius*5);
	
	//font.drawString("word", x-20, y+5);
	ofPopMatrix();
	
}
