/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
