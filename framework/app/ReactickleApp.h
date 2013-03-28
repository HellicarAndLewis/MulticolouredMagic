/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/**
 * ReactickleApp.h
 * ReacticklesMagic
 *
 * This holds all the core functionality of the app,
 * accessible anywhere in the app. All the settings should
 * be here too.
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */
#pragma once

#include "ofMain.h"
#ifdef TARGET_OF_IPHONE
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#endif
#include "Reactickle.h"
#include "HoldButton.h"
#include "Centerer.h"

// how long it takes for the app to fade from one reactickle to another
#define	CROSS_FADE_TIME 2

//OSC things
#ifndef TARGET_OF_IPHONE
#include "ofxOsc.h"
//#include "ofxWebServer.h"
#endif

class ReactickleApp: 
#ifdef TARGET_OF_IPHONE
public ofxiPhoneApp 
#else
public ofBaseApp
//, public ofxWSRequestHandler
#endif

{
public:
	// call this in your reactickle app setup
	void setupApp(ReactickleApp *instance, string appName);
#ifndef TARGET_OF_IPHONE
    void setupOSC();
#endif    
	void exit();
	
	// these just redirect to touch events.
#ifndef TARGET_OF_IPHONE
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
//	ofxWebServer webserver;
//	void httpGet(string url);
#endif
	
	// these will redirect to explicit versions e.g. touchDown(float x, float y, int id);
	void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	
	void audioReceived( float * input, int bufferSize, int nChannels );
	
	void switchReactickle(Reactickle *reactickle);
	
	// stuff you have to override
	virtual void launchReactickle(Reactickle *reactickle) = 0;
	virtual void showSettings() = 0;
	virtual void showAbout() = 0;
	
	static ReactickleApp *instance;
	
	// - iphone specific stuff
	void lostFocus();
	void gotFocus();
	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);
	void setEnabled(bool enabled) { this->enabled = enabled; }

	// hack to make the mode up/dn buttons work.
	virtual void buttonDown(float x, float y, int id) {}; 
	virtual void buttonUp(float x, float y, int id) {}; 
#ifndef TARGET_OF_IPHONE
    //more osc fun
    ofxOscSender sender;
#endif    
protected:
	
	bool enabled;
	
	Centerer centerer;
	
	void setupGraphics();
	void setupOrientation();
	int currOrientation;
	void updateOrientation();
	
	
	// draws the current reactickle and takes 
	// care of fading in and out of reactickles
	void drawCurrentReactickle();
	
	// animates between reactickles
	void startCrossFade(bool fadeIn);
	float crossFadeStartTime;
	bool fadingIn;
	// this is the app that's currently fading out
	Reactickle *fadingOutReactickle;
	
	virtual bool isReactickle(Reactickle *reactickle) = 0;
	float gain;
	float volume;
	static const float VOLUME_THRESHOLD = 0.3;
	Reactickle *currentApp;
	Reactickle *mainMenu;
	
	// back buttons for when on a reactickle
	HoldButton backButton;
};