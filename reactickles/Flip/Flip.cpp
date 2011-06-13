/**
 * Inversion.cpp
 * magic
 *
 * Created by Marek Bereza on 13/04/2011.
 *
 */

#include "Flip.h"

void Flip::start() {
	pos.push_back(ofGetWindowSize()/2);
	lastPos = pos.back();
	currShapeId = MAGIC_CIRCLE;
}
void Flip::draw() {
	int color1 = 0x000000;
	int color2 = 0xAAAAAA;
	

	if(pos.back().x>ofGetWidth()/2) {
		int t = color1;
		color1 = color2;
		color2 = t;
	}
	
	ofSetHexColor(color1);
	ofRect(0, 0, ofGetWidth()/2, ofGetHeight());
	
	ofSetHexColor(color2);
	ofRect(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());

	
	
//	for(int i = 0; i < pos.size(); i++) {
//		if((pos.size()-i)%2==1) ofSetHexColor(color1);
//		else ofSetHexColor(color2);
	
	ofSetHexColor(0xFFFFFF);
	drawShape(currShapeId, pos.back(), 400);
//	ofCircle(pos.back().x, pos.back().y, 200);

	
	while(pos.size()>100) {
		pos.pop_front();
	}
}

void Flip::update() {
	if(mode==0) {
		currShapeId = MAGIC_CIRCLE;
	} else {
	
		float w2 = ofGetWidth()/2;
		if((lastPos.x<w2 && pos.back().x>w2) || (lastPos.x>w2 && pos.back().x<w2)) {
			currShapeId++;
			currShapeId %= NUM_MAGIC_SHAPES;
		}
		
		lastPos = pos.back();
	}
}
bool Flip::touchDown(float x, float y, int touchId) {
	touches.push_back(FlipTouch(x, y, touchId));
	ofVec2f lastPos;
	if(pos.size()>0) {
		lastPos = pos.back();
	}
	pos.push_back((ofVec2f(x, y)*0.05+lastPos*0.95));
	return true;
}
bool Flip::touchMoved(float x, float y, int touchId) {
	ofVec2f lastPos;
	if(pos.size()>0) {
		lastPos = pos.back();
	}
	pos.push_back((ofVec2f(x, y)*0.05+lastPos*0.95));
	
	for(int i = 0; i < touches.size(); i++) {
		if(touchId==touches[i].touchId) {
			touches[i].x = x;
			touches[i].y = y;
			return true;
		}
	}
	return touchDown(x, y, touchId);
	
}
bool Flip::touchUp(float x, float y, int touchId) {
	for(int i = 0; i < touches.size(); i++) {
		if(touchId==touches[i].touchId) {
			touches.erase(touches.begin()+i);
			return true;
		}
	}
	return true;
}