//
//  Echo.cpp
//  Somability
//
//  Created by Marek Bereza on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Echo.h"
#include "constants.h"

Echo::~Echo() {
	
}
void Echo::draw() {
	ofSetHexColor(0xffffff);
	display.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void Echo::start() {


	DELAY_SIZE		= 12;
	
	currFrame = 0;
	

	
	output = new unsigned char[VISION_WIDTH*VISION_HEIGHT*3];
	memset(output, 0, VISION_WIDTH*VISION_HEIGHT*3);
	display.allocate(VISION_WIDTH, VISION_HEIGHT, OF_IMAGE_COLOR);
	
	// allocate delay buffer
	for(int i = 0; i < DELAY_SIZE; i++) {
		unsigned char *frame = new unsigned char[VISION_WIDTH*VISION_HEIGHT*3];
		memset(frame, 0, VISION_WIDTH*VISION_HEIGHT*3);
		frames.push_back(frame);
	}
}


void Echo::stop() {
	printf("Echo stopped\n");
	for(int i = 0; i < frames.size(); i++) {
		delete [] frames[i];
	}
	frames.clear();
	delete [] output;
}

void Echo::update() {
	//printf("%d / %d\n", currFrame, frames.size());
	
	int totalPixels = VISION_WIDTH*VISION_HEIGHT*3;
	unsigned char * pixels = colorImg->getPixels();
	unsigned char *curr = frames[currFrame];
	
	
	int tap = currFrame - 1;
	if(tap<0) tap = frames.size()-1;
	
	float amt = 0.38;//ofMap(mouseX, 0, ofGetWidth(), 0, 1);
	
	for (int i = 0; i < totalPixels; i++){
		float f = (int)pixels[i];
		f = f * amt + curr[i] * (1.f - amt);
		curr[i] = f;
	}
	
	
	
	
	currFrame++;
	if(currFrame>=frames.size()) {
		currFrame = 0;
	}
	display.setFromPixels(curr, VISION_WIDTH, VISION_HEIGHT, OF_IMAGE_COLOR);
}