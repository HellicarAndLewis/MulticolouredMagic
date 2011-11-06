#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxBox2d.h"

#include "Reactickle.h"
#include "constants.h"

class Cascades : public Reactickle
{
	
public:
	
	void setup();
	void update();
	void draw();
	
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);

	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;
	
	bool needsKinect() { return true; } 
	ofxCvContourFinder 	contourFinder;
	
	ofxBox2dPolygon			*bodyShape;
	ofxBox2d				box2d;
	
	vector<ofxBox2dCircle> circles;
	int waterfallLEdge, waterfallREdge;
	float radius;
	
	bool debugging, contours;
	bool bLearnBakground;
	
	int		threshold;
	float	amount;	
	
	void checkBlobs();
	
	
};

