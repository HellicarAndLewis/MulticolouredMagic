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