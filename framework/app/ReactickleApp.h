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
	
	virtual void setup();
	
#ifndef TARGET_OF_IPHONE
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
#endif
	
	virtual void touchDown(ofTouchEventArgs &touch);
	virtual void touchMoved(ofTouchEventArgs &touch);
	virtual void touchUp(ofTouchEventArgs &touch);
	
	
	void setupOrientation();
	void audioReceived( float * input, int bufferSize, int nChannels );
	void updateOrientation();
	void exit();
	void setupGraphics();
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