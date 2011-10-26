#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxBox2d.h"

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
// otherwise, we'll use a movie file

//#define DEBUG

class Cascades : public ofBaseApp{
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);		
	

	ofVideoGrabber 		vidGrabber;
	ofxCvColorImage			colorImg;
	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;
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

