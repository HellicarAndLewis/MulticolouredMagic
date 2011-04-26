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

	if(image.width==0) {
		image.loadImage("soft.png");
		image.setAnchorPercent(0.5, 0.5);
	}
	//
}
void Star::reset() {

	x = ofRandom(0, ofGetWidth());
	y = ofRandom(0, ofGetHeight());
	
	dx = 1.f/ofRandom(-5, 5);
	dy = 1.f/ofRandom(-5, 5);
	
	radius	= ofRandom(20, 80);

}

void Star::update() {

	x += dx;
	y += dy;
	
	dx *= 0.996;
	dy += 0.001f; 

	if(y>ofGetHeight()) {

		dy *= -1.0f;
	}
	if(y<0) {
		dy *= -1.0f;
	}
	

	if(x<0 || x>ofGetWidth()) dx *= -1.0f;

}
void Star::attract(int fx, int fy) {

	float distX = x - fx;
	float distY = y - fy;

	float dist = sqrt(distX*distX + distY*distY);

	distX *= -20.f/dist;
	distY *= -20.f/dist;

	dx = dx*0.9 + 0.1*distX;
	dy = dy*0.9 + 0.1*distY;
}
void Star::draw(int red, int green, int blue, int alpha) {
	alpha = 255;
	ofPushMatrix();

	ofSetColor(255, 255, 255, 30);
	ofLine(ofGetWidth()/2, ofGetHeight()/2, x, y);
	ofSetColor(255, 255, 255, 60);
	image.draw(x, y, radius*2, radius*2);

	ofPopMatrix();
	
}
