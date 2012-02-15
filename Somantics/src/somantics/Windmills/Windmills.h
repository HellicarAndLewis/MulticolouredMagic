#pragma once

#include "ofMain.h"
#include "Windmill.h"
#include "Reactickle.h"
#ifndef TARGET_OF_IPHONE
#include "ofxCvOpticalFlowLK.h"
#endif
class Windmills : public Reactickle {

	public:
		void setup();
		void update();
		void draw();

		
	int toWindmillIndex(int x, int y);
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	
#ifndef TARGET_OF_IPHONE
	ofxCvOpticalFlowLK opticalFlow;
	bool needsKinect() { return true; }
	ofxCvGrayscaleImage grey;
	ofxCvGrayscaleImage curr;
	ofxCvGrayscaleImage prev;
	
#endif
	map<int,ofVec2f> touches;
	vector<Windmill> windmills;
	int windmillsX;
	int windmillsY;

};
