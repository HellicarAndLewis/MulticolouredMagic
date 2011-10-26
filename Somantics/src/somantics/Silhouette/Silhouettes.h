#pragma once

#include "ofMain.h"
#include "Silhouette.h"
#include "Reactickle.h"
#ifndef TARGET_OF_IPHONE
#define USE_FBO
#endif
// still can't get this to work!!!
//#ifdef TARGET_OF_IPHONE
//#include "ofxFBOTexture.h"
//#define ofFbo ofxFBOTexture
//#endif
//#endif
class Silhouettes : public Reactickle {

public:
	~Silhouettes();
	void setup();
	void update();
	void draw();

	void stop();
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
#ifndef TARGET_OF_IPHONE
	ofxCvContourFinder contourFinder;
	bool needsKinect() { return true; }
#endif
	
	map<int,ofVec2f> touches;
	vector<Silhouette> silhouettes;
	
	
#ifdef USE_FBO
	ofFbo *currFrame;
	ofFbo *histFrame;
#endif
};
