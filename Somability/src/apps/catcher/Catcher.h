//
//  Catcher.h
//  Somability
//
//  Created by Marek Bereza on 24/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Somability_Catcher_h
#define Somability_Catcher_h

#include "Reactickle.h"
#include "ofxBox2d.h"

class Catcher: public Reactickle {
	
public:
	
	
	void setup();
	void update();
	void draw();
	bool touchDown(float x, float y, int touchId);
	
	bool needsKinect() { return true; }
	
	ofxCvContourFinder contours;
	ofxBox2d box2d;
	vector<ofxBox2dPolygon> contourParts;
	vector		<ofxBox2dCircle>	circles;
	void makeCircle();
};


#endif
