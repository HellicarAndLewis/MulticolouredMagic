#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	backgroundColour = "white";
	
	ofBackground(255, 255, 255);
	
	squareX = 200;
	squareY = 200;
	squareWidth = 200;
	squareHeight = 200;
	
	circleX = 600;
	circleY = ofGetHeight() - 75;
}

//--------------------------------------------------------------
void testApp::update(){
	if(dragging) {
		circleX = mouseX + offsetX;
		circleY = mouseY + offsetY;
		
		if ((circleX - 75 < squareX + squareWidth) && circleX + 75 > squareX &&
			circleY - 75 < squareY + squareHeight && circleY + 75 > squareY) {
			while ((circleX - 75 < squareX + squareWidth) && circleX + 75 > squareX &&
				   circleY - 75 < squareY + squareHeight && circleY + 75 > squareY) {
				squareX = ofRandom(0, ofGetWidth() - squareWidth);
				squareY = ofRandom(0, ofGetHeight() - squareHeight);
			}
			
			if(backgroundColour == "white") {
				backgroundColour = "black";
				ofBackground(0, 0, 0);
			} else {
				backgroundColour = "white";
				ofBackground(255, 255, 255);
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0x0000FF);
	ofRect(squareX, squareY, squareWidth, squareHeight);
	ofSetColor(0xFF0000);
	ofEllipse(circleX, circleY, 150, 150);
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

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	if(getDistance(x, y, circleX, circleY) < 75) {
		offsetX = circleX - x;
		offsetY = circleY - y;
		dragging = true;
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	dragging = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

float testApp::getDistance(int startX, int startY, int endX, int endY) {
	return sqrt((endX - startX) * (endX - startX) + (endY - startY) * (endY - startY));
}