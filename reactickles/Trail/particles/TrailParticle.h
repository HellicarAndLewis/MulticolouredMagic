/*
 *  TrailParticle.h
 *  audioReactive
 *
 *  Created by Marek Bereza on 19/01/2011.
 *
 */
#pragma once

#include "ofMain.h"
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
	void draw() {
//		printf("Bubble\n");
		ofFill();
		ofSetColor(color.r, color.g, color.b, ofMap(ofGetElapsedTimef() - birthday, 0, BUBBLE2_MAX_AGE, 255, 0, true));
		ofCircle(pos.x, pos.y, radius);
//		ofSetColor(color);
//		img.draw(pos.x, pos.y, radius*2, radius*2);
	}
	
	
	float radius;
	float radiusBase;
	ofVec2f pos;
	ofVec2f vel;
	
	static ofImage img;
	static void start() {
		if(!img.loadImage("bubble.png")) {
			printf("Couldn't load image\n");
		}
		img.setAnchorPercent(0.5, 0.5);
		inited = true;
	}
	static bool inited;
};