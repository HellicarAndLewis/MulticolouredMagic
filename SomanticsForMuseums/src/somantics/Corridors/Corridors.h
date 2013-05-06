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

#pragma once

#include "ofMain.h"
#include "Corridor.h"
#include "Reactickle.h"

#ifndef TARGET_OF_IPHONE
#include "ofxBlobTracker.h"
#endif

class Corridors : public Reactickle 
#ifndef TARGET_OF_IPHONE
, public ofxBlobListener 
#endif

{

public:
	void setup();
	void update();
	void draw();
	const static int NUM_COLORS = 7;
	ofColor colors[NUM_COLORS];	
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	
	map<int,ofVec2f> touches;
	vector<Corridor> corridors;
	
#ifndef TARGET_OF_IPHONE
	ofxBlobTracker tracker;
	void blobEntered(ofVec3f pos, int blobId) { 
		touchDown(pos.x*WIDTH - pos.z/2, pos.y*HEIGHT, blobId); 
		touchDown(pos.x*WIDTH + pos.z/2, pos.y*HEIGHT, blobId+8192); 
	}
	void blobMoved(ofVec3f pos, int blobId) { 
		touchMoved(pos.x*WIDTH - pos.z/2, pos.y*HEIGHT, blobId); 
		touchMoved(pos.x*WIDTH + pos.z/2, pos.y*HEIGHT, blobId+8192); 
	}
	void blobExited(ofVec3f pos, int blobId) { 
		touchUp(pos.x*WIDTH - pos.z/2, pos.y*HEIGHT, blobId); 
		touchUp(pos.x*WIDTH + pos.z/2, pos.y*HEIGHT, blobId+8192); 
	}
	
	ofxCvContourFinder contourFinder;
	bool needsKinect() { return true; } 
#endif	
};
