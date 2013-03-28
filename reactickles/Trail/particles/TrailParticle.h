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
 *  TrailParticle.h
 *  audioReactive
 *
 *  Created by Marek Bereza on 19/01/2011.
 *
 */
#pragma once

#include "ofMain.h"
#include "MagicShapes.h"

#define BUBBLE2_MAX_AGE 2

class TrailParticle{
public: 
	ofColor color;
	float brightness;
	float birthday;
	TrailParticle() {
		birthday = ofGetElapsedTimef();
		color.setHsb(ofRandom(0, 360), 190, 255, 255);
		if(!inited) {
			start();
		}
		brightness = ofRandom(0.5, 1.0);
		radius = radiusBase = ofRandom(7, 30);
		vel = ofVec2f(ofRandom(-1, 1), ofRandom(-1, 1));
		seed = ofRandom(0.4, 1.3);
	}
	float seed;
	bool isAlive() {
		return ofGetElapsedTimef() - birthday<BUBBLE2_MAX_AGE;
	}
	void update() {
		pos += vel;
		vel += ofVec2f(
					  ofRandom(-0.2, 0.2),
					  0
		);
		radius = radiusBase + (radiusBase *0.4)*sin(seed+ofGetElapsedTimef()*seed);
	}
	void draw(int shapeType) {
		ofFill();
		ofSetColor(color.r, color.g, color.b, ofMap(ofGetElapsedTimef() - birthday, 0, BUBBLE2_MAX_AGE, 255, 0, true));
        drawShape(shapeType, pos, radius*2);
		//ofCircle(pos.x, pos.y, radius);
	}
	
	
	float radius;
	float radiusBase;
	ofVec2f pos;
	ofVec2f vel;
	
	static void start() {
		inited = true;
	}
	static bool inited;
};