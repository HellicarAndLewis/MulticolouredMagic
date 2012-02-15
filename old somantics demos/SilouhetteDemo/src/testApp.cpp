#include "testApp.h"

#define NUM_COLORS 4
ofColor colors[NUM_COLORS];

//--------------------------------------------------------------
void testApp::setup(){
	//ofSetDataPathRoot(ofToDataPath("../SilhouetteDemo.app/Contents/"));
	bool fullscreen = true;
	Silhouette::setup();
	ofHideCursor();
	ofEnableNormalizedTexCoords();
	ofSetFullscreen(fullscreen);
	ofEnableAlphaBlending();
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	colors[0].setHex(0xFF0000);
	colors[1].setHex(0xFFFF00);
	colors[2].setHex(0xFF00FF);
	colors[3].setHex(0x0000FF);
	
	float w = fullscreen?ofGetScreenWidth():ofGetWidth();
	float h = fullscreen?ofGetScreenHeight():ofGetHeight();
	
	currFrame.setup(w, h);
	histFrame.setup(w, h);
		
	
	
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

bool histFrameCleared = false;
//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255);
	
	currFrame.begin();
	ofClear(0, 0, 0, 0);
	for(int i = 0; i < silhouettes.size(); i++) {
		ofSetColor(colors[i%NUM_COLORS]);
		silhouettes[i].draw();
		if(silhouettes[i].dead()) {
			silhouettes.erase(silhouettes.begin()+i);
			i--;
		}
	}
	currFrame.end();
	histFrame.begin();
	if(!histFrameCleared) {
		ofClear(0,0,0,0);
		histFrameCleared = true;
	}
	glColor4f(1,1,1, 0.02);
	
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
	
	glColor4ub(255, 255, 255, 200);
	currFrame.draw(0, 0);
	histFrame.end();
	glColor4f(1, 1, 1, 1);
	histFrame.draw(0, 0);
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
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchDown(x,y,touchId)) {
			return;
		}
	}
	silhouettes.push_back(Silhouette());
	silhouettes.back().touchDown(x, y, touchId);
	touches[touchId] = ofVec2f(x, y);
	
}

void testApp::touchUp(int touchId) {
	touches.erase(touchId);
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchUp(touchId)) {
			
			return;
		}
	}
	
//	printf("Touch Deleted: %d\n", touchId);
}

void testApp::touchMoved(float x, float y, int touchId) {
	touches[touchId].x = x;
	touches[touchId].y = y;
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchMoved(x, y, touchId)) {
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