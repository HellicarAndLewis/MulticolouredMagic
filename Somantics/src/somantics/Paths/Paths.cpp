/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Paths.h"
#include "constants.h"
#include "ImageCache.h"
#include "Settings.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif

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

