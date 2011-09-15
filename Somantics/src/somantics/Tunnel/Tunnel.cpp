#include "Tunnel.h"
#include "constants.h"
#define BRUSHED_LINE_SIZE 8
//--------------------------------------------------------------
void Tunnel::setup(){
	
	float w = WIDTH;
	float h = HEIGHT;
	Silhouette::setup();
	
	ofEnableNormalizedTexCoords();
	brushedLine.setup(ImageCache::getImage("img/blob.png"), BRUSHED_LINE_SIZE);
}

//--------------------------------------------------------------
void Tunnel::update(){ 
	// take the snapshots and make them bigger
	for(int i = 0; i < history.size(); i++) {
		ofVec2f centre;
		for(int k = 0; k < history[i].size(); k++) {
			centre += history[i][k];
		}
		centre /= history[i].size();
		float maxDistSquared = 0;
		for(int k = 0; k < history[i].size(); k++) {
			ofVec2f dist = history[i][k] - centre;
			dist.normalize();
			history[i][k] -= dist*10;
			float distSquared = centre.distanceSquared(history[i][k]);
			if(maxDistSquared<distSquared) {
				maxDistSquared = distSquared;
			}
		}
		if(maxDistSquared<400) {
			history.erase(history.begin()+i);
			i--;
		} 
		//printf("max dist: %f\n", maxDistSquared);
		
	}
}
int cc = 0;
//--------------------------------------------------------------
void Tunnel::draw(){
	ofBackground(150, 150, 150); // just to confirm we have something going on
	while(history.size()>20) {
		history.erase(history.begin());
	}
	
	ofSetHexColor(0xFFFFFF);
	for(int i = 0; i < history.size(); i++) {
		ofColor c;
		float h = ofMap(i, history.size()-40, history.size(), 0, 255, true);
		h = (history.size()-i)*15;
		c.setHsb(h, 255, 255);
		ofSetColor(c);
		brushedLine.drawLines(history[i], true);
	}
	
	for(int i = 0; i < silhouettes.size(); i++) {
		ofSetColor(255, 0, 0);
		silhouettes[i].draw();
		if(silhouettes[i].dead()) {
			silhouettes.erase(silhouettes.begin()+i);
			i--;
		} else {
			cc++;
			if(cc%3==0)
				history.push_back(silhouettes[i].getSnapshot());
		}
	}
}

bool Tunnel::touchDown(float x, float y, int touchId) {
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchDown(x,y,touchId)) {
			return true;
		}
	}
	silhouettes.push_back(Silhouette());
	silhouettes.back().setSize(BRUSHED_LINE_SIZE);
	silhouettes.back().touchDown(x, y, touchId);
	touches[touchId] = ofVec2f(x, y);
	return true;
}

bool Tunnel::touchUp(float x, float y, int touchId) {
	touches.erase(touchId);
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchUp(touchId)) {
			
			return true;
		}
	}
	return true;
}

bool Tunnel::touchMoved(float x, float y, int touchId) {
	touches[touchId].x = x;
	touches[touchId].y = y;
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchMoved(x, y, touchId)) {
			return true;
		}
	}
	return true;
}

