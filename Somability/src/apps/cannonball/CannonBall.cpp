/**
 *  CannonBall.cpp
 *
 *  Created by Marek Bereza on 11/06/2012.
 */

#include "CannonBall.h"
#include "Skeletons.h"
#include "constants.h"

void CannonBall::setup() {
	for(int i = 0; i < 3; i++) {
		balls.push_back(cannon::Ball());
		balls.back().setup();
	}
}



void CannonBall::update() {
	
	for(int i = 0; i < balls.size(); i++) {
		balls[i].update();
	}
	
	walls.clear();
	for(int i = 0; i < Skeletons::getInstance().size(); i++) {

		ofxOpenNIUser &user = Skeletons::getInstance().getUser(i);
		// find out if there's a collision
		ofxOpenNIJoint &top = user.getJoint(JOINT_HEAD);
		ofxOpenNIJoint &bot = user.getJoint(JOINT_TORSO);
		
		ofPoint a, b;
		a = top.getProjectivePosition();
		b = bot.getProjectivePosition();

		a = ofPoint(a.x, a.y)*ofPoint(WIDTH, HEIGHT)/ofPoint(640.f, 480.f);
		b = ofPoint(b.x, b.y)*ofPoint(WIDTH, HEIGHT)/ofPoint(640.f, 480.f);
		walls.push_back(LineEquation());
		walls.back().setFrom2Points(a, b);
		

		for(int j = 0; j < balls.size(); j++) {
			if(balls[j].doCollision(a, b)) {
				balls[j].update();
			}
		}
	}
	
	
	
}


void CannonBall::draw() {
	glPushMatrix();
	glScalef((float)WIDTH/640.f, (float)HEIGHT/480.f, 1);
	ofSetHexColor(0xFFFFFF);
	colorImg->draw(0, 0, 640, 480);
	for(int i = 0; i < Skeletons::getInstance().size(); i++) {
		ofxOpenNIUser &user = Skeletons::getInstance().getUser(i);
	//	user.drawSkeleton();
	}
	
	glPopMatrix();
	glLineWidth(5);
	ofSetHexColor(0x0000FF);
	
	for(int i = 0; i < walls.size(); i++) {
		ofVec2f a(0, 0);
		ofVec2f b(0, HEIGHT);
		a.x = walls[i].getX(a.y);
		b.x = walls[i].getX(b.y);
		ofLine(a, b);
	}

	glLineWidth(1);
	for(int j = 0; j < balls.size(); j++) {
		balls[j].draw();
	}
}
