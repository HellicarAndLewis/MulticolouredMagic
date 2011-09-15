#include "Paths.h"
#include "constants.h"
#include "ImageCache.h"

//--------------------------------------------------------------
void Paths::setup(){
	
	float w = WIDTH;
	float h = HEIGHT;
	blob = ImageCache::getImage("img/blob.png");
	brushedLine.setup(blob, 20);
}

//--------------------------------------------------------------
void Paths::update(){
	ofVec2f offset(0, -10);
	// loop through touchToPath and add points to each path
	map<int, Path*>::iterator it;
	for(it = touchToPath.begin(); it != touchToPath.end(); it++) {
		int touchId = (*it).first;
		Path *path = (*it).second;
		path->addPoint(touches[touchId]);
	}

	for(int i = 0; i < paths.size(); i++) {
		paths[i]->update(offset);
		
		// work out if dead, and delete if so
		if(!paths[i]->isAlive()) {
			delete paths[i];
			paths.erase(paths.begin()+i);
			i--;
		}
	}
}

//--------------------------------------------------------------
void Paths::draw(){
	ofBackground(200,200, 200); //just to confirm we have something going on
	for(int i = 0; i < paths.size(); i++) {
		paths[i]->draw();
	}
	ofSetHexColor(0);
	map<int,ofVec2f>::iterator it;
	for(it = touches.begin(); it != touches.end(); it++) {
		blob->draw((*it).second.x-20, (*it).second.y-20, 40, 40);
	}
}

bool Paths::touchDown(float x, float y, int touchId) {
	
	// just create the paths
	touches[touchId] = ofVec2f(x, y);
	Path *p = new Path();
	
	// pick a random colour
	int colors [5] = {0xFF00FF, 0x00FF00, 0xFF0000, 0xFFFF00, 0x00FFFF};
	ofColor c;
	int i = ofRandom(0, 100);
	i %= 5;
	c.setHex(colors[i]);
	p->setDrawingStuff(&brushedLine, c);
	paths.push_back(p);
	touchToPath[touchId] = p;
	 
	return true;
}

bool Paths::touchUp(float x, float y, int touchId) {
	// just remove paths
	touches.erase(touchId);

	touchToPath.erase(touchId);
	return true;
}

bool Paths::touchMoved(float x, float y, int touchId) {
	ofVec2f newPos = ofVec2f(x, y);
	touches[touchId] = newPos;
	return true;
}

