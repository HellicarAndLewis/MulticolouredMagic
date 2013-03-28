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
	glLineWidth(3);
	for(int i = 0; i < contours.blobs.size(); i++) {
		glBegin(GL_LINE_LOOP);
		for(int j = 0; j < contours.blobs[i].pts.size(); j+=6) {
			glVertex2f(contours.blobs[i].pts[j].x,contours.blobs[i].pts[j].y);
		}
		glEnd();
	}
	glLineWidth(1);
//	contours.draw(0, 0);
	
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0x90d4e3);
		ofCircle(circles[i].getPosition(), circles[i].getRadius());
	}

	
	
	glPopMatrix();
	//	printf("%d skelingtons\n", Skeletons::getInstance().size());
}
