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


// for now we comment this out for reactickles and include for somantics
#define USES_CAMERA

#ifdef USES_CAMERA
#include "ofxOpenCv.h"
	
	// this is what you get if you're not on iphone
//	#include "ofxSimpleGuiToo.h"
	//
	#define VISION_WIDTH 640
	#define VISION_HEIGHT 480
	#define CAM_THRESHOLD 20
	#define MAX_MOVEMENT 5000
	#define MOVEMENT_FILTER 0.3f
#endif

#include "Container.h"

class Reactickle: public Container {
public:
	string name;
	// this is called every time the reactickle is restarted
	virtual void start() {};
	virtual void stop() {};
	
	// called at the beginning of the app
	virtual void setup() {};
	
	// called when the app quits
	virtual void exit() {};
	
	// same as ofBaseApp
	virtual void update() {};
	
	// don't use these - I will remove them soon
	virtual void keyPressed( int key ){}
	virtual void keyReleased( int key ){}
	virtual void mouseMoved( int x, int y ){}
	virtual void mouseDragged( int x, int y, int button ){}
	virtual void mousePressed( int x, int y, int button ){}
	virtual void mouseReleased(){}
	virtual void mouseReleased(int x, int y, int button ){}
	virtual void audioReceived( float * input, int bufferSize, int nChannels ){}
	virtual void audioRequested( float * input, int bufferSize, int nChannels ){}
    virtual void windowResized(int x, int y) {} // probably won't be used.
	// end of don't use these's
	
	
	
    // if the mode has been changed, 
    virtual void modeChanged() {};
	
//#ifndef TARGET_OF_IPHONE
	virtual bool needsKinect() { return false; }
	virtual bool needsKinectBlobs() { return false; }
#ifdef USES_CAMERA
ofxCvColorImage *colorImg;		
#endif
    // how much camera movement there is
	float movement;
//#endif
#ifdef USES_CAMERA
	ofxCvGrayscaleImage *depthImg;
	ofxCvGrayscaleImage *threshImg;
#endif
    
    void setMode(int mode) {
        this->mode = mode;
        modeChanged();
    }
    
	int getMode() {
		return mode;
	}
	
	// you need to override this if you support more than one mode.
	virtual int getNumModes() {
		return 1;
	}
	// how loud the sound is at the moment
	float volume;

	// the adjustable volume sensitivity
	float volumeThreshold;
	
	
	ofImage *titleImage;

//protected:
    int mode;
    
};