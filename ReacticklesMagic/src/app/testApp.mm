#include "testApp.h"
#include "MagicShapes.h"
#define BUTTON_PADDING 5
#ifndef TARGET_OF_IPHONE
#include "util.h"

#endif
//--------------------------------------------------------------
void testApp::setup(){	

	setupApp(this, "ReacticklesMagic");
	
	modeDisplay.setup();


#ifndef TARGET_OF_IPHONE
	setupGui();
#endif
	
	mainMenu = new MainMenu();
	currentApp = mainMenu;
	mainMenu->setup();
	
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
	

	vector<ofxSimpleGuiPage*> pages = gui.getPages();
	string prefsDir = getPreferencesDirectory(APP_NAME);
	for(int i = 0; i < pages.size(); i++) {
		pages[i]->setXMLName(prefsDir+"/"+pages[i]->name + "_settings.xml");
	}
	
	gui.loadFromXML();
	gui.setAutoSave(true);
}


#endif

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
		
		// otherwise, just do this
	} else {
		currentApp->draw();
	}
	
	
	
	if(currentApp!=mainMenu) {
		backButton.draw();
		if(currentApp!=&aboutPage && currentApp!=&settingsPage) {
			modeUpButton.draw();
			modeDownButton.draw();
		}
	}
	if(isReactickle(currentApp)) {
		modeDisplay.draw();
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
	return currentApp!=mainMenu && currentApp!=&aboutPage && currentApp!=&settingsPage;
}
void testApp::buttonPressed(string name) {
	if(name=="back") {
		switchReactickle(mainMenu);
	} else if(name=="modeUp") {
		// increment mode
		if(isReactickle(currentApp)) {
			int newMode = currentApp->getMode();
			newMode++;
			if(newMode>=currentApp->getNumModes()) {
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


