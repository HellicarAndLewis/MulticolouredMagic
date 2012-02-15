#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofBackground(255, 255, 255);
	
	ofSetFrameRate(60);
	
	for (int i=0; i<256; i++){
		array[i] = -200;
	}
}

//--------------------------------------------------------------
void testApp::update(){
	
	if(!state) array[lastposX] = lastposY;
//	if(ofGetFrameNum()%2==0)
	for (int i=0; i<256; i++){
		if(i>0){
			
			array[i-1] = array[i];
			
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 0, 0);
	ofSetLineWidth(1);
	
	for (int i=1; i<256; i++){
		//ofLine(i*U,array[i], i*U, ofGetHeight());
		
		ofFill();
		ofSetLineWidth(0.2);
		ofSetColor(255, array[i]/4, i*U/4, 100);
			ofCircle(i*U, array[i], i);
		
//		ofNoFill();
//		ofSetLineWidth(0.2);
//		ofSetColor(0, 0, 0);
//			ofCircle(i*U, array[i], i);
	}
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
	
	array[x/U] = y;
	
	
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	state = 1;
	array[x/U] = y;
	

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	state = 0;
	lastposY = y;
	lastposX = x/U;
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	U = ofGetScreenWidth()/200;
}

