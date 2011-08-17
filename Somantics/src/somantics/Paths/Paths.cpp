#include "Paths.h"
#include "constants.h"
//--------------------------------------------------------------
void Paths::setup(){
	
	float w = WIDTH;
	float h = HEIGHT;
}

//--------------------------------------------------------------
void Paths::update(){
}

//--------------------------------------------------------------
void Paths::draw(){
	ofBackground(255,0,0); //just to confirm we have something going on
//	for(int i = 0; i < Paths.size(); i++) {
//		Paths[i].draw();
//	}
}

bool Paths::touchDown(float x, float y, int touchId) {
	touches[touchId] = ofVec2f(x, y);
	return true;
}

bool Paths::touchUp(float x, float y, int touchId) {
	touches.erase(touchId);
	return true;
}

bool Paths::touchMoved(float x, float y, int touchId) {
//	ofVec2f oldPos = touches[touchId];
	ofVec2f newPos = ofVec2f(x, y);
//	ofVec2f force = newPos-oldPos;
//	for(int i = 0; i < Paths.size(); i++) {
//		Paths[i].applyForce(newPos, force);
//	}
	touches[touchId] = newPos;
	return true;
}

