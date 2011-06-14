#include "MagicApp.h"
#include "stdio.h"
#include "util.h"


//--------------------------------------------------------------
void MagicApp::setup(){	
	
	// setup graphics
	mustTakeScreenshot = false;
	ofBackground(255,255,255);	
	ofSetVerticalSync(true);

	
	// setup apps
	appIndex = lastAppIndex = 0;
	initApps();
	
	for(int i = 0; i < apps.size(); i++) {
		apps[i]->setup();
	}
	
	
	apps[appIndex]->start();
	apps[appIndex]->setMode(0);


	// set up kinect
	kinect.setup();
	
	// set up tuio
	tuioClient.connect(3333);
	ofAddListener(ofEvents.touchDown, this, &MagicApp::touchDown);
	ofAddListener(ofEvents.touchUp, this, &MagicApp::touchUp);
	ofAddListener(ofEvents.touchMoved, this, &MagicApp::touchMoved);
	
	// setup sound
	gain = 1;
	volumeThreshold = 0.7;
	volume = 0;
	ofSoundStreamSetup(0,1,this, 44100, 256, 4);	
	
	setupGui();
	
	// open an outgoing connection to HOST:PORT
	sender.setup( HOST, PORT );
}

void MagicApp::setupGui() {
	
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

//--------------------------------------------------------------
void MagicApp::update() {
	
	if(gui.isOn()) {
		ofShowCursor();
	} else {
		ofHideCursor();
	}
	
	if(appIndex!=lastAppIndex) {
		gui.setPage(1);
		apps[appIndex]->start();
        apps[appIndex]->setMode(0);
	}
	lastAppIndex = appIndex;

	// send latest volume values to current app
	apps[appIndex]->volumeThreshold = volumeThreshold;
	apps[appIndex]->volume = volume;
	

	float startTime = ofGetElapsedTimef();
	kinect.update(apps[appIndex]->needsKinect());
//	printf("Vision time: %f\n", 1.f/(ofGetElapsedTimef()-startTime));
	apps[appIndex]->update();
}





//--------------------------------------------------------------
void MagicApp::draw() {
	ofBackground(0,0,0);
    apps[appIndex]->draw();
	
	// do the screenshot
	if(mustTakeScreenshot) {
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		string filename = getDesktopPath() + "/Magic-" + dateTimeString()+ ".jpg";
		
		screenshot.saveImage(filename);
		mustTakeScreenshot = false;
	}
	gui.draw();    
}



//--------------------------------------------------------------
void MagicApp::audioReceived(float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	float max = 0;

	for (int i = 0; i < bufferSize; i++){
		float val = gain*ABS(input[i]);
		if(val>max) max = val;
	}

	if(max>volume) volume = max;
	else volume *= 0.96;
	
	//volume *= gain;
	apps[appIndex]->audioReceived(input, bufferSize, nChannels);
	
}

void MagicApp::exit() {
	
	// stop the kinect
	kinect.exit();
	
	// unload everything.
	for(int i = 0; i < apps.size(); i++) {
		apps[i]->exit();
		delete apps[i];
	}
}
