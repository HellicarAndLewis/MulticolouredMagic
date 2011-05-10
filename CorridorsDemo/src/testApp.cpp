#include "testApp.h"

#define NUM_COLORS 4
ofColor colors[NUM_COLORS];
//--------------------------------------------------------------
void testApp::setup(){
	
	ofHideCursor();
	ofSetFullscreen(true);
	ofEnableAlphaBlending();
	ofSetFrameRate(40);
	ofSetVerticalSync(true);
	colors[0].setHex(0xFF0000);
	colors[1].setHex(0xFFFF00);
	colors[2].setHex(0xFF00FF);
	colors[3].setHex(0x0000FF);
	
	for(int i = 0; i < NUM_COLORS; i++) {
		colors[i].a = 50;
	}	
	
	
	ofAddListener(touchPad.touchAdded, this, &testApp::touchAdded);
	ofAddListener(touchPad.touchRemoved, this, &testApp::touchRemoved);
	ofAddListener(touchPad.update, this, &testApp::touchesUpdated);
	
}

void testApp::touchAdded(MTouch &touch) {
	touchDown(touch.x*ofGetWidth(), touch.y*ofGetHeight(), touch.ID);
}

void testApp::touchRemoved(int &touchId) {
	touchUp(touchId);
}

void testApp::touchesUpdated(int &touchCount) {
	MTouch t;
	for(int i = 0; i < touchPad.getTouchCount(); i++) {
		touchPad.getTouchAt(i, &t);
		touchMoved(t.x*ofGetWidth(), t.y*ofGetHeight(), t.ID);
	}
}
//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255);
	for(int i = 0; i < corridors.size(); i++) {
		ofSetColor(colors[i%NUM_COLORS]);
		corridors[i].draw();
		if(corridors[i].dead()) {
			corridors.erase(corridors.begin()+i);
			i--;
		}
	}
	/*
	ofSetHexColor(0);
	ofNoFill();
	map<int,ofVec2f>::iterator it;
	for(it = touches.begin(); it != touches.end(); it++) {
		ofCircle((*it).second.x, (*it).second.y, 10);
		ofDrawBitmapString(ofToString((*it).first), (*it).second);
	}
	ofFill();
	ofDrawBitmapString(ofToString(corridors.size()), 20, ofGetHeight()-20);*/
}


void testApp::touchDown(float x, float y, int touchId) {
	for(int i = 0; i < corridors.size(); i++) {
		if(corridors[i].touchDown(x,y,touchId)) {
			return;
		}
	}
	corridors.push_back(Corridor());
	corridors.back().touchDown(x, y, touchId);
	touches[touchId] = ofVec2f(x, y);
	
}

void testApp::touchUp(int touchId) {
	touches.erase(touchId);
	for(int i = 0; i < corridors.size(); i++) {
		if(corridors[i].touchUp(touchId)) {
			
			return;
		}
	}
	
//	printf("Touch Deleted: %d\n", touchId);
}

void testApp::touchMoved(float x, float y, int touchId) {
	touches[touchId].x = x;
	touches[touchId].y = y;
	for(int i = 0; i < corridors.size(); i++) {
		if(corridors[i].touchMoved(x, y, touchId)) {
			return;
		}
	}
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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}