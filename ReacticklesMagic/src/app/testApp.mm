#include "testApp.h"
#include "MagicShapes.h"
#define BUTTON_PADDING 20
//--------------------------------------------------------------
void testApp::setup(){	
	
	
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
	
	ofSoundStreamSetup(0, 1, this, 22050, 1024, 1);
	aboutPage.setup();
	settingsPage.setup();
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
		currentApp->volume = volume;
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
#endif
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){
	if(currentApp!=&mainMenu) {
		if(backButton.touchDown(touch.x, touch.y, touch.id)) {
			return;
			
		} else {
			if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
				if(modeUpButton.touchDown(touch.x, touch.y, touch.id)) {
					return;
				} else if(modeDownButton.touchDown(touch.x, touch.y, touch.id)) {
					return;
				}
					
			}
		}
	}
	currentApp->touchDown(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
	if(currentApp!=&mainMenu) {
		if(backButton.touchMoved(touch.x, touch.y, touch.id)) {
			return;
		} else {
			if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
				if(modeUpButton.touchMoved(touch.x, touch.y, touch.id)) {
					return;
				} else if(modeDownButton.touchMoved(touch.x, touch.y, touch.id)) {
					return;
				}
			}
		}
	}
	currentApp->touchMoved(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){
	if(currentApp!=&mainMenu) {
		if(backButton.touchUp(touch.x, touch.y, touch.id)) {
			return;
		}  else {
			if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
				if(modeUpButton.touchUp(touch.x, touch.y, touch.id)) {
					return;
				} else if(modeDownButton.touchUp(touch.x, touch.y, touch.id)) {
					return;
				}
			}
		}
	}
	currentApp->touchUp(touch.x, touch.y, touch.id);
}

#ifndef TARGET_OF_IPHONE
void testApp::mousePressed(int x, int y, int button) {
	ofTouchEventArgs t;
	t.x = x;
	t.y = y;
	t.id = button;
	touchDown(t);
}

void testApp::mouseDragged(int x, int y, int button) {
	ofTouchEventArgs t;
	t.x = x;
	t.y = y;
	t.id = button;
	touchMoved(t);
}

void testApp::mouseReleased(int x, int y, int button) {
	ofTouchEventArgs t;
	t.x = x;
	t.y = y;
	t.id = button;
	touchUp(t);
}
#endif

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}


//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs& args){

}


void testApp::audioReceived( float * input, int bufferSize, int nChannels ) {
	// samples are "interleaved"
	float max = 0;
	
	for (int i = 0; i < bufferSize; i++){
		float val = gain*ABS(input[i]);
		if(val>max) max = val;
	}
	
	if(max>volume) volume = max;
	else volume *= 0.96;
	
	//volume *= gain;
	currentApp->audioReceived(input, bufferSize, nChannels);
}