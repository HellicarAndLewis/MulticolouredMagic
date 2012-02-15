#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	g = 100;
	aLength = 254;
	bLength = 254;
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(g,g,g);
	//ofBackground(bg(), bg(), bg());
	//ofBackground(mouseX/5, mouseY/3, mouseX+mouseY/4);
	
	// Draw a little thread trailing from the orbs
	for(int i = 0; i < aLength; i++) {
		ofLine(x[i], y[i], x[i+1], y[i+1]);
	}
	
	// Pop mouse coordinates at the end of the array
	x[aLength] = mouseX;
	y[aLength] = mouseY;
	
	// These are reveresed..
	x2[bLength] = mouseY;
	y2[bLength] = mouseX;
	
	// Move each element down one space
	for(int i = 0; i < aLength; i++) {
		x[i] = x[i+1];
		y[i] = y[i+1];
	   x2[i] = x2[i+1];
	   y2[i] = y2[i+1];
	}
	
	// Draw the array
	for(int i = 0; i < aLength; i++) {
		ofSetColor(mouseX/3, mouseY/2, i, i);
		ofCircle(x[i], y[i], i/5); // Original
		ofSetColor(mouseY/2, i, mouseX/3, i);
	    ofCircle(x2[i], y2[i], i/5); // Mirror
	}

	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	// Time stamp
	file = ofToString(ofGetYear()) + ofToString(ofGetMonth()) +  ofToString(ofGetDay()) +  " " + ofToString(ofGetHours()) +  ofToString(ofGetMinutes()) + ofToString(ofGetSeconds()) + ".png";
	
	if(key == 's') {
		ofSaveScreen(file);
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

int testApp::bg() {
	return g-mouseX/8;
}

