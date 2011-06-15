#include "Silhouettes.h"
#include "constants.h"



//--------------------------------------------------------------
void Silhouettes::setup(){
	//ofSetDataPathRoot(ofToDataPath("../SilhouetteDemo.app/Contents/"));

	Silhouette::setup();
	ofEnableNormalizedTexCoords();

	colors[0].setHex(0xFF0000);
	colors[1].setHex(0xFFFF00);
	colors[2].setHex(0xFF00FF);
	colors[3].setHex(0x0000FF);
	
	float w = WIDTH;
	float h = HEIGHT;
	
	//currFrame.setup(w, h);
	//histFrame.setup(w, h);
	
}
//--------------------------------------------------------------
void Silhouettes::update(){
}

bool histFrameCleared = false;
//--------------------------------------------------------------
void Silhouettes::draw(){
	ofBackground(255);
	
	//currFrame.begin();
	ofClear(0, 0, 0, 0);
	for(int i = 0; i < silhouettes.size(); i++) {
		ofSetColor(colors[i%NUM_COLORS]);
		silhouettes[i].draw();
		if(silhouettes[i].dead()) {
			silhouettes.erase(silhouettes.begin()+i);
			i--;
		}
	}
	//currFrame.end();
	/*histFrame.begin();
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
	 */
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


bool Silhouettes::touchDown(float x, float y, int touchId) {
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchDown(x,y,touchId)) {
			return true;
		}
	}
	silhouettes.push_back(Silhouette());
	silhouettes.back().touchDown(x, y, touchId);
	touches[touchId] = ofVec2f(x, y);
	return true;	
}

bool Silhouettes::touchUp(int touchId) {
	touches.erase(touchId);
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchUp(touchId)) {
			
			return true;
		}
	}
	return true;
//	printf("Touch Deleted: %d\n", touchId);
}

bool Silhouettes::touchMoved(float x, float y, int touchId) {
	touches[touchId].x = x;
	touches[touchId].y = y;
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchMoved(x, y, touchId)) {
			return true;
		}
	}
	return true;
}

