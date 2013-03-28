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

//
//  Pendulum.cpp
//  Somability
//
//  Created by Marek Bereza on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "constants.h"
#include "Pendulum.h"
#include "Skeletons.h"

float mx = 0;
float my = 0;
void Pendulum::setup() {
	box2d.init();
	box2d.setGravity(0, 20);
	box2d.setFPS(30.0);
	//pendula[0] = Pendule();
	//pendula[0].setup(&box2d);
}

void Pendulum::start() {
	pendula.clear();
}
void Pendulum::update() {
	
	
	
		
	// add any new skelingtons
	for(int i = 0; i < Skeletons::getInstance().size(); i++) {
		ofxOpenNIUser &user = Skeletons::getInstance().getUser(i);
		if(pendula.find(user.getXnID())==pendula.end()) {
			pendula[user.getXnID()] = Pendule();
			printf("Creating pendule\n");
			pendula[user.getXnID()].setup(&box2d);
		}
		
		ofPoint p = g_worldToProjective(user.getCenter());
		p *= ofPoint(WIDTH, HEIGHT);
		p /= ofPoint(640, 480);
		
		pendula[user.getXnID()].setTarget(ofVec2f(p.x, p.y));
		printf("%f %f\n", p.x, p.y);
	}
	
	// get rid of any old ones.
	map<int,Pendule>::iterator it = pendula.begin();
	for(; it != pendula.end(); ) {
		bool found = false;
		for(int i = 0; i < Skeletons::getInstance().size(); i++) {
			if(Skeletons::getInstance().getUser(i).getXnID()==(*it).first) {
				
				found = true;
				break;
			}
		}
		if(!found) {
			(*it).second.destroy();
			printf("DEleting pendule\n");
			pendula.erase(it++);
		} else {
			++it;
		}
	}
	
	
	
	
	box2d.update();
}



void Pendulum::draw() {
	ofSetHexColor(0xFFFFFF);
//	colorImg->draw(0, 0, WIDTH, HEIGHT);
//	ofSetLineWidth(10);


	map<int,Pendule>::iterator it = pendula.begin();
	for(; it != pendula.end(); it++) {
		(*it).second.draw();
	}
//	ofSetLineWidth(1);
}


bool Pendulum::touchDown(float x, float y, int touchId) {
	pendula[0] = Pendule();
	pendula[0].setup(&box2d);
}

bool Pendulum::touchMoved(float x, float y, int touchId) {
	pendula[0].setTarget(ofVec2f(x, y));
}

bool Pendulum::touchUp(float x, float y, int touchId) {
	
}