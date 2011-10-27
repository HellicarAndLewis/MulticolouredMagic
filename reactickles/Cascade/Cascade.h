/*
 *  Cascade.h
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */
#include "Reactickle.h"

#include "MagicShapes.h"
#include "constants.h"

class CascadeParticle {
public:
	
    
	CascadeParticle(float x, float y, float magnitude, ofColor _color, int _shape);	
	void update();
	
	void draw();
	bool isDead();

private:
	ofPoint pos;
	ofPoint vel;
	float birth;
	float age;
	ofColor color;
    int shape;
	
};


class Cascade: public Reactickle {
public:

	void start();	
	void setup();	
	void update();
	void draw();
	
	bool touchDown(float x, float y, int touchId);
	
	void audioReceived(float *input, int length, int nChannels);    
    int getNumModes() {
		return 3;
	}
    void modeChanged() {        
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        m.setAddress("/modechange");
        m.addIntArg( mode );
        ReactickleApp::instance->sender.sendMessage( m );
#endif
	}
	
private:
    ofPoint clapPoint;

	float clapThreshold;
	float magnitude;
	float lastClap;
	bool clapping;
	vector<CascadeParticle> particles;
    int currShapeId;
};