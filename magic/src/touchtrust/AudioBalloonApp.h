/*
 *  AudioBalloon.h
 *  touchTrust
 *
 *  Created by Mehmet Akten on 05/07/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "Reactickle.h"

static int		audioBalloonCountX	= 4;
static int		audioBalloonCountY	= 3;

static int		audioBalloonMinRadius = 5;
static int		audioBalloonMaxRadius;

class AudioBalloon {
public:
	float		radius;
	float		fullness;
	ofPoint		pos;
	
	void setup(ofPoint pos) {
		this->pos = pos;
		radius = audioBalloonMinRadius;
	}
	
	void update(float fullness) {
		this->fullness = fullness;
		radius = ofLerp(audioBalloonMinRadius, audioBalloonMaxRadius, fullness);
	}
	
	void draw() {
		ofFill();
		if(fullness < 1) glColor3f(1, 0, 0);
		else glColor3f(0, 0, 1);

		ofCircle(pos.x, pos.y, radius);
		
		glColor3f(1, 1, 1);
		ofNoFill();
		glLineWidth(2);
		ofCircle(pos.x, pos.y, radius);
		
		ofFill();
	}
	
	
};

class AudioBalloonApp : public Reactickle {
public:
	
	vector<AudioBalloon>	balloons;
	float					overallFullness;
	
	float					dieSpeed;
	float					incSpeed;
	float					volumeThreshold;
	
	void init() {
		//gui->setPage("Audio Balloon");
		
		ofSetCircleResolution(64);
		overallFullness		= 0;
		
		balloons.clear();
		
		for(int j=0; j<audioBalloonCountY; j++) {
			for(int i=0; i<audioBalloonCountX; i++) {
				AudioBalloon b;
				ofPoint pos;
				pos.x = ofMap(i, 0, audioBalloonCountX-1, ofGetWidth() * 0.2, ofGetWidth() * 0.8);
				pos.y = ofMap(j, 0, audioBalloonCountY-1, ofGetHeight() * 0.2, ofGetHeight() * 0.8);
				b.setup(pos);
				
				balloons.push_back(b);
			}
		}
	}
	
	void setup() {
		dieSpeed			= 0.0001;
		incSpeed			= 0.03;
		
		

		
		init();
		
	}
	
	void update() {
		if(volume > volumeThreshold) overallFullness += incSpeed * incSpeed * volume;
		else overallFullness -= dieSpeed;
		
		overallFullness = ofClamp(overallFullness, 0, 1.2);
		
		
		float totalFullness = overallFullness * balloons.size();
		
		audioBalloonMaxRadius = (ofGetWidth() / (audioBalloonCountX+1) / 2);
		for(int i=0; i<balloons.size(); i++) {
			float fullness;
			int totalFullnessWhole = floor(totalFullness);
			if(i<totalFullnessWhole) fullness = 1;
			else if(i>totalFullnessWhole) fullness = 0;
			else fullness = totalFullness - totalFullnessWhole;
			balloons[i].update(fullness);
		}
	}
	
	
	void debugDraw() {
		glColor3f(1, 0, 0);
		
		// draw active volume bar
		ofRect(0, 0, ofGetWidth() * volume, 30);
		
		
		// draw overallFullness
		ofRect(0, 100, ofGetWidth() * overallFullness, 30);
		
		
	}
	
	void draw() {
		if(overallFullness < 1) ofBackground(0, 0, 0);
		else ofBackground(255, 0, 0);
		ofEnableSmoothing();
		
		for(int i=0; i<balloons.size(); i++) balloons[i].draw();
//		debugDraw();
	}
};