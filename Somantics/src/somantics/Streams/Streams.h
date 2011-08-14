/*
 *  Streams.h
 *  SomanticsMac
 *
 *  Created by base on 14/08/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#include "ofMain.h"
#include "Reactickle.h"

class Streams : public Reactickle {
	
public:
	
	void setup();
	void update();
	void draw();
	
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	bool needsKinect() { return false; }
	
private:
		
	ofColor lColor, rColor;
	ofPolyline lLine, rLine;
	float lHue, rHue;
	
};