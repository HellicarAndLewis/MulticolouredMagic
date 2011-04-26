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

	   
	kinect.init();
	usingKinect = kinect.open();
	if(usingKinect) {
		
	} else {
		// init video grabber
		camera.initGrabber(width, height);
		greyscaleBuffer = new unsigned char[width*height];
	}
	
	
	
}

void KinectOrCamera::update() {
	if(usingKinect) {
		kinect.update();
	} else {
		camera.grabFrame();
	}
}
void KinectOrCamera::close() {
	if(usingKinect) {
		kinect.close();
	} else {
		camera.close();
		delete [] greyscaleBuffer;
	}
}


unsigned char *KinectOrCamera::getPixels() {
	if(usingKinect) {
		return kinect.getPixels();
	} else {
		return camera.getPixels();
	}
}
unsigned char *KinectOrCamera::getDepthPixels() {
	if(usingKinect) {
		return kinect.getDepthPixels();
	} else {
		unsigned char *pix = camera.getPixels();
		int numPixels = width*height;
		for(int i = 0; i < numPixels; i++) {
			greyscaleBuffer[i] = pix[i*3];
		}
		return greyscaleBuffer;
	}
}