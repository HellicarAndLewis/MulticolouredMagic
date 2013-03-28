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
#endif

//#ifndef TARGET_IPHONE_SIMULATOR
#include "ofxOpenCv.h"
//#endif

#ifndef TARGET_OF_IPHONE
#include "ofxSimpleGuiToo.h"
#endif

#include "constants.h"
#include "Reactickle.h"
#include "MainMenu.h"
#include "ReactickleApp.h"
#include "HoldButton.h"
#include "ofxBlobTracker.h"
#include "ofxOpenNI.h"

class testApp : public ReactickleApp, public SimpleButtonListener, ofxBlobListener {

public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void blobEntered(ofVec3f pos, int blobId);
	void blobMoved(ofVec3f pos, int blobId);
	void blobExited(ofVec3f pos, int blobId);
		
	
	// app stuff
	void launchReactickle(Reactickle *reactickle);
	void showSettings();
	void showAbout();
	
	
	void keyPressed(int key);
	void keyReleased(int key);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);		

#ifdef USES_CAMERA
	ofxCvGrayscaleImage depthImg;
	ofxCvGrayscaleImage threshImg;
	ofxCvColorImage colorImg;
	ofxCvContourFinder contourFinder;
	
	float depthThreshold;
#endif
	bool hasCamera;
	
	// button event (for back button)
	void buttonPressed(string name);
	
protected:
	//#ifndef TARGET_IPHONE_SIMULATOR
	ofxOpenNI openNI;
	//#endif
	// true if fading into an app, false if fading out to the menu.
	
	bool isReactickle(Reactickle *reactickle);
	int currOrientation;
	
	ofxBlobTracker blobTracker;

};

