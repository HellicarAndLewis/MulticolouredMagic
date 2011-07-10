#include "testApp.h"
#include "MagicShapes.h"


#ifndef TARGET_OF_IPHONE
#include "util.h"
#endif

//--------------------------------------------------------------
void testApp::setup(){
	
	setupApp(this, "Somantics");
	
#ifndef TARGET_IPHONE_SIMULATOR
		
	kinect.setup();
#endif
	
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
		
#ifndef TARGET_IPHONE_SIMULATOR
		if(currentApp->needsKinect()) {
			kinect.update();
			//currentApp->colorPixels = kinect.getPixels();
			//currentApp->grayPixels = kinect.getDepthPixels();
		}
#endif
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
	
	// do the brightness control by just drawing a black rectangle over
	// the whole screen
	float alpha = ofMap(Settings::getInstance()->settings["brightness"], 0, 1, 0.6, 0);
	glColor4f(0, 0, 0, alpha);
	ofEnableAlphaBlending(); // reset blend func
	ofRect(0, 0, WIDTH, HEIGHT);
	
	
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



