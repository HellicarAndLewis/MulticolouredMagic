/*
 *  Rectangle.cpp
 *  _PIvectormaths_springy
 *
 *  Created by Will Pearson on 02/03/2010.
 *  Copyright 2010 Sacculi >>. All rights reserved.
 *
 */

#include "Rectangle.h"
#include "ofMain.h"

//_________________________________
void rectangle::setup(float _distance, float _diameter, float x, float y){
	
	circx = x;
	circy = y;
	
	counter = 0;
	
	
	dist = _distance;
	diameter = _diameter;
	
	theta = 0;
	orbitspeed = ofRandom(0, 3); 
	
}


//_________________________________
void rectangle::update(){
	
	theta += orbitspeed;
	counter = counter + 0.033f;
	
}

//_________________________________
void rectangle::display(){
	
	glPushMatrix();
	glRotatef(theta, 0, 0, 20);
	glTranslatef(dist, 0, 0);
	ofFill();
	ofSetColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
	float radius = 30 + 10 * sin(counter);
	ofEnableAlphaBlending();
	ofEllipse(circx, circy, radius, radius);
	ofDisableAlphaBlending();
	glPopMatrix();
	
}


//_________________________________
void rectangle::update_position(float x, float y){
	circx=x;
	circy=y;
	
}



//_________________________________