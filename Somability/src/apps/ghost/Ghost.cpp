//
//  Ghost.cpp
//  Somability
//
//  Created by Marek Bereza on 23/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Ghost.h"
#include "constants.h"

void Ghost::setup() {
	img.allocate(VISION_WIDTH, VISION_HEIGHT, OF_IMAGE_COLOR_ALPHA);
}
void Ghost::start() {
	frameNum = 0;
	for(int i = 0; i < 10; i++) {
		imgs.push_back(new ofImage());
		imgs[i]->allocate(VISION_WIDTH, VISION_HEIGHT, OF_IMAGE_COLOR_ALPHA);
	}
}
void Ghost::stop() {
	while(!imgs.empty()) {
		delete imgs.front();
		imgs.pop_front();
	}
}


void Ghost::update() {
	
	frameNum++;
	
	threshImg->blur(7);
	
	
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

	if(frameNum%3==0) {
		ofImage *im = imgs.back();	
		imgs.pop_back();
		imgs.push_front(im);
		imgs.front()->setFromPixels(pix, VISION_WIDTH, VISION_HEIGHT, OF_IMAGE_COLOR_ALPHA);	
	}
}

void Ghost::draw() {
	// draw it backwards?
	ofSetHexColor(0xFFFFFF);
	deque<ofImage*>::reverse_iterator it;
	for(it = imgs.rbegin(); it != imgs.rend(); it++) {
		(*it)->draw(0, 0, WIDTH, HEIGHT);
	}
	img.draw(0, 0, WIDTH, HEIGHT);
}