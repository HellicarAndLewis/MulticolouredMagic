#include "Paths.h"
#include "constants.h"
#include "ImageCache.h"
#include "Settings.h"
#include "ColorPicker.h"

//--------------------------------------------------------------
void Paths::setup(){
	
	blob = ImageCache::getImage("img/blob.png");
	finger = ImageCache::getImage("img/blob.png");
	brushedLine.setup(blob, 20);
	
#ifndef TARGET_OF_IPHONE
	tracker.addListener(this);
#endif
}


//--------------------------------------------------------------
void Paths::update(){
	
#ifndef TARGET_OF_IPHONE
	contourFinder.findContours(*threshImg, 20*20, VISION_WIDTH*VISION_HEIGHT, 10, false);
	
	vector<ofVec2f> blobs;
	for(int i = 0; i < contourFinder.blobs.size(); i++) {
		blobs.push_back(ofVec2f(contourFinder.blobs[i].centroid.x/VISION_WIDTH, contourFinder.blobs[i].centroid.y/VISION_HEIGHT));
	}
	tracker.track(blobs);
	
	
#endif
	
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
	
	ofFloatColor top(0.8, 0.8, 0.8);
	ofFloatColor bottom(0.4, 0.4, 0.4);
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);

	mesh.addColor(top);
	mesh.addVertex(ofVec2f(0, 0));
	mesh.addColor(top);
	mesh.addVertex(ofVec2f(WIDTH, 0));
	mesh.addColor(bottom);
	mesh.addVertex(ofVec2f(0, HEIGHT));
	mesh.addColor(bottom);
	mesh.addVertex(ofVec2f(WIDTH, HEIGHT));
	
	ofSetHexColor(0xFFFFFF);
	mesh.draw();
	
	for(int i = 0; i < paths.size(); i++) {
		paths[i]->draw();
	}
	
	ofSetHexColor(0);
	map<int,ofVec2f>::iterator it;
	for(it = touches.begin(); it != touches.end(); it++) {
		finger->draw((*it).second.x-20, (*it).second.y-20, 40, 40);
	}
}

bool Paths::touchDown(float x, float y, int touchId) {
	
	// just create the paths
	touches[touchId] = ofVec2f(x, y);
	Path *p = new Path();
	
	int colorIndex = Settings::getInstance()->settings["fgColor"];
	ofColor c;
	if(colorIndex==20) {
		// pick a random colour
		int colors [7] = {0x4D1965,
			0xE50043,
		0x0E2356,
		0x74AF27,
		0xFFEC00,
		0xED6B06,
		0x6D1B00};

		
		int i = ofRandom(0, 100);
		i %= 7;
		c.setHex(colors[i]);
	} else {
		c.setHex(ColorPicker::colors[colorIndex]);
	}
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

