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