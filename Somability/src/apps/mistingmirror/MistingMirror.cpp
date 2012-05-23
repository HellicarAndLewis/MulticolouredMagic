//
//  MistingMirror.cpp
//  Somability
//
//  Created by Marek Bereza on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "MistingMirror.h"
#include "constants.h"

void MistingMirror::start() {
	frameNum = 0;
}
void MistingMirror::stop() {
}
void MistingMirror::setup() {
	img.allocate(VISION_WIDTH, VISION_HEIGHT, OF_IMAGE_COLOR);
	mask.allocate(VISION_WIDTH, VISION_HEIGHT);
}

void MistingMirror::update() {
	unsigned char *pix = img.getPixels();
	unsigned char *cam = colorImg->getPixels();
	unsigned char *g = threshImg->getPixels();
	
	int numPix = VISION_WIDTH * VISION_HEIGHT;
	frameNum++;
	if(frameNum%3==0) {
		mask.erode_3x3();
	}
	
	unsigned char *m = mask.getPixels();
	// merge mask and threshold
	for(int i = 0; i < numPix; i++) {
		m[i] = MAX(g[i], m[i]);
	}
	
	mask.setFromPixels(m, VISION_WIDTH, VISION_HEIGHT);
	
	mask.blur();
	m = mask.getPixels();
	
	for(int i = 0; i < numPix; i++) {
		pix[i*3] = (cam[i*3] * m[i])/255;
		pix[i*3+1] = (cam[i*3+1] * m[i])/255;
		pix[i*3+2] = (cam[i*3+2] * m[i])/255;
	}
	img.setFromPixels(pix, VISION_WIDTH, VISION_HEIGHT, OF_IMAGE_COLOR);
}


void MistingMirror::draw() {
	ofSetHexColor(0XFFFFFF);
	img.draw(0, 0, WIDTH, HEIGHT);
}
