#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	
	width = ofGetWidth();
	height = ofGetHeight();
	
	shape1.setup(250);
		
	sound[0].loadSound("1.wav");
	sound[1].loadSound("2.wav");
	sound[2].loadSound("3.wav");
	

	
	ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void testApp::update(){
	
	shape1.update(mX, mY);
	ofSoundUpdate();
}

//--------------------------------------------------------------
void testApp::draw(){
	//draw 3 bands
	
	ofSetColor(0, 0, 255);
	ofRect(0, 0, width/3, height);
	ofSetColor(0, 0, 0);
	ofRect(width/3, 0, width/3, height);
	ofSetColor(255, 0, 0);
	ofRect(width/3*2, 0, width/3, height);
	
	shape1.draw(mX, mY);
	
}

void testApp::playSample(){
	sound[shape1.getState()].play();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key=='f' || key=='F') ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	mX = x;
	mY = y;
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	playSample();
	mX = x;
	mY = y;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	width = ofGetWidth();
	height = ofGetHeight();
}

