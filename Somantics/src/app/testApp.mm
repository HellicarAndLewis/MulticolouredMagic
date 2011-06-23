#include "testApp.h"
#include "MagicShapes.h"
#define	CROSS_FADE_TIME 2
//--------------------------------------------------------------
void testApp::setup(){
	ReactickleApp::instance = this;
	ReactickleApp::setup();
	
		
	kinect.setup();
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
		if(currentApp->needsKinect()) {
			kinect.update();
			//currentApp->colorPixels = kinect.getPixels();
			//currentApp->grayPixels = kinect.getDepthPixels();
		}
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
	

	
	
	float crossFadeTime = ofGetElapsedTimef() - crossFadeStartTime;
	
	// if we're crossfading do this:
	if(crossFadeTime<CROSS_FADE_TIME) {
		
		Reactickle *first = mainMenu;
		Reactickle *second = currentApp;
		
		// choose which way we're fading
		if(!fadingIn) {
			first = currentApp;
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
	}
	if(currentApp!=mainMenu) {
		backButton.draw();
	}
	// pops the pixel coordinates scaling stuff.
	if(RETINA) {
		glPopMatrix();
	}
	
}

bool testApp::isReactickle(Reactickle *reactickle) {
	return currentApp!=mainMenu && currentApp!=&aboutPage && currentApp!=&settingsPage;
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



