/*
 *  Rectangle.h
 *  _PIvectormaths_springy
 *
 *  Created by Will Pearson on 02/03/2010.
 *  Copyright 2010 Sacculi >>. All rights reserved.
 *
 */
#ifndef RECTANGLE
#define RECTANGLE


#include "ofMain.h";

class rectangle{
	
public:
	
	float theta;
	float diameter;
	float dist;
	float orbitspeed;
	
	void setup(float _distance, float _diameter, float x, float y);
	void update();
	void display();
	void update_position(float x, float y);
	
	float circx;
	float circy;
	
	float counter;
	
};

#endif
