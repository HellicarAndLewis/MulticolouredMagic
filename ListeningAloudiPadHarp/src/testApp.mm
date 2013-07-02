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

	ofSetLogLevel(OF_LOG_VERBOSE);

	ofBackground(255, 255, 255);

	xmlgui::Resources::setFont("Arial.ttf", 12);
	
	centerer.setup(WIDTH, HEIGHT);
	setupGraphics();
	setupOrientation();
	
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

#else
//	setDataPathRootToAppContents(appName);

#endif
	
	
	ofSetFrameRate(60);
	sampler.init();
	

	ofSoundStreamSetup(2, 1, this, 44100, 512, 4);
	 
}


void testApp::setupGraphics() {
}

void testApp::setupOrientation() {
}

void testApp::updateOrientation() {
}


//--------------------------------------------------------------
void testApp::update(){
    sampler.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	sampler.draw();
	sampler.gui.draw();
	
}

//--------------------------------------------------------------
void testApp::exit(){
    
}

//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){
	
	sampler.audioRequested (output,bufferSize,nChannels);
	
}
void testApp::audioIn(float * output, int bufferSize, int nChannels){
	
	sampler.audioReceived(output,bufferSize,nChannels);
	
}


//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs & touch){
	sampler.mousePressed(touch.x, touch.y, touch.id);
	sampler.gui.touchDown(touch.id, touch.x, touch.y);
	
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs & touch){
	sampler.mouseDragged(touch.x, touch.y, touch.id);
	sampler.gui.touchMoved(touch.id, touch.x, touch.y);
}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs & touch){
	sampler.mouseReleased(touch.x, touch.y, touch.id);
	sampler.gui.touchUp(touch.id, touch.x, touch.y);
}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void testApp::touchCancelled(ofTouchEventArgs & touch){

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
