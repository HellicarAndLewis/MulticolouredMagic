/*
 *  TTFramework.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"
#include "ofxSimpleGuiToo.h"
#include "ofxOpenCv.h"
#include "MagicShapes.h"
#define VISION_WIDTH 640
#define VISION_HEIGHT 480
#define CAM_THRESHOLD 20
#define MAX_MOVEMENT 5000
#define MOVEMENT_FILTER 0.3f


class TTApp: public ofBaseApp {
public:
	
	// this is called every time the app is restarted
	virtual void init() {};
	
	virtual void touchDown(float x, float y, int touchId) {};
	virtual void touchMoved(float x, float y, int touchId) {};
	virtual void touchUp(float x, float y, int touchId) {};
	
    
    // if the mode has been changed, 
    virtual void modeChanged() {};
    
	virtual bool needsKinect() { return false; }
	
    
    void setMode(int mode) {
        this->mode = mode;
        modeChanged();
    }
    
	// how loud the sound is at the moment
	float volume;

	// the adjustable volume sensitivity
	float volumeThreshold;
	
	
    // how much camera movement there is
	float movement;

protected:
    int mode;
    
};