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

//--------------------------------------------------------------
void testApp::setup(){

	Pad::circle.loadImage("circle.png");
	Pad::circle.setAnchorPercent(0.5, 0.5);
	ofSetLogLevel(OF_LOG_VERBOSE);

	ofEnableAlphaBlending();
	ofBackground(0,0,0);
	
	centerer.setup(WIDTH, HEIGHT);
	setupGraphics();
	setupOrientation();
	xmlgui::Resources::setFont("Arial.ttf", 12);
	gui.gui.setAutoLayoutPadding(30);
#ifdef TARGET_OF_IPHONE
	ofxiPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	// register touch events
	ofAddListener(ofEvents().touchDown, this, &testApp::touchDown);
	ofAddListener(ofEvents().touchMoved, this, &testApp::touchMoved);
	ofAddListener(ofEvents().touchUp, this, &testApp::touchUp);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);

	gui.setup();
#else
//	setDataPathRootToAppContents(appName);

#endif
	float h = 140;
	float pad = 20;
	recMode.set(pad, ofGetHeight()-h - pad, h, h);
	recMode.setup("play|rec", Pad::recMode);
	
	ofSetFrameRate(60);
	ofSetCircleResolution(100);
	

	ofSoundStreamSetup(0, 1, this, 44100, 512, 4);
	setNumPads(3);
	
	

}


void testApp::setNumPads(int numPads) {
	if(numPads>11) numPads = 11;
	mutex.lock();
	gui.numPads = numPads;
	

	
	ofVec2f centre(ofGetWidth()/2, ofGetHeight()/2);
	
	float radius = ofGetHeight()/2;
	float dist = radius * 1.5;
	switch(numPads) {
		case 1:
			dist = 0;
			break;
		case 2:
			dist = ofGetWidth()/4;
			radius /= 1.6;
			break;
		case 3:
			dist = ofGetHeight()/3.5;
			radius /= 2.2;
			break;
		case 4:
			dist = ofGetHeight()/3.4;
			radius /= 2.75;
			break;
		case 5:
			dist = ofGetHeight()/3.2;
			radius /= 2.8;
			break;
		case 6:
			dist = ofGetHeight()/2.8;
			radius /= 2.9;
			break;
		case 7:
			dist = ofGetHeight()/2.82;
			radius /= 3.2;
			break;
		case 8:
			dist = ofGetHeight()/2.6;
			radius /= 3.4;
			break;
		case 9:
			dist = ofGetHeight()/2.7;
			radius /= 3.9;
			break;
		case 10:
			dist = ofGetHeight()/2.6;
			radius /= 4.1;
			break;
		case 11:
			dist = ofGetHeight()/2.6;
			radius /= 4.1;
			break;
	}
	
	
	// if there aren't enough, add here
	for(int i = pads.size(); i < numPads; i++) {
		pads.push_back(new Pad);
	}
	
	// if there's too many, remove
	while(pads.size()>numPads) {
		delete pads[pads.size()-1];
		pads.erase(pads.begin()+pads.size()-1);
	}
	
	
	for(int i = 0; i < pads.size(); i++) {
		float angle = ofMap(i, 0, numPads, 0, PI*2);
		if(pads.size()==8) {
			angle += PI*2/16.f;
		}
		ofVec2f offset(dist*cos(angle), dist*sin(angle));
		pads[i]->set(i, centre+offset,radius);
	}
	mutex.unlock();
}



void testApp::setupGraphics() {
}

void testApp::setupOrientation() {
}

void testApp::updateOrientation() {
}

bool lastMode = false;
//--------------------------------------------------------------
void testApp::update(){
	if(gui.numPads!=pads.size()) {
		setNumPads(gui.numPads);
	}
	
	if(lastMode!=Pad::recMode) {
		if(Pad::recMode) {
			ofSoundStreamStop();
			ofSoundStreamSetup(0, 1, this, 44100, 512, 4);
		} else {
			ofSoundStreamStop();
			ofSoundStreamSetup(2, 0, this, 44100, 512, 4);
		}
		if(Pad::recMode) {
			Pad::currRecId = -1;
		}
	}
	lastMode = Pad::recMode;
	
}

//--------------------------------------------------------------
void testApp::draw(){
	if(Pad::recMode) {
		ofClear(100,0,0,0);
	} else {
		ofClear(0, 0, 0, 0);
	}
	for(int i = 0; i < pads.size(); i++) {
		pads[i]->draw();
	}
	recMode.draw();
	gui.draw();

}

//--------------------------------------------------------------
void testApp::exit(){
    
}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
	memset(output, 0, bufferSize*nChannels*sizeof(float));
	mutex.lock();
	for(int i = 0; i < pads.size(); i++) {
		pads[i]->addSamples(output, bufferSize, nChannels);
	}

	mutex.unlock();
	
	
	// quieten
	int n = bufferSize * nChannels;
	float v = 1.f/pads.size();
	for(int i = 0; i < n; i++) {
		output[i] *= v;
	}
	//sampler.audioRequested (output,bufferSize,nChannels);
	
}
void testApp::audioIn(float * output, int bufferSize, int nChannels){
	if(Pad::recMode && Pad::currRecId!=-1) {
		mutex.lock();
		pads[Pad::currRecId]->recordSamples(output, bufferSize);
		mutex.unlock();
	}
	//sampler.audioReceived(output,bufferSize,nChannels);
	
}


//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
	gui.touchDown(touch.id, touch.x, touch.y);
	if(!gui.gui.isEnabled()) {
		for(int i = 0; i < pads.size(); i++) {
			pads[i]->touchDown(touch.x, touch.y, touch.id);
		}
		recMode.touchDown(touch.x, touch.y, touch.id);
	}
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
	gui.touchMoved(touch.id, touch.x, touch.y);
	if(!gui.gui.isEnabled()) {
		for(int i = 0; i < pads.size(); i++) {
			pads[i]->touchMoved(touch.x, touch.y, touch.id);
		}
	
		recMode.touchMoved(touch.x, touch.y, touch.id);
	}
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
	gui.touchUp(touch.id, touch.x, touch.y);
	
	if(!gui.gui.isEnabled()) {
		for(int i = 0; i < pads.size(); i++) {
			pads[i]->touchUp(touch.x, touch.y, touch.id);
		}
		
		recMode.touchUp(touch.x, touch.y, touch.id);
	}
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
	touchUp(touch);
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){
	touchUp(touch);
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



#ifndef TARGET_OF_IPHONE


void testApp::mouseDragged(int x, int y, int button) {
	ofTouchEventArgs touch;
	touch.x = x;
	touch.y = y;
	touch.id = button;
	if(FAKE_GAME_MODE) centerer.transformMouse(touch.x, touch.y);
	this->touchMoved(touch);
}
void testApp::mousePressed(int x, int y, int button) {
	ofTouchEventArgs touch;
	touch.x = x;
	touch.y = y;
	touch.id = button;
	if(FAKE_GAME_MODE) centerer.transformMouse(touch.x, touch.y);
	this->touchDown(touch);
}
void testApp::mouseReleased(int x, int y, int button) {
	ofTouchEventArgs touch;
	touch.x = x;
	touch.y = y;
	touch.id = button;
	if(FAKE_GAME_MODE) centerer.transformMouse(touch.x, touch.y);
	this->touchUp(touch);
}




#endif
