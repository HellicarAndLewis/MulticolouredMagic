#include "testApp.h"
#include "MagicShapes.h"

//--------------------------------------------------------------
void testApp::setup(){	
	gain = 1;
	ReactickleApp::instance = this;
	setupGraphics();
	setupOrientation();
	
	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
	currentApp = &mainMenu;
	mainMenu.setup();
	
	backButton.setup("back", ofVec2f(0,0), IMAGE_ROOT + "backButton.png", IMAGE_ROOT + "backButtonDown.png");
	backButton.x = WIDTH - backButton.width;
	backButton.y = HEIGHT - backButton.height;
	backButton.setListener(this);
	ofSoundStreamSetup(0, 1, this, 22050, 1024, 1);
}

void testApp::buttonPressed(string name) {
	if(name=="back") {
		currentApp = &mainMenu;
	}
}

void testApp::setupOrientation() {
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
}


void testApp::updateOrientation() {
	int orientation = [[UIDevice currentDevice] orientation];
	int orient = iPhoneGetOrientation();
	//printf("Phone orientation: %d, window orientation %d\n", orientation, orient);
	
	if(orientation!=currOrientation || orient==OFXIPHONE_ORIENTATION_PORTRAIT || orient==OFXIPHONE_ORIENTATION_UPSIDEDOWN) {
		if(orientation==UIDeviceOrientationLandscapeLeft) {
			iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
		} else if(orientation==UIDeviceOrientationLandscapeRight) {
			iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT);
		}
	}
	
	currOrientation = orientation;
}

void testApp::setupGraphics() {
	ofEnableNormalizedTexCoords();
	ofBackground(0, 0, 0);
	ofSetFrameRate(30.f);
	ofEnableAlphaBlending();
}
//--------------------------------------------------------------
void testApp::update(){
	updateOrientation();
	
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
	
//	ofCircle(WIDTH/2, HEIGHT/2, HEIGHT/2);
	//mainMenu.draw();
	currentApp->draw();
	if(currentApp!=&mainMenu) {
		backButton.draw();
	}
	// pops the pixel coordinates scaling stuff.
	if(RETINA) {
		glPopMatrix();
	}
	
}


void testApp::launchReactickle(Reactickle *reactickle) {

	currentApp = reactickle;
}

//--------------------------------------------------------------
void testApp::exit(){
	[[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];
}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch){
	if(currentApp!=&mainMenu) {
		if(backButton.touchDown(touch.x, touch.y, touch.id)) {
			return;
		}
	}
	currentApp->touchDown(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){
	if(currentApp!=&mainMenu) {
		if(backButton.touchMoved(touch.x, touch.y, touch.id)) {
			return;
		}
	}
	currentApp->touchMoved(touch.x, touch.y, touch.id);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){
	if(currentApp!=&mainMenu) {
		if(backButton.touchUp(touch.x, touch.y, touch.id)) {
			return;
		}
	}
	currentApp->touchUp(touch.x, touch.y, touch.id);
}

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

void testApp::showAbout() {
	currentApp = &aboutPage;
}

void testApp::showSettings() {
	currentApp = &settingsPage;
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