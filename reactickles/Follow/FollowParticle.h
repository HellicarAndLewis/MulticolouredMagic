/*
 *
 *  Created by Marek Bereza on 19/01/2011.
 *
 */
#pragma once

#include "ofMain.h"

#define MAX_SWARM_AGE 10


class FollowParticle {
public: 
	ofColor color;
	
	FollowParticle();
	
	
	
	
	void update();
	
	void attract(ofVec2f &point, float strength = 0.05);
	
	void draw();
	bool isAlive();
	void spawn(float x, float y, int mode, int shape = 0);
	
	
	

	float	brightness;
	float	birthday;
	float	maxAge;
	float	mass;
	float	seed;
	
	ofVec2f pos;
	ofVec2f	vel;
	
	int		mode;
	
	
	float	radius;
	float	radiusBase;
	int		shape;


};