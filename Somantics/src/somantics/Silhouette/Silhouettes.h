#pragma once

#include "ofMain.h"
#include "Silhouette.h"
#include "Reactickle.h"
#ifndef TARGET_OF_IPHONE
#define USE_FBO
#endif
class Silhouettes : public Reactickle {

public:
	void setup();
	void update();
	void draw();

	const static int NUM_COLORS = 4;
	ofColor colors[NUM_COLORS];
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	
	
	map<int,ofVec2f> touches;
	vector<Silhouette> silhouettes;
	
	
#ifdef USE_FBO
	ofFbo currFrame;
	ofFbo histFrame;
#endif
};
