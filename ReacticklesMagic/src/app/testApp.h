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

#pragma once

#include "ofMain.h"

#ifdef TARGET_OF_IPHONE

#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

#else

#include "ofxOpenCv.h"
#include "ofxSimpleGuiToo.h"
#include "TuioKinect.h"
#include "ofxTuioClient.h"
#include "ofxOsc.h"
#define HOST "localhost"
#define PORT 12345

#endif



#include "constants.h"
#include "Reactickle.h"
#include "MainMenu.h"
#include "ReactickleApp.h"
#include "HoldButton.h"
#include "AboutPage.h"
#include "SettingsPage.h"
#include "ModeDisplay.h"

class testApp : public ReactickleApp, public SimpleButtonListener {

public:
	void setup();
	void update();
	void draw();

	
	void buttonDown(float x, float y, int id);
	void buttonMoved(float x, float y, int id);
	void buttonUp(float x, float y, int id);

		
	// don't use these for now
	void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);


#ifndef TARGET_OF_IPHONE

	void keyPressed(int key);
	void tuioTouchDown(ofTouchEventArgs &touch);
	void tuioTouchMoved(ofTouchEventArgs &touch);
	void tuioTouchUp(ofTouchEventArgs &touch);


#endif


	// app stuff
	void launchReactickle(Reactickle *reactickle);
	void showSettings();
	void showAbout();


	AboutPage aboutPage;
	SettingsPage settingsPage;


	// back buttons for when on a reactickle
	HoldButton modeUpButton;
	HoldButton modeDownButton;

	// button event (for back button)
	void buttonPressed(string name);

private:
	bool isReactickle(Reactickle *reactickle);


	ModeDisplay modeDisplay;
#ifndef TARGET_OF_IPHONE
	ofxTuioClient tuioClient;
    ofxOscSender sender;
	ofxSimpleGuiToo gui;
	TuioKinect kinect;
	void setupGui();
	bool mustTakeScreenshot;
	ofImage screenshot;
#endif
};


