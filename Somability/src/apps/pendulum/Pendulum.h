//
//  Pendulum.h
//  Somability
//
//  Created by Marek Bereza on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Somability_Pendulum_h
#define Somability_Pendulum_h

#include "ofMain.h"
#include "Reactickle.h"
#include "ofxBox2d.h"
#include "Pendule.h"
class Pendulum: public Reactickle {
public:
	void start();
	void setup();
	void update();
	void draw();
	bool touchDown(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	
	map<int,Pendule> pendula;

	
	bool needsKinect() { return true; }
	ofxBox2d box2d;
};


#endif
