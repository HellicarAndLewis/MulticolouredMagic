/*
 *  MotionPop.h
 *  touchTrust
 *
 *  Created by Mehmet Akten on 05/07/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "testApp.h"


#include "ofMain.h"
#include "TTApp.h"

static int		popBalloonCountX			= 40;
static int		popBalloonMomentumSecs		= 5;
static float	popBalloonLerpUp			= 0.1;
static float	popBalloonLerpDown			= 0.05;


static float	popBalloonSize;



class PopBalloon {
public:
	ofPoint		pos;
	ofColor		color;
	int			motionCounter;			// inc this for motion momentum
	float		rot;
	float		targetRot;
	
	
	void init() {
		color.r = ofRandomuf();
		color.g = ofRandomuf();
		color.b = ofRandomuf();
		motionCounter = 0;
		targetRot = 0;
	}
	
	
	void setup(ofPoint pos) {
		rot = 0;
		this->pos = pos;
		init();
	}
	
	void update(bool hasMotion) {
		if(hasMotion) {
			if(motionCounter < popBalloonMomentumSecs * 60) motionCounter = popBalloonMomentumSecs * 60;
		} else {
			if(motionCounter > 0) motionCounter--;
		}
		
		if(motionCounter>0) targetRot = 1;
		else targetRot = 0;
		
		float lerpSpeed;
		if(targetRot > rot) lerpSpeed = popBalloonLerpDown;
		else lerpSpeed = popBalloonLerpUp;
		
		rot += (targetRot - rot) * lerpSpeed;
	}
};



class MotionPopApp : public TTApp {
public:
	
	vector<PopBalloon>	balloons;
	ofxCvGrayscaleImage smallGreyDiff;
	int					motionThreshold;
	
	void init() {
		gui->setPage("Motion Pop");

		balloons.clear();
		
		popBalloonSize = (ofGetWidth() / (popBalloonCountX+1));
		int popBalloonCountY = (popBalloonCountX * ofGetHeight() / ofGetWidth());
		for(int j=0; j<popBalloonCountY; j++) {
			for(int i=0; i<popBalloonCountX; i++) {
				PopBalloon b;
				ofPoint pos;
				pos.x = ofMap(i, 0, popBalloonCountX-1, popBalloonSize/2, ofGetWidth() - popBalloonSize/2);
				pos.y = ofMap(j, 0, popBalloonCountY-1, popBalloonSize/2, ofGetHeight() - popBalloonSize/2);
				b.setup(pos);
				
				balloons.push_back(b);
			}
		}
		
		smallGreyDiff.allocate(popBalloonCountX, popBalloonCountY);
		
		
		for(int i=0; i<balloons.size(); i++) {
			balloons[i].init();
		}
	}
	
	
	void setup() {
		motionThreshold = 20;
		
		gui->saveToXML();
		gui->addPage("Motion Pop");
		gui->addSlider("popBalloonCountX", popBalloonCountX, 20, 80);
		gui->addSlider("popBalloonMotionThreshold", motionThreshold, 0, 50);
		gui->addSlider("popBalloonMomentumSecs", popBalloonMomentumSecs, 0, 10);
		gui->addSlider("popBalloonLerpUp", popBalloonLerpUp, 0, 0.5);
		gui->addSlider("popBalloonLerpDown", popBalloonLerpDown, 0, 0.5);
		gui->loadFromXML();
		
		init();
	}
	
	void update() {
		testApp* app = (testApp*)ofGetAppPtr();
		
		smallGreyDiff.scaleIntoMe(app->diffImage, CV_INTER_NN);
		unsigned char *smallDiffPixels = smallGreyDiff.getPixels();
		
		for(int i=0; i<balloons.size(); i++) {
			bool pixelHasMotion = smallDiffPixels[i] > motionThreshold;
			balloons[i].update(pixelHasMotion);
		}
	}
	
	
	void debugDraw() {
		//		smallGreyDiff.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	void draw() {
		ofBackground(0, 0, 0);
		ofEnableSmoothing();
		ofEnableAlphaBlending();

		ofSetRectMode(OF_RECTMODE_CENTER);
		for(int i=0; i<balloons.size(); i++) {
			glColor3f(balloons[i].color.r, balloons[i].color.g, balloons[i].color.b);
			float s = (1-balloons[i].rot) * popBalloonSize * 0.95;

			ofRect(balloons[i].pos.x, balloons[i].pos.y, s, s);
		}
		ofSetRectMode(OF_RECTMODE_CORNER);
	}
	
};