#include "Tunnel.h"
#include "constants.h"

//--------------------------------------------------------------
void Tunnel::setup(){
	
	float w = WIDTH;
	float h = HEIGHT;
}

//--------------------------------------------------------------
void Tunnel::update(){
}

//--------------------------------------------------------------
void Tunnel::draw(){
	ofBackground(0,0,255); //just to confirm we have something going on
//	for(int i = 0; i < Tunnel.size(); i++) {
//		Tunnel[i].draw();
//	}
}

bool Tunnel::touchDown(float x, float y, int touchId) {
	touches[touchId] = ofVec2f(x, y);
	return true;
}

bool Tunnel::touchUp(float x, float y, int touchId) {
	touches.erase(touchId);
	return true;
}

bool Tunnel::touchMoved(float x, float y, int touchId) {
//	ofVec2f oldPos = touches[touchId];
	ofVec2f newPos = ofVec2f(x, y);
//	ofVec2f force = newPos-oldPos;
//	for(int i = 0; i < Tunnel.size(); i++) {
//		Tunnel[i].applyForce(newPos, force);
//	}
	touches[touchId] = newPos;
	return true;
}

