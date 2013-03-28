/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "testApp.h"
#include "Skeletons.h"

bool flipX = true;
bool flipImage = false;
#include "Settings.h"

#ifndef TARGET_OF_IPHONE
#include "util.h"
#include "ofxSimpleGuiToo.h"

#else
#include <AVFoundation/AVFoundation.h>
#endif

//--------------------------------------------------------------
void testApp::setup(){
	setupApp(this, "Somability");
	ofSetFullscreen(false);
	Skeletons::getInstance().setOpenNI(&openNI);
	

	

	
	// just a regular setup
	
	openNI.setup();
    openNI.addDepthGenerator();
    openNI.addImageGenerator();
    openNI.setRegister(true);
    openNI.setMirror(true);
    openNI.addUserGenerator();
    openNI.setMaxNumUsers(4);
	openNI.setDepthColoring(COLORING_GREY);
    openNI.start();

	
	
	
	colorImg.allocate(640, 480);
	gui.addToggle("Flip Image", flipImage);
	gui.addToggle("Flip Camera", flipX);
	gui.addContent("camera", colorImg);
	depthImg.allocate(640, 480);
	gui.addContent("depth", depthImg);
	gui.addSlider("depth threshold", depthThreshold, 0, 255);
	threshImg.allocate(640, 480);
	gui.addContent("thresholded depth", threshImg);
	gui.loadFromXML();
	gui.setAutoSave(true);

	
	mainMenu = new MainMenu();
	currentApp = mainMenu;
	mainMenu->setup();
	
	blobTracker.addListener(this);
	
	backButton.setup("back", ofVec2f(0,0), IMAGE_ROOT + "backButton.png", IMAGE_ROOT + "backButtonDown.png");
	backButton.x = WIDTH - backButton.width;
	backButton.y = HEIGHT - backButton.height;
	backButton.setListener(this);
	backButton.setHoldMode(false);

	
	
}

void testApp::exit() {
	openNI.stop();
}

void testApp::showAbout() {
	
}

void testApp::showSettings() {
	
}


bool testApp::isReactickle(Reactickle *reactickle) {
	return reactickle!=mainMenu;
}




void testApp::buttonPressed(string name) {
	if(name=="back") {
		switchReactickle(mainMenu);
	}
}


void testApp::launchReactickle(Reactickle *reactickle) {
	switchReactickle(reactickle);
}

//--------------------------------------------------------------
void testApp::update(){

	openNI.update();
	if(currentApp!=NULL) {
		currentApp->volume = volume;
		currentApp->volumeThreshold = VOLUME_THRESHOLD;
		
		//#ifndef TARGET_IPHONE_SIMULATOR
		if(currentApp->needsKinect()) {
			

			unsigned char *pix = openNI.getImagePixels().getPixels();
			if(pix!=NULL) {
				colorImg.setFromPixels(openNI.getImagePixels().getPixels(), 640, 480);
#ifdef TARGET_OF_IPHONE
				colorImg.mirror(true, false);
#else
				colorImg.mirror(false, flipX);
#endif
				currentApp->colorImg = &colorImg;
#ifndef TARGET_OF_IPHONE
				unsigned char *dep = openNI.getDepthPixels().getPixels();
				unsigned char *d = depthImg.getPixels();
				for(int i = 0; i < 480*640; i++) {
					if(dep[i*4]==0) d[i] = 0; // this is really annoying, but the 
												// black unknowns of the kinect
												// turn up at the wrong end.
					else d[i] = 255-dep[i*4]; 
				}
				depthImg.setFromPixels(d, 640, 480);
				depthImg.mirror(false, flipX);
				// depthImg.invert();
				threshImg = depthImg;
				threshImg.threshold(depthThreshold);
				currentApp->depthImg = &depthImg;
				currentApp->threshImg = &threshImg;
				
				if(currentApp->needsKinectBlobs()) {
					contourFinder.findContours(threshImg, 40*40, 480*480,
											   10, false);
					vector<ofVec2f> blobs;
					for(int i = 0; i < contourFinder.blobs.size(); i++) {
						blobs.push_back(
										ofVec2f(contourFinder.blobs[i].centroid.x,
												contourFinder.blobs[i].centroid.y)/ofVec2f(VISION_WIDTH, VISION_HEIGHT));
					}
					blobTracker.track(blobs);
				}
#endif
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
	
	
	if(FAKE_GAME_MODE) centerer.begin();
	
	if(flipImage) {
		glPushMatrix();
		glScalef(-1, 1, 1);
		glTranslatef(-WIDTH, 0, 0);
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
	//	colorImg.draw(0, 0, WIDTH, HEIGHT);
	if(flipImage) {
		glPopMatrix();
	}
	
	if(FAKE_GAME_MODE) centerer.end();	
	
	// pops the pixel coordinates scaling stuff.
	if(RETINA) {
		glPopMatrix();
	}
//	openNI.drawDebug(0, 0);
#ifndef TARGET_OF_IPHONE
	gui.draw();
#endif
	ofEnableAlphaBlending(); // for gui stuff
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
#ifndef TARGET_OF_IPHONE
	switch(key) {
		case ' ': 
			gui.toggleDraw();
			if(gui.isOn()) {
				setEnabled(false);
			} else {
				setEnabled(true);
			}
			break;
		case 'f':
			ofToggleFullscreen();
			break;
	}
#endif

}


//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	WIDTH = w;
	HEIGHT = h;
	
	
	// hacky, but reposition backbutton if we go between
	// fullscreen and windowed.
	backButton.x = WIDTH - backButton.width;
	backButton.y = HEIGHT - backButton.height;
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


void testApp::blobEntered(ofVec3f pos, int blobId) {
	if(currentApp!=NULL && currentApp->needsKinectBlobs()) {
		currentApp->touchDown(pos.x*WIDTH, pos.y*HEIGHT, blobId);
	}
}


void testApp::blobMoved(ofVec3f pos, int blobId) {
	if(currentApp!=NULL && currentApp->needsKinectBlobs()) {
		currentApp->touchMoved(pos.x*WIDTH, pos.y*HEIGHT, blobId);
	}
}

void testApp::blobExited(ofVec3f pos, int blobId) {
	if(currentApp!=NULL && currentApp->needsKinectBlobs()) {
		currentApp->touchUp(pos.x*WIDTH, pos.y*HEIGHT, blobId);
	}
}