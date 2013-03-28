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

/*
 *  Bubble.cpp
 *  audioReactive
 *
 *  Created by Marek Bereza on 19/01/2011.
 *
 */
// 10, 35
#include "ofMain.h"

#include "constants.h"
#include "Settings.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif

#define MIN_RADIUS 20
#define MAX_RADIUS 50
#include "FollowParticle.h"
#include "MagicShapes.h"


FollowParticle::FollowParticle() {
	spawn(ofRandomWidth(), ofRandomHeight(), 0);
}


void FollowParticle::spawn(float x, float y, int mode, int shape) {


	this->shape = shape;
	this->mode = mode;
	pos = ofVec2f(x, y);
	birthday = ofGetElapsedTimef();

	int colorIndex = Settings::getInstance()->settings["fgColor"];
	if(colorIndex==20) {
		color.setHsb(ofRandom(0, 360), 190, 255, 255);
	} else {
		color = ofColor::fromHex(ColorPicker::colors[colorIndex]);
		color.setBrightness(ofRandom(127, 255));
	}
	brightness = ofRandom(0.5, 1.0);
	if(mode==0 || mode==1) {
		radius = radiusBase = 160;
	} else {
		radius = radiusBase = ofRandom(MIN_RADIUS, MAX_RADIUS);
	}
	vel = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
	seed = ofRandom(0.4, 1.3);
	mass = ofMap(radius, MIN_RADIUS, MAX_RADIUS, 0.2, 1);
	// in mode 0 the shape lasts for ever.
	if(mode==0) {
		maxAge = 1000000;
	} else {
		maxAge = ofRandom(MAX_SWARM_AGE*0.5, MAX_SWARM_AGE);
	}
}
#define MAX_SPEED 8
void FollowParticle::update() {

	pos += vel;
	vel += ofVec2f(
				   ofRandom(-0.2, 0.2),
				   0
				   );

	// bit o drag
	vel *= 0.99;


	if(vel.x>MAX_SPEED) {
		vel.x = MAX_SPEED;
	} else if(vel.x<-MAX_SPEED) {
		vel.x = -MAX_SPEED;
	}

	if(vel.y>MAX_SPEED) {
		vel.y = MAX_SPEED;
	} else if(vel.y<-MAX_SPEED) {
		vel.y = -MAX_SPEED;
	}


	radius = radiusBase + (radiusBase *0.4)*sin(seed+ofGetElapsedTimef()*seed);

	if(pos.x>WIDTH+radius) vel.x = 0;
	else if(pos.x<-radius) vel.x = 0;

	if(pos.y>HEIGHT+radius) vel.y = 0;
	else if(pos.y<-radius) vel.y = 0;
}

void FollowParticle::draw() {
	if(!isAlive()) return;
	ofFill();
	float alpha = ofMap(ofGetElapsedTimef() - birthday, maxAge*0.76, maxAge, 255, 0, true);
	if(mode==0) alpha = 255;
	ofSetColor(color.r, color.g, color.b, alpha);


	float shapeSize = ofMap(ofGetElapsedTimef() - birthday, 0, maxAge*0.04, 0, radius, true);
	if(mode==0) shapeSize = radius;
	drawShape(shape, pos, shapeSize);
}

bool FollowParticle::isAlive() {
	return ofGetElapsedTimef() < maxAge+birthday;
}


void FollowParticle::attract(ofVec2f &point, float strength /* = 0.05 */) {
	ofVec2f delta = pos - point;

	float dist = delta.length();

	delta.normalize();

	float nearThreshold = 10;
	float farThreshold = 70;

	float magnitude = sqrt(dist);

	if(dist<nearThreshold) {
		magnitude = 0;
	} else if(dist>farThreshold) {
		magnitude = sqrt(farThreshold);
	}

	vel -= delta*magnitude*strength*(1.f/mass);
//	vel -= delta*magnitude*0.05*(1.f/mass);
}
