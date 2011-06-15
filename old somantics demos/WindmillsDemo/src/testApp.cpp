#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	bool fullscreen = true;
	ofHideCursor();
	ofSetFullscreen(fullscreen);
	ofEnableAlphaBlending();
	ofSetFrameRate(40);
	
	ofSetVerticalSync(true);
	
	
	
	ofAddListener(touchPad.touchAdded, this, &testApp::touchAdded);
	ofAddListener(touchPad.touchRemoved, this, &testApp::touchRemoved);
	ofAddListener(touchPad.update, this, &testApp::touchesUpdated);
	windmillsX = 40;
	windmillsY = 35;
	float w = ofGetWidth();
	float h = ofGetHeight();
	if(fullscreen) {
		w = ofGetScreenWidth();
		h = ofGetScreenHeight();
	}
	for(int x = 0; x < windmillsX; x++) {
		for(int y = 0; y < windmillsY; y++) {
			windmills.push_back(Windmill());
			ofVec2f pos = ofVec2f((float)(x+1)*w/(float)(windmillsX+1), (float)(y+1)*h/(float)(windmillsY+1));
			if(y%2==0) {
				pos.x -= (float)w/((float)(windmillsX+1)*4.f);
			} else {
				pos.x += (float)w/((float)(windmillsX+1)*4.f);
			}
			windmills.back().pos = pos;
		}
	}
	
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
int testApp::toWindmillIndex(int x, int y) {
	return x*windmillsX + y;
}
//--------------------------------------------------------------
void testApp::update(){
	//flowField.update();
	/*for(int x = 1; x < windmillsX-1; x++) {
		for(int y = 1; y < windmillsY-1; y++) {
			
			windmills[toWindmillIndex(x, y)].rotationSpeed = (windmills[toWindmillIndex(x-1, y)].rotationSpeed
																	 + windmills[toWindmillIndex(x, y)].rotationSpeed 
																	 + windmills[toWindmillIndex(x+1, y)].rotationSpeed
																	 + windmills[toWindmillIndex(x, y-1)].rotationSpeed 
																	 + windmills[toWindmillIndex(x, y+1)].rotationSpeed)/5;
		}
	}*/
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255);
	
	
	for(int i = 0; i < windmills.size(); i++) {
		windmills[i].draw();
	}
	
	/*ofNoFill();
	map<int,ofVec2f>::iterator it;
	for(it = touches.begin(); it != touches.end(); it++) {
		ofCircle((*it).second.x, (*it).second.y, 10);
		ofDrawBitmapString(ofToString((*it).first), (*it).second);
	}
	ofFill();*/
}


void testApp::touchDown(float x, float y, int touchId) {
	touches[touchId] = ofVec2f(x, y);
	
}

void testApp::touchUp(int touchId) {
	touches.erase(touchId);
	
}

void testApp::touchMoved(float x, float y, int touchId) {
	ofVec2f oldPos = touches[touchId];
	ofVec2f newPos = ofVec2f(x, y);
	ofVec2f force = newPos-oldPos;
	printf("Force %f %f\n", force.x, force.y);
	for(int i = 0; i < windmills.size(); i++) {
		windmills[i].applyForce(newPos, force);
	}
	touches[touchId] = newPos;
	
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