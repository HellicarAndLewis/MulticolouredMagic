/*
 *
 *  Created by Marek Bereza on 19/01/2011.
 *
 */
#pragma once

#include "ofMain.h"

#define MAX_SWARM_AGE 10
#define COLOR_MODE_RAINBOW 1
#define COLOR_MODE_RED 2
#define COLOR_MODE_GREEN 3
#define COLOR_MODE_BLUE 4

class FollowParticle {
public: 
	ofColor color;
	float brightness;
	float birthday;
	FollowParticle();
	
	float seed;
	
	
	void update();
	
	void attract(ofVec2f &point, float strength = 0.05);
	
	void draw();
	bool isAlive();
	void spawn(float x, float y, int mode, int shape = 0);
	float radius;
	int shape;
	float radiusBase;
	ofVec2f pos;
	float maxAge;
	ofVec2f vel;
	float mass;
	static int colorMode;
	int mode;

};