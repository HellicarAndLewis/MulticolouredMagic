#include "testApp.h"
#include "MagicShapes.h"


#ifndef TARGET_OF_IPHONE
#include "util.h"
#else
#include <AVFoundation/AVFoundation.h>
#endif

//--------------------------------------------------------------
void testApp::setup(){
	
	setupApp(this, "Somantics");

	printf("---------->>>>>>>>>><<<<<<<<<<<<<<<_----------------\n");
//#ifndef TARGET_IPHONE_SIMULATOR

#ifdef TARGET_OF_IPHONE
	
	// if we're ont the iphone, we want to double check there's a camera
	NSArray * devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
	if([devices count]>0) {
		//kinect.camera.listDevices();
		
		// front facing camera
		//kinect.camera.setDeviceID(2);

	
		kinect.setup();
		colorImg.allocate(kinect.getWidth(),kinect.getHeight());
		printf("Setting up camera %d %d\n", kinect.getWidth(), kinect.getHeight());
	} else {
		printf("No cameras available\n");
		hasCamera = false;
	}
#else 
	// just a regular setup
	kinect.setup();
	colorImg.allocate(kinect.getWidth(),kinect.getHeight());
#endif
//#endif
	
	mainMenu = new MainMenu();
	currentApp = mainMenu;
	mainMenu->setup();
	
	
	backButton.setup("back", ofVec2f(0,0), IMAGE_ROOT + "backButton.png", IMAGE_ROOT + "backButtonDown.png");
	backButton.x = WIDTH - backButton.width;
	backButton.y = HEIGHT - backButton.height;
	backButton.setListener(this);
	backButton.setHoldMode(false);
	
	aboutPage.setup();
	settingsPage.setup();
	
}



//--------------------------------------------------------------
void testApp::update(){
	updateOrientation();
	if(currentApp!=NULL) {
		currentApp->volume = volume;
		currentApp->volumeThreshold = volumeThreshold;
		
//#ifndef TARGET_IPHONE_SIMULATOR
		if(currentApp->needsKinect()) {
			
			kinect.update();
			unsigned char *pix = kinect.getPixels();
			if(pix!=NULL) {
				colorImg.setFromPixels(pix, kinect.getWidth(), kinect.getHeight());
#ifdef TARGET_OF_IPHONE
				colorImg.mirror(true, false);
#else
				colorImg.mirror(false, true);
#endif
				currentApp->colorImg = &colorImg;
			} else {
				currentApp->colorImg = NULL;
			}
		}
//#endif
		currentApp->update();
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	// if we're running on the retina display,
	// the openGL coordinates aren't pixel coordinates
	// (it's still 480x320 on a 960x640 iphone4 display)
	// so this scales the modelview so we can always use
	// pixel coordinates.
	if(RETINA) { 
		glPushMatrix();
		glScalef(0.5, 0.5, 1);
	}
	

	
	
	drawCurrentReactickle();
	
	if(currentApp!=mainMenu) {
		backButton.draw();
	}
	
	// do the brightness control by just drawing a black rectangle over
	// the whole screen
	float alpha = ofMap(Settings::getInstance()->settings["brightness"], 0, 1, 0.6, 0);
	glColor4f(0, 0, 0, alpha);
	ofEnableAlphaBlending(); // reset blend func
	ofRect(0, 0, WIDTH, HEIGHT);
	colorImg.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	
	// pops the pixel coordinates scaling stuff.
	if(RETINA) {
		glPopMatrix();
	}
	
}

bool testApp::isReactickle(Reactickle *reactickle) {
	return reactickle!=mainMenu && reactickle!=&aboutPage && reactickle!=&settingsPage;
}




void testApp::buttonPressed(string name) {
	if(name=="back") {
		switchReactickle(mainMenu);
	}
}


void testApp::launchReactickle(Reactickle *reactickle) {
	switchReactickle(reactickle);
}


void testApp::showAbout() {
	switchReactickle(&aboutPage);
}

void testApp::showSettings() {
	switchReactickle(&settingsPage);
}



