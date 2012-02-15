/**
 * KinectOrCamera.h
 * magic
 *
 * Created by Marek Bereza on 13/04/2011.
 *
 */
#pragma once
#include "ofMain.h"
#ifndef TARGET_OF_IPHONE
#include "ofxKinect.h"
#endif
class KinectOrCamera {
public:
	void setup();
	void update();
	void close();
	
	int width;
	int height;
	
	unsigned char *getPixels();
	unsigned char *getDepthPixels();

	int getWidth() { return width; }
	int getHeight() { return height; } 
	ofVideoGrabber camera;
	
#ifndef TARGET_OF_IPHONE
	ofxKinect kinect;

#endif
private:
	unsigned char *greyscaleBuffer;
	bool usingKinect;
};