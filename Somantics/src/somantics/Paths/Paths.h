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
#include "Reactickle.h"
#include "constants.h"
#include "BrushedLine.h"

class Path {
public:
	bool everHadPoints;
	Path() {
		everHadPoints = false;

	}
	void setDrawingStuff(BrushedLine *brushedLine, ofColor color) {
		this->color = color;
		this->brushedLine = brushedLine;
		
	}
	BrushedLine *brushedLine;
	ofColor color;
	
	vector<ofVec2f> points;
	
	void addPoint(ofVec2f p) {
		if(points.size()>0) {
			points.push_back((p+points.back())/2);
		} else {
			points.push_back(p);
		}
		everHadPoints = true;
	}
	
	bool isAlive() {
		return !(everHadPoints && points.size()==0);
	}
	
	void update(const ofVec2f &offset) {
		for(int i = 0; i < points.size(); i++) {
			points[i] += offset;
			// clear any points that aren't alive anymore
			int BORDER = 20; // we don't want to lose all vertices that are offscreen, or we'll get weird things happening
							 // at the edges, so we'll 
			if(points[i].x<0-BORDER || points[i].y<0-BORDER || points[i].x>WIDTH+BORDER || points[i].y>HEIGHT+BORDER) {
				points.erase(points.begin()+i);
				i--;
			}
			
		}
	
	}
	void draw() {
		ofSetColor(color);
		brushedLine->drawLines(points);
	}
		
};
#ifndef TARGET_OF_IPHONE
#include "ofxBlobTracker.h"
#endif

class Paths : public Reactickle
#ifndef TARGET_OF_IPHONE
, public ofxBlobListener 
#endif
{

public:
	void setup();
	void update();
	void draw();

	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);

	map<int,ofVec2f> touches;
	vector<Path*> paths;
	map<int, Path*> touchToPath;
	BrushedLine brushedLine;
	ofImage *blob;
	ofImage *finger;
	
#ifndef TARGET_OF_IPHONE
	ofxBlobTracker tracker;
	void blobEntered(ofVec3f pos, int blobId) { touchDown(pos.x*WIDTH, pos.y*HEIGHT, blobId); }
	void blobMoved(ofVec3f pos, int blobId) { touchMoved(pos.x*WIDTH, pos.y*HEIGHT, blobId); }
	void blobExited(ofVec3f pos, int blobId) { touchUp(pos.x*WIDTH, pos.y*HEIGHT, blobId); }
	
	ofxCvContourFinder contourFinder;
	bool needsKinect() { return true; } 
#endif	
};
