#include "Corridors.h"



//--------------------------------------------------------------
void Corridors::setup(){
	

	colors[0] = ofColor::fromHex(0x0E2356);
	colors[1] = ofColor::fromHex(0x4D1965);
	colors[2] = ofColor::fromHex(0xFFEC00);
	colors[3] = ofColor::fromHex(0x6D1B00);
	colors[4] = ofColor::fromHex(0xE50043);
	colors[5] = ofColor::fromHex(0x74AF27);	
	colors[6] = ofColor::fromHex(0xED6B06);
	
	
	for(int i = 0; i < NUM_COLORS; i++) {
		colors[i].a = 50;
	}	
	
	
#ifndef TARGET_OF_IPHONE
	tracker.addListener(this);
#endif
	
}

//--------------------------------------------------------------
void Corridors::update(){
#ifndef TARGET_OF_IPHONE
	contourFinder.findContours(*threshImg, 40*40, VISION_WIDTH*VISION_HEIGHT, 10, false);
	
	vector<ofVec3f> blobs;
	for(int i = 0; i < contourFinder.blobs.size(); i++) {
		blobs.push_back(ofVec3f(contourFinder.blobs[i].centroid.x/VISION_WIDTH, contourFinder.blobs[i].centroid.y/VISION_HEIGHT, contourFinder.blobs[i].boundingRect.width));
	}
	tracker.track(blobs);
	
	
#endif
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

