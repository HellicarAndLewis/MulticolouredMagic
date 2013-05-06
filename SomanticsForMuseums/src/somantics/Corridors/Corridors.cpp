/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

