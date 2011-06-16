#include "Corridors.h"



//--------------------------------------------------------------
void Corridors::setup(){
	
	
	colors[0].setHex(0xFF0000);
	colors[1].setHex(0xFFFF00);
	colors[2].setHex(0xFF00FF);
	colors[3].setHex(0x0000FF);
	
	for(int i = 0; i < NUM_COLORS; i++) {
		colors[i].a = 50;
	}	
	

	
}

//--------------------------------------------------------------
void Corridors::update(){
}

//--------------------------------------------------------------
void Corridors::draw(){
	ofBackground(255);
	for(int i = 0; i < corridors.size(); i++) {
		ofSetColor(colors[i%NUM_COLORS]);
		corridors[i].draw();
		if(corridors[i].dead()) {
			corridors.erase(corridors.begin()+i);
			i--;
		}
	}
	/*
	ofSetHexColor(0);
	ofNoFill();
	map<int,ofVec2f>::iterator it;
	for(it = touches.begin(); it != touches.end(); it++) {
		ofCircle((*it).second.x, (*it).second.y, 10);
		ofDrawBitmapString(ofToString((*it).first), (*it).second);
	}
	ofFill();
	ofDrawBitmapString(ofToString(corridors.size()), 20, ofGetHeight()-20);*/
}


bool Corridors::touchDown(float x, float y, int touchId) {
	for(int i = 0; i < corridors.size(); i++) {
		if(corridors[i].touchDown(x,y,touchId)) {
			return true;
		}
	}
	corridors.push_back(Corridor());
	corridors.back().touchDown(x, y, touchId);
	touches[touchId] = ofVec2f(x, y);
	return true;
}

bool Corridors::touchUp(float x, float y, int touchId) {
	printf("Touch up\n");
	touches.erase(touchId);
	for(int i = 0; i < corridors.size(); i++) {
		if(corridors[i].touchUp(touchId)) {
			printf("Touch removed\n");
			return true;
		}
	}
	return true;	
//	printf("Touch Deleted: %d\n", touchId);
}

bool Corridors::touchMoved(float x, float y, int touchId) {
	touches[touchId].x = x;
	touches[touchId].y = y;
	for(int i = 0; i < corridors.size(); i++) {
		if(corridors[i].touchMoved(x, y, touchId)) {
			return true;
		}
	}
	return true;
}

