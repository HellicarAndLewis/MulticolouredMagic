//
//  MoveLoop.cpp
//  Somability
//
//  Created by Marek Bereza on 25/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MoveLoop.h"
#include "constants.h"


void MoveLoop::start() {
	count = 0;
	movement = 0;
	lastMovement = 0;
	recording = false;
	for(int i = 0; i < 100; i++) {
		buff.push_back(new unsigned char[VISION_WIDTH*VISION_HEIGHT*3]);
	}
}
void MoveLoop::stop() {
	while(!buff.empty()) {
		delete [] buff.front();
		buff.pop_front();
	}
}
void MoveLoop::setup() {
	prevImg.allocate(VISION_WIDTH, VISION_HEIGHT);
	diffImg.allocate(VISION_WIDTH, VISION_HEIGHT);
}

void MoveLoop::update() {
	

	diffImg = *colorImg;
	diffImg -= prevImg;
	prevImg = *colorImg;
	unsigned char *pix = diffImg.getPixels();
	float total = 0;
	int numPix = VISION_WIDTH * VISION_HEIGHT;
	for(int i = 0; i < numPix; i++) {
		if(pix[i]>20) { // filter out some of the noise
			total += pix[i];
		}
	}
	lastMovement = movement;
	movement = total/numPix;
	if(movement>0.1 || lastMovement>0.1) {
		
		// start recording if we're not recording
		if(!recording) {
			count = 0;
			recording = true;
		} else {
			count++;
		}
	} else {
		if(recording) {
			
		}
		count = 0;
	}
	
	if(recording) {
		// this is recording
		unsigned char *frame = buff.back();
		memcpy(colorImg->getPixels(), frame, VISION_WIDTH*VISION_HEIGHT*3);
		buff.pop_back();
		buff.push_front(frame);
	}	
}

void MoveLoop::draw() {
	ofSetHexColor(0xFFFFFF);
	if(recording) {
		colorImg->draw(0, 0, WIDTH, HEIGHT);
	} else {
		// show playback
	}

}