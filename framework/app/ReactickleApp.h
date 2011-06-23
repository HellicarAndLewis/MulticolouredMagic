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

class ReactickleApp: 
#ifdef TARGET_OF_IPHONE
public ofxiPhoneApp 
#else
public ofBaseApp
#endif

{
public:
	
	// call this in your reactickle app setup
	void setupApp(ReactickleApp *instance, string appName);
	void exit();
	
	// these just redirect to touch events.
#ifndef TARGET_OF_IPHONE
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
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
	
protected:
	
	void setupGraphics();
	void setupOrientation();
	int currOrientation;
	void updateOrientation();
	
	// animates between reactickles
	void startCrossFade(bool fadeIn);
	float crossFadeStartTime;
	bool fadingIn;
	
	virtual bool isReactickle(Reactickle *reactickle) = 0;
	float gain;
	float volume;
	float volumeThreshold;
	Reactickle *currentApp;
	Reactickle *mainMenu;
	// back buttons for when on a reactickle
	HoldButton backButton;


};