//
//  Catcher.cpp
//  Somability
//
//  Created by Marek Bereza on 24/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Catcher.h"
#include "constants.h"

void Catcher::setup() {
	box2d.init();
	box2d.setGravity(0, 20);
	box2d.createGround();
	box2d.setFPS(30.0);
}
void Catcher::update() {
	
	for(int i = 0; i < contourParts.size(); i++) {
		contourParts[i].destroy();
	}
	
	// remove any circles that aren't on screen anymore.
	for(int i = 0; i < circles.size(); i++) {
		ofVec2f pos =	circles[i].getPosition();
		
		if(pos.x<0 || pos.x>640 || pos.y>480) {
			circles[i].destroy();
			circles.erase(circles.begin()+i);
			i--;
		}
	}
	if(circles.size()<100 && ofRandom(0, 1)>0.6) {
		makeCircle();
	}
	contourParts.clear();
	contours.findContours(*threshImg, 60*60, HEIGHT*HEIGHT, 20, true);
	for(int i = 0; i < contours.blobs.size(); i++) {
		contourParts.push_back(ofxBox2dPolygon());
		for(int j = 0; j < contours.blobs[i].pts.size(); j+=2) {
			contourParts.back().addVertex(contours.blobs[i].pts[j].x, contours.blobs[i].pts[j].y);
		}
		contourParts.back().setPhysics(0, 0.5, 0.5);
		contourParts.back().create(box2d.getWorld());
	}
	
	box2d.update();
}

bool Catcher::touchDown(float x, float y, int touchId) {
	makeCircle();
}

void Catcher::makeCircle() {

		float r = ofRandom(4, 20);		// a random radius 4px - 20px
		ofxBox2dCircle circle;
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), ofRandom(40, 600), 0, r);
		circles.push_back(circle);
	
}
void Catcher::draw() {
	
	ofSetHexColor(0xFFFFFF);
	glPushMatrix();
	glScalef((float)WIDTH/colorImg->getWidth(), (float)HEIGHT/colorImg->getHeight(), 1);
	colorImg->draw(0, 0);
	contours.draw(0, 0);
	
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0x90d4e3);
		circles[i].draw();
	}

	
	
	glPopMatrix();
	//	printf("%d skelingtons\n", Skeletons::getInstance().size());
}
