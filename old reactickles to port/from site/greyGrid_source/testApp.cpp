#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(255,255,255);
	
	stageWidth = ofGetWidth();
	stageHeight = ofGetHeight();
	maxDistance = ofDist(0, 0, stageWidth, stageHeight);
	
	ofEnableSmoothing();
}


//--------------------------------------------------------------
void testApp::draw(){
		
	int radius = 77;
	int diameter = radius * 2;
	
	for (int i = 0; i < NUM_COLS; i++) {
		for (int ii = 0; ii < NUM_ROWS; ii++) {
			float distColor = getDistance(mouseX - radius, mouseY - radius, i * diameter, ii * diameter);
			distColor = distColor / maxDistance * 100;
			ofSetColor(distColor * 5, distColor * 5, distColor * 5);
			ofEllipse(50 + radius + diameter * i, radius + diameter * ii, diameter, diameter);
		}
	}
}


float testApp::getDistance(int startX, int startY, int endX, int endY) {
	return sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));
}

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
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	stageWidth = w;
	stageHeight = h;	
}
