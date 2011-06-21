#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Reactickle.h"



class Painter : public Reactickle {

public:
	void setup();
	void update();
	void draw();
	
	
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	bool needsKinect() { return true; }

	
private:
	ofVideoGrabber 		vidGrabber;
	

	ofxCvColorImage			colorImg;

	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;
	ofxCvColorImage			canvas;
	ofxCvContourFinder		contourFinder;

	void nextColour();
	
	int		threshold;
	float	amount;
	static const int NUM_PAINTER_COLOURS = 5;
	ofColor colours[NUM_PAINTER_COLOURS];
	int colourIndex;
};

