#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "constants.h"
#include "Reactickle.h"
#include "MainMenu.h"
#include "ReactickleApp.h"

class testApp : public ReactickleApp {
	
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

	void lostFocus();
	void gotFocus();
	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);

	void launchReactickle(Reactickle *reactickle);
	MainMenu mainMenu;
	
	// this is the app that's currently receiving events
	Reactickle *currentApp;
	
private:
	int currOrientation;
	
	void setupGraphics();
	void setupOrientation();
	void updateOrientation();
};


