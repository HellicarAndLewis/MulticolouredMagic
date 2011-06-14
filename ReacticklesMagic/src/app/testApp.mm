#include "testApp.h"
#include "MagicShapes.h"
#define BUTTON_PADDING 20
#ifndef TARGET_OF_IPHONE
#include "util.h"

#endif
//--------------------------------------------------------------
void testApp::setup(){	

#ifndef TARGET_OF_IPHONE
	char path[512];
	getcwd(path, 512);
	string dataRoot = path;
	dataRoot += "/../data/";
	ofSetDataPathRoot(dataRoot);
	setupGui();
#endif
	
	modeDisplay.setup();
	gain = 1;
	volumeThreshold = 0.3;
	ReactickleApp::instance = this;
	setupGraphics();
	setupOrientation();
#ifdef TARGET_OF_IPHONE
	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	//==--
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
#endif
	currentApp = &mainMenu;
	mainMenu.setup();
	
	backButton.setup("back", ofVec2f(0,0), IMAGE_ROOT + "backButton.png", IMAGE_ROOT + "backButtonDown.png");
	backButton.x = BUTTON_PADDING;
	backButton.y = HEIGHT - backButton.height - BUTTON_PADDING;
	backButton.setListener(this);
	backButton.setHoldMode(false);
	
	
	modeUpButton.setup("modeUp", ofVec2f(0,0), IMAGE_ROOT + "modeUpButton.png", IMAGE_ROOT + "modeUpButtonDown.png");
	modeDownButton.setup("modeDown", ofVec2f(0,0), IMAGE_ROOT + "modeDownButton.png", IMAGE_ROOT + "modeDownButtonDown.png");
	
	modeUpButton.x = WIDTH - modeUpButton.width - BUTTON_PADDING;
	modeUpButton.y = BUTTON_PADDING;
	
	modeDownButton.x = WIDTH - modeDownButton.width - BUTTON_PADDING;
	modeDownButton.y = HEIGHT - modeDownButton.height - BUTTON_PADDING;
	
	modeUpButton.setListener(this);
	modeDownButton.setListener(this);
	
	modeUpButton.setHoldMode(true);
	modeDownButton.setHoldMode(true);
	
	ofSoundStreamSetup(0, 1, this, 44100, 1024, 1);
	aboutPage.setup();
	settingsPage.setup();
	
#ifndef TARGET_OF_IPHONE
	// set up kinect
	kinect.setup();
	
	// set up tuio
	tuioClient.connect(3333);
	ofAddListener(ofEvents.touchDown, this, &testApp::tuioTouchDown);
	ofAddListener(ofEvents.touchUp, this, &testApp::tuioTouchUp);
	ofAddListener(ofEvents.touchMoved, this, &testApp::tuioTouchMoved);
	
#endif	
}



void testApp::setupOrientation() {
	#ifdef TARGET_OF_IPHONE
	[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
	
	int orientation = [[UIDevice currentDevice] orientation];
	
	
	if(orientation==UIDeviceOrientationLandscapeLeft) {
		iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	} else if(orientation==UIDeviceOrientationLandscapeRight) {
		iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
	} else { // default
		iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
	}
	
	currOrientation = UIDeviceOrientationPortrait;	
#endif
}
#ifndef TARGET_OF_IPHONE
void testApp::setupGui() {
	
	gui.addSlider("Threshold", kinect.threshold, 0, 255);
	gui.addSlider("Far clipping", kinect.farClip, 0, 255);
	gui.addSlider("blend amount", kinect.blendAmount, 0.01, 0.2);
	
	
	gui.addTitle("SOUND");
	gui.addSlider("Sound Meter", volume, 0, 1);
	gui.addSlider("Sound input volume", gain, 0, 3);
	gui.addSlider("Volume Sensitivity", volumeThreshold, 0, 1);
	

	gui.addTitle("KINECT");
	gui.addToggle("Flip X", kinect.flipX);
	gui.addToggle("Flip Y", kinect.flipY);
	gui.addContent("Camera image", kinect.colorImage);
	gui.addContent("Depth image", kinect.depthImage);
	gui.addContent("Thresholded image", kinect.grayImage);
	gui.addContent("Bg image", kinect.bgImage);
	gui.addContent("Blobs", kinect.contourFinder);
	
	gui.setDraw(false);
	gui.loadFromXML();
	gui.setAutoSave(true);
}


#endif

void testApp::updateOrientation() {
#ifdef TARGET_OF_IPHONE
	int orientation = [[UIDevice currentDevice] orientation];
	int orient = iPhoneGetOrientation();
	//printf("Phone orientation: %d, window orientation %d\n", orientation, orient);
	
	if(orientation!=currOrientation || orient==OFXIPHONE_ORIENTATION_PORTRAIT || orient==OFXIPHONE_ORIENTATION_UPSIDEDOWN) {
		if(orientation==UIDeviceOrientationLandscapeLeft) {
			iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
		} else if(orientation==UIDeviceOrientationLandscapeRight) {
			iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
		}
	}
	
	currOrientation = orientation;
#endif
}

void testApp::setupGraphics() {
	ofEnableNormalizedTexCoords();
	ofBackground(0, 0, 0);
	ofSetFrameRate(30.f);
	ofEnableAlphaBlending();
	ofSetCircleResolution(64);
#ifndef TARGET_OF_IPHONE
	ofSetVerticalSync(true);
#endif
}
//--------------------------------------------------------------
void testApp::update(){
	updateOrientation();
	if(currentApp!=NULL) {
		gain = Settings::getInstance()->settings["volume"];
#ifndef TARGET_OF_IPHONE	
		kinect.update(currentApp->needsKinect());
#endif
		currentApp->volume = volume*gain;
		currentApp->volumeThreshold = volumeThreshold;
		currentApp->update();
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	
	
	// this is more to reset the blend mode
	ofEnableAlphaBlending();
	// if we're running on the retina display,
	// the openGL coordinates aren't pixel coordinates
	// (it's still 480x320 on a 960x640 iphone4 display)
	// so this scales the modelview so we can always use
	// pixel coordinates.
	if(RETINA) { 
		glPushMatrix();
		glScalef(0.5, 0.5, 1);
	}
	
//	ofCircle(WIDTH/2, HEIGHT/2, HEIGHT/2);
	//mainMenu.draw();
	currentApp->draw();
	if(currentApp!=&mainMenu) {
		backButton.draw();
		if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
			modeUpButton.draw();
			modeDownButton.draw();
		}
	}
	if(isReactickle(currentApp)) {
		modeDisplay.draw();
	}
	// pops the pixel coordinates scaling stuff.
	if(RETINA) {
		glPopMatrix();
	}
	
#ifndef TARGET_OF_IPHONE
	// do the screenshot
	if(mustTakeScreenshot) {
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		string filename = getDesktopPath() + "/Magic-" + dateTimeString()+ ".jpg";
		
		screenshot.saveImage(filename);
		mustTakeScreenshot = false;
	}
	gui.draw(); 
#endif
}

bool testApp::isReactickle(Reactickle *reactickle) {
	return currentApp!=&mainMenu && currentApp!=&aboutPage && currentApp!=&settingsPage;
}

void testApp::switchReactickle(Reactickle *reactickle) {
	if(currentApp!=NULL) {
		currentApp->stop();
	}
	// take care of previous reactickle - i.e. delete it if it's an actual reactickle
	if(isReactickle(currentApp)) {
		delete currentApp;
		currentApp = NULL;
	}
	
	// start the new one
	currentApp = reactickle;
	if(isReactickle(currentApp)) {
		backButton.setHoldMode(true); // make the back button require a hold
		currentApp->setup();
	} else {
		backButton.setHoldMode(false); // let the back button just work normally
	}
	currentApp->start();

}

void testApp::buttonPressed(string name) {
	if(name=="back") {
		switchReactickle(&mainMenu);
	} else if(name=="modeUp") {
		// increment mode
		if(isReactickle(currentApp)) {
			int newMode = currentApp->getMode();
			newMode++;
			if(newMode>currentApp->getNumModes()) {
				newMode = 0;
			}
			currentApp->setMode(newMode);
			modeDisplay.setMode(newMode);
		}
	} else if(name=="modeDown") {
		// decrement mode
		if(isReactickle(currentApp)) {
			int newMode = currentApp->getMode();
			newMode--;
			if(newMode<0) {
				newMode = currentApp->getNumModes()-1;
			}
			currentApp->setMode(newMode);
			modeDisplay.setMode(newMode);
		}
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



//--------------------------------------------------------------
void testApp::exit(){
#ifdef TARGET_OF_IPHONE
	[[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];
#else 
	// stop the kinect
	kinect.exit();
#endif
}



void testApp::audioReceived( float * input, int bufferSize, int nChannels ) {
	// samples are "interleaved"
	float max = 0;
	
	for (int i = 0; i < bufferSize; i++){
		float val = ABS(input[i]);
		if(val>max) max = val;
	}
	
	if(max>volume) volume = max;
	else volume *= 0.96;
	
	volume *= gain;
	currentApp->audioReceived(input, bufferSize, nChannels);
}


