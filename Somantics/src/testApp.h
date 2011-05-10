#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "constants.h"
#include "Reactickle.h"
#include "MainMenu.h"
#include "SomanticsApp.h"
#include "DoubleTapButton.h"
#include "AboutPage.h"
#include "SettingsPage.h"

class testApp : public SomanticsApp, public SimpleButtonListener {
	
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
	
	void audioReceived( float * input, int bufferSize, int nChannels );
	
	void lostFocus();
	void gotFocus();
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
	DoubleTapButton backButton;

	// button event (for back button)
	void buttonPressed(string name);
	
private:
	bool isReactickle(Reactickle *reactickle);
	int currOrientation;
	
	void setupGraphics();
	void setupOrientation();
	void updateOrientation();


};


