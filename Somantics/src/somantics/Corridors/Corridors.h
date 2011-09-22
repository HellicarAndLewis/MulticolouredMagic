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
