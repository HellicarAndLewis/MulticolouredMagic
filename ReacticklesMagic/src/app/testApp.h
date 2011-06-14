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
	void exit();
	
	void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);
	void touchCancelled(ofTouchEventArgs &touch);

#ifndef TARGET_OF_IPHONE	
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void keyPressed(int key);
#else
	virtual void gotFocus();
	virtual void lostFocus();
#endif
	
	void audioReceived( float * input, int bufferSize, int nChannels );
	

	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);

	// app stuff
	void launchReactickle(Reactickle *reactickle);
	void showSettings();
	void showAbout();
	

	void switchReactickle(Reactickle *reactickle);
	
	MainMenu mainMenu;
	AboutPage aboutPage;
	SettingsPage settingsPage;
	
	// this is the app that's currently receiving events
	Reactickle *currentApp;
	
	// back buttons for when on a reactickle
	HoldButton backButton;
	HoldButton modeUpButton;
	HoldButton modeDownButton;
	
	// button event (for back button)
	void buttonPressed(string name);
	
private:
	bool isReactickle(Reactickle *reactickle);
	int currOrientation;
	
	void setupGraphics();
	void setupOrientation();
	void updateOrientation();

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


