#pragma once

#include "ofMain.h"
#ifdef TARGET_OF_IPHONE
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#endif



//#ifndef TARGET_IPHONE_SIMULATOR
#include "ofxOpenCv.h"
//#endif

#include "KinectOrCamera.h"



#ifndef TARGET_OF_IPHONE
#include "ofxSimpleGuiToo.h"
#include "TuioKinect.h"
#include "ofxTuioClient.h"
#endif


#include "constants.h"
#include "Reactickle.h"
#include "MainMenu.h"
#include "ReactickleApp.h"
#include "HoldButton.h"
#include "AboutPage.h"
#include "SettingsPage.h"

class testApp : public ReactickleApp, public SimpleButtonListener {
	
public:
	void setup();
	void update();
	void draw();
	
	// app stuff
	void launchReactickle(Reactickle *reactickle);
	void showSettings();
	void showAbout();
	

	AboutPage aboutPage;
	SettingsPage settingsPage;
	
	ofVideoGrabber vidGrabber;
	ofxCvColorImage colorImg;
#ifndef TARGET_OF_IPHONE
	ofxCvGrayscaleImage depthImg;
	ofxCvGrayscaleImage threshImg;
	float depthThreshold;
#endif
	bool hasCamera;
	
	// button event (for back button)
	void buttonPressed(string name);
	
	void keyPressed(int key);
protected:
//#ifndef TARGET_IPHONE_SIMULATOR
	KinectOrCamera kinect;
//#endif
	// true if fading into an app, false if fading out to the menu.
	
	bool isReactickle(Reactickle *reactickle);
	int currOrientation;
};



