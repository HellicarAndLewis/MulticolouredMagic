//
//  Pendulum.cpp
//  Somability
//
//  Created by Marek Bereza on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//
#include "constants.h"
#include "Pendulum.h"
float mx = 0;
float my = 0;
void Pendulum::setup() {
	img.allocate(VISION_WIDTH, VISION_HEIGHT, OF_IMAGE_COLOR_ALPHA);

}

void Pendulum::start() {
	pendula.clear();
}
void Pendulum::update() {
	
	
	map<int,Pendule>::iterator it = pendula.begin();
	for(; it != pendula.end(); it++) {
		(*it).second.update();
	}

	unsigned char *pix = img.getPixels();
	unsigned char *c = colorImg->getPixels();
	unsigned char *t = threshImg->getPixels();
	int cnt = VISION_WIDTH * VISION_HEIGHT;
	for(int i = 0; i < cnt; i++) {
		pix[i*4] = (c[i*3] * t[i])/255;
		pix[i*4+1] = (c[i*3+1] * t[i])/255;
		pix[i*4+2] = (c[i*3+2] * t[i])/255;
		pix[i*4+3] = t[i];
		
	}
	img.setFromPixels(pix, VISION_WIDTH, VISION_HEIGHT, OF_IMAGE_COLOR_ALPHA);
}



void Pendulum::draw() {
	ofSetHexColor(0xFFFFFF);
	img.draw(0, 0, WIDTH, HEIGHT);
	
	
	map<int,Pendule>::iterator it = pendula.begin();
	for(; it != pendula.end(); it++) {
		(*it).second.draw();
	}
}


bool Pendulum::touchDown(float x, float y, int touchId) {
	pendula[touchId] = Pendule(x, y);
	pendula[touchId].setTarget(ofVec2f(x, y));
}

bool Pendulum::touchMoved(float x, float y, int touchId) {
	pendula[touchId].setTarget(ofVec2f(x, y));
}

bool Pendulum::touchUp(float x, float y, int touchId) {
	if(pendula.find(touchId)!=pendula.end()) {
		pendula.erase(touchId);
	}
}