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

/**
 *  Cascade.cpp
 *
 *  Created by Marek Bereza on 27/10/2011.
 */

#include "Cascade.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif
#include "Settings.h"
#include "ofxOsc.h"
#include "ReactickleApp.h"

///////////////////////////////////////////////////////////////////////
// CASCADE PARTICLE


CascadeParticle::CascadeParticle(float x, float y, float magnitude, ofColor _color, int _shape){
	pos.x = x;
	pos.y = y;
	color = _color;
	float angle = ofRandom(0, PI*2);
	float speed = magnitude*5.f + ofRandom(-2, 3);
	vel.x = speed*cos(angle);
	vel.y = speed*sin(angle);
	birth = ofGetElapsedTimef();
	shape = _shape;
}

void CascadeParticle::update() {
	age = ofMap(ofGetElapsedTimef() - birth, 0, 5, 1, 0, true);
	pos += vel;
	vel.y += 0.2;
	if(pos.y>HEIGHT && vel.y>0) vel.y *= -0.75;
}

void CascadeParticle::draw() {

	ofSetColor(color.r, color.g, color.b, age*120);
	float radius = ofMap(age, 1, 0.6, 50, 0, true);
	drawShape(shape, pos, radius*4);
	ofSetColor(color.r*255, color.g*255, color.b*255, ofMap(age, 1, 0.6, 100, 0, true));
	radius = ofMap(age, 0, 1, 0, 100, false);
	drawShape(shape, pos, radius);
}
bool CascadeParticle::isDead() {
	return age<0.6;
}



///////////////////////////////////////////////////////////////////////
// THE CASCADE ITSELF


void Cascade::start() {
	currShapeId = 0;

}

void Cascade::setup() {
	lastClap = 0;
	clapping = false;
	currShapeId = 0;
}

void Cascade::update() {
	clapThreshold = volumeThreshold;
	if(clapping) {

		if(mode>0) {
			if(mode == 1){
				if (currShapeId == MAGIC_CIRCLE){
					currShapeId = MAGIC_CROSS;
				}else{
					currShapeId = MAGIC_CIRCLE;
				}
			}else{
				currShapeId++;
				currShapeId %= NUM_MAGIC_SHAPES;
			}

#ifndef TARGET_OF_IPHONE
			ofxOscMessage m;
			m.setAddress( "/shapechange" );
			m.addIntArg( currShapeId );
			ReactickleApp::instance->sender.sendMessage( m );
#endif
		}



		ofColor color;
		int colorIndex = Settings::getInstance()->settings["fgColor"];
		if(colorIndex==20) {
			color.setHsb(ofRandom(0, 255), 255, 255);
		} else {
			color = ofColor::fromHex(ColorPicker::colors[colorIndex]);
		}


		int numParticles = ofRandom(8, 12);

		for(int i = 0; i < numParticles; i++) {
			if(particles.size()<100) {
				particles.push_back(CascadeParticle(clapPoint.x, clapPoint.y, volume, color, currShapeId));
			}
		}
		clapping = false;
	}

	for(int i = 0; i < particles.size(); i++) {
		particles[i].update();
		if(particles[i].isDead()) {
			particles.erase(particles.begin()+i);
			i--;
		}
	}



}
void Cascade::draw() {


	int colorIndex = Settings::getInstance()->settings["fgColor"];


	ofBackground(0,0,0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	float timeSinceLastClap = ofGetElapsedTimef() - lastClap;
	float value = ofMap(timeSinceLastClap, 0, 0.5, 0.4, 0, true);

	ofColor color;
	if(colorIndex==20) {
		ofSetColor(value*255, 0, 0);
	} else {
		ofColor c = ofColor::fromHex(ColorPicker::colors[colorIndex]);
		c.a = value * 255;
		ofSetColor(c);
	}


	ofRect(0, 0, WIDTH, HEIGHT);

	for(int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
}

bool Cascade::touchDown(float x, float y, int touchId) {
//#ifdef TARGET_OF_IPHONE
	clapPoint = ofPoint(x, y);
	clapping = true;
//#endif
}

void Cascade::audioReceived(float *input, int length, int nChannels) {

	float lastSample = input[0];
	for(int i = 1; i < length; i++) {
		float diff = input[i] - lastSample;

		if(ABS(diff)>clapThreshold) {
			magnitude = ABS(diff);

			lastClap = ofGetElapsedTimef();
			clapPoint = ofPoint(ofRandomWidth(), ofRandomHeight());
			clapping = true;

#ifndef TARGET_OF_IPHONE
			//claps are touch downs for this one...
			ofxOscMessage m;
			m.setAddress( "/touchdown" );
			m.addIntArg(mode);
			ReactickleApp::instance->sender.sendMessage(m);
#endif
			return;
		}
		lastSample = input[i];
	}
}

