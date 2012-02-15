/*
 *  Ball.cpp
 *  _PIvectormaths
 *
 *  Created by Will Pearson on 10/02/2010.
 *  Copyright 2010 Sacculi >>. All rights reserved.
 *
 */

#include "Ball.h"

Ball::Ball(){
	
	setTexture();
	
	
	//color[0] = 255;
	//color[1] = 255;
	//color[2] = 255;
	
	location.set(ofRandom(0.0f, 800.0f), 0.0f, 0.0f);
	velocity.set(0.0f, 0.0f, 0.0f);
	
	acceleration.set(0.0f, 0.0f, 0.0f);
	
	mass = ofRandom(0,20);
	maximum_velocity = 5;
	
	bounce = 1.0;
	
	radius = 50;
	rotAngle = -90;
	accelX = 5;
	accelY = 5;
	springing = .0085;
	damping = .98;
	
	
	
	
	//need width and height here...
	//_mxBase.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 4);
	//_mxBlend.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 4);
	//_mxShader.loadShader("earth");
	
	//corner nodes
	for (int i=0; i<nodes; i++){
		
		nodeStartX[i] = nodes+i;
		nodeStartY[i] = nodes+i;
		nodeX[i] = nodes+i;
		nodeY[i] = nodes+i;
		angle[i] = nodes+i;
		frequency[i] = nodes+i;
	}
}

void Ball::addForce(ofxVec3f force){
	force /= mass;
	acceleration += force;
}

void Ball::pauseBall(float locX, float locY){
	
		
	
	
	location.y = locY;
	location.x = locX;	
	velocity.set(0.0f, 0.0f, 0.0f);
	
	acceleration.set(0.0f, 0.0f, 0.0f);
	
}


void Ball::updateBall(){
	

	
	
	velocity += acceleration;
	location += velocity;
	acceleration.set(0.0f, 0.0f, 0.0f);
	
	//organicConstant = 1;
	centerX = location.x;
	centerY = location.y;
	for (int i=0; i<nodes; i++){
		frequency[i] = ofRandom(5,12);
	}
	
	
	if (location.y > ofGetHeight()){
		velocity.y *= -bounce;
		location.y = ofGetHeight();
	}
	
	if (location.y < 0){
		velocity.y *= -bounce;
		location.y = 0;
	}
	
	if (location.x > ofGetWidth()){
		velocity.x *= -bounce;
		location.x = ofGetWidth();
	}
	
	if (location.x < 0){
		velocity.x *= -bounce;
		location.x = 0;
	}
}

void Ball::drawFrame(){
	
	
	//ofSetColor(color[0], color[1], color[2]);
	//ofCircle(location.x, location.y, 50);
	glEnable(GL_TEXTURE_2D);
	
	//calculate node starting points
	for (int i=0; i<nodes; i++){
		nodeStartX[i] = centerX+cos(ofDegToRad(rotAngle))*radius;
		nodeStartY[i] = centerY+sin(ofDegToRad(rotAngle))*radius;
		rotAngle += 360.0/nodes;
	}
	
	//draw polygon
	//curveTightness(organicConstant);
	
		
	ofSetupScreen();
	
	
	
		metalTexture.bind();
	//glPushMatrix();
	
		ofBeginShape();
		for (int i=0; i<nodes; i++){
			ofCurveVertex(nodeX[i], nodeY[i]);
		}
		for (int i=0; i<nodes-2; i++){
			ofCurveVertex(nodeX[i], nodeY[i]);
		}
		ofEndShape();
	glEnd();
	//glPopMatrix();
		
	glDisable(GL_TEXTURE_2D);
	//metalTexture.unbind();

		
	
	 
}

void Ball::moveShape(){
	//move center point
	float deltaX = (location.x-centerX);
	float deltaY = (location.y-centerY);
	
	//create springing effect
	deltaX *= springing;
	deltaY *= springing;
	accelX += deltaX;
	accelY += deltaY;
	
	//move polygon center
	centerX += accelX;
	centerY += accelY;
	
	//slow down springing
	accelX *= damping;
	accelY *= damping;
	
	//change curve tightness
	//organicConstant = 1-((fabs(accelX)+fabs(accelY))*0.1);
	
	//move nodes
	for (int i=0; i<nodes; i++){
		nodeX[i] = nodeStartX[i]+sin(ofDegToRad(angle[i]))*(accelX*2);
		nodeY[i] = nodeStartY[i]+sin(ofDegToRad(angle[i]))*(accelY*2);
		angle[i] += frequency[i];
	}
}


void Ball::collision(Ball* b1){
	
	float m1 = mass;
	float m2 = b1->mass;
	float x1 = location.x;
	float x2 = b1->location.x;
	float y1 = location.y;
	float y2 = b1->location.y;
	
	//declare things need at once...
	
	float newMass, diff, angle, newX, newY, newVelocityX, newVelocityY, fy21, sign;
	
	newMass = m2/m1;
	newX = x2-x1;
	newY = y2-y1;
	newVelocityX = b1->velocity.x - velocity.x;
	newVelocityY = b1->velocity.y - velocity.y;
	
	if ( (newVelocityX*newX + newVelocityY*newY) >= 0) return;
	
	fy21=1.0E-12*fabs(newY);
	if ( fabs(newX)<fy21){
		if (newX<0){sign=-1;} else {sign=1;}
		newX = fy21*sign;
	}
	
	//now figured the direction, set the velocities
	
	angle=newY/newX;
	diff = -2 * (newVelocityX + angle * newVelocityY)/((1 + angle * angle) * (1 + newMass));
	b1->velocity.x = b1->velocity.x + diff;
	b1->velocity.y = b1->velocity.y + angle * diff;
	velocity.x = velocity.x - newMass * diff;
	velocity.y = velocity.y - angle * newMass * diff;
}
	
//texture stuff...

void Ball::setTexture(){
	metalImage.loadImage("metal.jpg");
	metalTexture.allocate(metalImage.width, metalImage.height, GL_LUMINANCE, false);
	metalTexture.loadData(metalImage.getPixels(), metalImage.width, metalImage.height, GL_LUMINANCE);
	
}



