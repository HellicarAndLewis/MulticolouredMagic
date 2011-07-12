//
//  Sparkles.h
//  SomanticsMac
//
//  Created by Marek Bereza on 11/07/2011.
//  Copyright 2011 MAZBOX LTD. All rights reserved.
//
#include "Reactickle.h"
#include "Sparticles.h"


class Sparkles : public Reactickle {

public:
	void setup();
	void update();
	void draw();
	
	
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	bool needsKinect() { return true; }
	
	
private:
	
	ofxCvColorImage			scaledImage;
	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;

	ofxCvContourFinder		contourFinder;
	
	Sparticles p;
	
	
	
	
	
	
	int		threshold;
	float	amount;
};
