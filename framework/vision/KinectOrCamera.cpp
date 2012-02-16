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

		camera.grabFrame();
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
