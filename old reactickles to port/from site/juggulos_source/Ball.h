/*
 *  Ball.h
 *  _PIvectormaths
 *
 *  Created by Will Pearson on 10/02/2010.
 *  Copyright 2010 Sacculi >>. All rights reserved.
 *
 */

#ifndef BALL
#define BALL

#include "ofMain.h"
#include "ofxVectorMath.h"


#define otherObjsCount 2

#define nodes 5

class Ball{
	public:
	Ball();
	
	void addForce(ofxVec3f force);
	void updateBall();
	void setTexture();
	
	void collision(Ball* b1);
	
	ofxVec3f location;
	ofxVec3f velocity;
	ofxVec3f acceleration;
	
	float mass; //how heavy are we?
	float maximum_velocity;
	
	float bounce;
	//int color[3];
	
	float centerX, centerY;
	float radius, rotAngle;
	float accelX, accelY;
	float springing, damping;
	
	float nodeStartX[nodes];
	float nodeStartY[nodes];
	float nodeX[nodes];
	float nodeY[nodes];
	float angle[nodes];
	float frequency[nodes];
	//float organicConstant;
	
	ofTexture metalTexture;
	
	ofImage metalImage;
	
	
	//method to display
	void pauseBall(float locX, float locY);
	void drawFrame();
	void moveShape();
};

#endif
	

