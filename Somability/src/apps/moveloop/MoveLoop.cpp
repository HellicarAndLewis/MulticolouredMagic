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