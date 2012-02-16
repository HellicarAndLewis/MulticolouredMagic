/**
 * ReactickleApp.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

#include "ReactickleApp.h"
#include "util.h"
#include "constants.h"
#include "MainMenu.h"

ReactickleApp *ReactickleApp::instance;

void ReactickleApp::setupApp(ReactickleApp *instance, string appName) {
	setEnabled(true);
	APP_NAME = appName;
	this->instance = instance;
	centerer.setup(WIDTH, HEIGHT);
	fadingOutReactickle = NULL;
	currentApp = NULL;
	gain = 1;
	crossFadeStartTime = -100;
//	volumeThreshold = 0.3;
	volume = 0;
	setupGraphics();
	setupOrientation();
#ifdef TARGET_OF_IPHONE
	// register touch events
	ofAddListener(ofEvents.touchDown, this, &ReactickleApp::touchDown);
	ofAddListener(ofEvents.touchMoved, this, &ReactickleApp::touchMoved);
	ofAddListener(ofEvents.touchUp, this, &ReactickleApp::touchUp);

	// initialize the accelerometer
	ofxAccelerometer.setup();

	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
#else
	setDataPathRootToAppContents(appName);
    setupOSC(); //osc too
//	webserver.start("htdocs/", 8080);
//	webserver.addHandler(this, "/action");
#endif

	ofSoundStreamSetup(0, 1, this, 44100, 1024, 1);
}

#ifndef TARGET_OF_IPHONE
void ReactickleApp::setupOSC(){
    // open an outgoing connection to HOST:PORT
    sender.setup( HOST, PORT );
}
string nextOneToLaunch = "";
/*void ReactickleApp::httpGet(string url) {
	printf("%s\n", url.c_str());
	httpRedirect("index.html?reactickle="+getRequestParameter("reactickle"));

	nextOneToLaunch = getRequestParameter("reactickle");
}*/
#endif



void ReactickleApp::drawCurrentReactickle() {
#ifndef TARGET_OF_IPHONE
	if(nextOneToLaunch!="") {
		((MainMenu*)mainMenu)->reactickleSelected(nextOneToLaunch);
		nextOneToLaunch = "";
	}
#endif
	float crossFadeTime = ofGetElapsedTimef() - crossFadeStartTime;

	// if we're crossfading do this:
	if(crossFadeTime<CROSS_FADE_TIME) {

		Reactickle *first = mainMenu;
		Reactickle *second = currentApp;

		// choose which way we're fading
		if(!fadingIn) {
			first = fadingOutReactickle;
			second = mainMenu;
		}
		// we want do draw the main menu fading out
		if(crossFadeTime<CROSS_FADE_TIME/2) {
			// fade out menu
			first->draw();
			ofSetColor(0, 0, 0, ofMap(crossFadeTime, 0, CROSS_FADE_TIME/2, 0, 255, true));
			ofRect(0, 0, WIDTH, HEIGHT);
		} else {
			// fade in app
			second->draw();
			ofSetColor(0, 0, 0, ofMap(crossFadeTime, CROSS_FADE_TIME/2, CROSS_FADE_TIME, 255, 0, true));
			ofRect(0, 0, WIDTH, HEIGHT);
		}


		// and then the app fading in


		// otherwise, just do this
	} else {
		currentApp->draw();

		// delete the last faded out reactickle
		// if it's finished fading out.
		if(fadingOutReactickle!=NULL) {
//			printf("deleting fading out reactickle\n");
			delete fadingOutReactickle;
			fadingOutReactickle = NULL;
		}
	}
}




void ReactickleApp::switchReactickle(Reactickle *reactickle) {



	// save for later
	Reactickle *lastApp = currentApp;

	if(currentApp!=NULL) {
		currentApp->stop();
	}
	// take care of previous reactickle - i.e. delete it if it's an actual reactickle
	if(isReactickle(currentApp)) {

		// just check the old one is actually deleted before reassigning.
		if(fadingOutReactickle!=NULL && isReactickle(fadingOutReactickle)) delete fadingOutReactickle;

		fadingOutReactickle = currentApp;
//		delete currentApp; - don't delete it yet, wait until it's faded out.
		currentApp = NULL;
	}


	// start the new one
	currentApp = reactickle;
	if(isReactickle(currentApp)) {
		currentApp->setup();
		backButton.setHoldMode(true);
		startCrossFade(true);
//		printf("it's a reactickle\n");
	} else if(currentApp==mainMenu) {

		// only crossfade if we're fading out of a reactickle
		if(
		   isReactickle(lastApp)
		   ) {
//			printf("Should be crossfading here\n");
			startCrossFade(false);
			backButton.setHoldMode(false);
		} else {
	//		printf("HERE\n");
		}
	} else {
		// not a reactickle or main menu
		backButton.setHoldMode(false);
//		printf("about or settings\n");
	}


	currentApp->start();
	if(isReactickle(currentApp)) {
#ifndef TARGET_OF_IPHONE
		ofxOscMessage m;
		m.setAddress( "/reacticklechange" );
		//m.addStringArg( reactickleNumber );
		ReactickleApp::instance->sender.sendMessage( m );
#endif
	}

}

void ReactickleApp::startCrossFade(bool fadeIn) {
	fadingIn = fadeIn;
	crossFadeStartTime = ofGetElapsedTimef();
}


#ifndef TARGET_OF_IPHONE


void ReactickleApp::mouseDragged(int x, int y, int button) {
	ofTouchEventArgs touch;
	touch.x = x;
	touch.y = y;
	touch.id = button;
	if(FAKE_GAME_MODE) centerer.transformMouse(touch.x, touch.y);
	this->touchMoved(touch);
}
void ReactickleApp::mousePressed(int x, int y, int button) {
	ofTouchEventArgs touch;
	touch.x = x;
	touch.y = y;
	touch.id = button;
	if(FAKE_GAME_MODE) centerer.transformMouse(touch.x, touch.y);
	this->touchDown(touch);
}
void ReactickleApp::mouseReleased(int x, int y, int button) {
	ofTouchEventArgs touch;
	touch.x = x;
	touch.y = y;
	touch.id = button;
	if(FAKE_GAME_MODE) centerer.transformMouse(touch.x, touch.y);
	this->touchUp(touch);
}




#endif


//--------------------------------------------------------------
void ReactickleApp::touchDown(ofTouchEventArgs &touch){
	float mult = RETINA?2:1;
	if(!enabled) return;
	if(currentApp!=mainMenu) {
		if(backButton.touchDown(touch.x*mult, touch.y*mult, touch.id)) {
			return;
		}
	}
#ifndef TARGET_OF_IPHONE
	if(isReactickle(currentApp)) {
		ofxOscMessage m;
		m.setAddress( "/touchdown" );
		//m.addIntArg(mode);
		ReactickleApp::instance->sender.sendMessage(m);
	}
#endif
	currentApp->touchDown(touch.x*mult, touch.y*mult, touch.id);
	this->buttonDown(touch.x*mult, touch.y*mult, touch.id);
}

//--------------------------------------------------------------
void ReactickleApp::touchMoved(ofTouchEventArgs &touch){
//	printf("Test");
	float mult = RETINA?2:1;
	if(!enabled) return;
	if(currentApp!=mainMenu) {
		if(backButton.touchMoved(touch.x*mult, touch.y*mult, touch.id)) {
			return;
		}
	}

#ifndef TARGET_OF_IPHONE
	if(isReactickle(currentApp)) {
		ofxOscMessage m;
		m.setAddress( "/touchmoved" );
		//m.addIntArg(mode);
		ReactickleApp::instance->sender.sendMessage(m);
	}
#endif
	currentApp->touchMoved(touch.x*mult, touch.y*mult, touch.id);

}

//--------------------------------------------------------------
void ReactickleApp::touchUp(ofTouchEventArgs &touch){
	float mult = RETINA?2:1;
	if(!enabled) return;
	if(currentApp!=mainMenu) {
		if(backButton.touchUp(touch.x*mult, touch.y*mult, touch.id)) {
			return;
		}
	}

#ifndef TARGET_OF_IPHONE
	if(isReactickle(currentApp)) {
		ofxOscMessage m;
		m.setAddress( "/touchup" );
		//m.addIntArg(mode);
		ReactickleApp::instance->sender.sendMessage(m);
	}
#endif
	currentApp->touchUp(touch.x*mult, touch.y*mult, touch.id);
	this->buttonUp(touch.x*mult, touch.y*mult, touch.id);
}

//--------------------------------------------------------------
void ReactickleApp::lostFocus(){

}

//--------------------------------------------------------------
void ReactickleApp::gotFocus(){

}

//--------------------------------------------------------------
void ReactickleApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ReactickleApp::deviceOrientationChanged(int newOrientation){

}
void ReactickleApp::setupGraphics() {
	ofEnableNormalizedTexCoords();
	ofBackground(0, 0, 0);
	ofSetFrameRate(30.f);
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
}


void ReactickleApp::updateOrientation() {
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


void ReactickleApp::audioReceived( float * input, int bufferSize, int nChannels ) {
	// samples are "interleaved"
	float max = 0;

	for (int i = 0; i < bufferSize; i++){
		float val = gain*ABS(input[i]);
		if(val>max) max = val;
	}

	if(max>volume) volume = max;
	else volume *= 0.96;

	if(currentApp!=NULL) {
		//volume *= gain;
		currentApp->audioReceived(input, bufferSize, nChannels);
	}
}


void ReactickleApp::exit(){
#ifdef TARGET_OF_IPHONE
	[[UIDevice currentDevice] endGeneratingDeviceOrientationNotifications];
#endif
}

void ReactickleApp::setupOrientation() {
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
