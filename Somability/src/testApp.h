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

