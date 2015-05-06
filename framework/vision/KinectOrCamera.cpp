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

/**
 * KinectOrCamera.cpp
 * magic
 *
 * Created by Marek Bereza on 13/04/2011.
 *
 */

#include "KinectOrCamera.h"

void KinectOrCamera::setup() {
	width = 640;
	height = 480;
	usingKinect = true;
	// try kinect first
	greyscaleBuffer = NULL;

#ifndef TARGET_OF_IPHONE
	kinect.init();
	usingKinect = kinect.open();
	kinect.setRegistration(true);
#else
	usingKinect = false;
	width /= 2;
	height /= 2;
#endif

	if(usingKinect) {

		printf("Using kinect\n");
	} else {
		camera		.setVerbose(false);
#ifdef TARGET_OF_IPHONE
		// if we're working on the iPhone
		// we want to use the front-facing camera.
		camera.setDeviceID(2);
#endif

		// init video grabber
		camera.initGrabber(width, height);
		width = camera.getWidth();
		height = camera.getHeight();
		greyscaleBuffer = new unsigned char[width*height];
		// set up the camera

	}



}

void KinectOrCamera::update() {
	if(usingKinect) {
#ifndef TARGET_OF_IPHONE
		kinect.update();
#endif
	} else {

		camera.update();
	}
}
void KinectOrCamera::close() {
	if(usingKinect) {
#ifndef TARGET_OF_IPHONE
		kinect.close();
#endif
	} else {
		camera.close();
		delete [] greyscaleBuffer;
	}
}


unsigned char *KinectOrCamera::getPixels() {
	if(usingKinect) {
#ifndef TARGET_OF_IPHONE
		return kinect.getPixels();
#endif
	} else {
		return camera.getPixels();
	}
}

unsigned char *KinectOrCamera::getDepthPixels() {
	if(usingKinect) {
#ifndef TARGET_OF_IPHONE
		return kinect.getDepthPixels();
#endif
	} else {
		unsigned char *pix = camera.getPixels();
		if(pix==NULL) return NULL;
		int numPixels = width*height;
		for(int i = 0; i < numPixels; i++) {
			greyscaleBuffer[i] = pix[i*3];
		}
		return greyscaleBuffer;
	}
	return NULL;
}
