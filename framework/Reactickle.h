/*
 *  TTFramework.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */



#pragma once
#include "ofConstants.h"
#include "ofMain.h"


#include "MagicShapes.h"

#ifndef TARGET_OF_IPHONE
	// this is what you get if you're not on iphone
	#include "ofxSimpleGuiToo.h"
	#include "ofxOpenCv.h"
	#define VISION_WIDTH 640
	#define VISION_HEIGHT 480
	#define CAM_THRESHOLD 20
	#define MAX_MOVEMENT 5000
	#define MOVEMENT_FILTER 0.3f
#endif

#include "Container.h"

class Reactickle: public Container {
public:
	
	// this is called every time the app is restarted
	virtual void start() {};
	virtual void stop() {};
	
	// called at the beginning of the app
	virtual void setup() {};
	
	// same as ofBaseApp
	virtual void update() {};
	
	virtual void keyPressed( int key ){}
	virtual void keyReleased( int key ){}
	
	virtual void mouseMoved( int x, int y ){}
	virtual void mouseDragged( int x, int y, int button ){}
	virtual void mousePressed( int x, int y, int button ){}
	virtual void mouseReleased(){}
	virtual void mouseReleased(int x, int y, int button ){}
	virtual void audioReceived( float * input, int bufferSize, int nChannels ){}
	virtual void audioRequested( float * input, int bufferSize, int nChannels ){}
    
    // if the mode has been changed, 
    virtual void modeChanged() {};
	
#ifndef TARGET_OF_IPHONE
	virtual bool needsKinect() { return false; }

    // how much camera movement there is
	float movement;
#endif
    
    void setMode(int mode) {
        this->mode = mode;
        modeChanged();
    }
    
	// how loud the sound is at the moment
	float volume;

	// the adjustable volume sensitivity
	float volumeThreshold;
	
	


protected:
    int mode;
    
};