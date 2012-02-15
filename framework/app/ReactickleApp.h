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