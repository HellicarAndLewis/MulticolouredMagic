/*
 *  Cascades.h
 *  SomanticsMac
 *
 *
 */

#include "ofMain.h"
#include "Reactickle.h"
#include "ofxBox2d.h"
#include "Reactickle.h"

//#define DEBUG

class Cascades : public Reactickle {
	
public:
	
	void setup();
	void update();
	void draw();
	
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	bool needsKinect() { return true; }
	
	void checkBlobs();
	
	vector<ofxBox2dCircle> circles;
	int waterfallLEdge, waterfallREdge;
	float radius;
	
	ofxBox2dPolygon			*bodyShape;
	ofxBox2d				box2d;
	
	
private:
	
	
	ofxCvColorImage			scaledImage;
	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;
	ofxCvColorImage			canvas;
	ofxCvContourFinder		contourFinder;
	
	void nextColour();
	
	int		threshold;
	float	amount;

};
