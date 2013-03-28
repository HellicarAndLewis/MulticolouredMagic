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
