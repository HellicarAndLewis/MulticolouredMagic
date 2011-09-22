#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	server.start("httpdocs");
	server.addHandler(this, "actions/*");
	color.r = 255;
	color.g = 255;
	color.b = 255;
}


void testApp::httpGet(string url) {
	string colorString = getRequestParameter("color");
	if(colorString=="red") {
		color.r = 255;
		color.g = 0;
		color.b = 0;
	} else if(colorString=="green") {
		color.r = 0;
		color.g = 255;
		color.b = 0;
	} else if(colorString=="blue") {
		color.r = 0;
		color.g = 0;
		color.b = 255;
	}
	httpResponse("Color value: " 
					+ ofToString(color.r) 
					+ " " + ofToString(color.g) 
					+ " " + ofToString(color.b));
}
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(color.r, color.g, color.b);
	ofRect(0,0,ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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

