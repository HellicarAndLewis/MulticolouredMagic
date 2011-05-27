/*
 * of3DVideo.h
 *
 *  Created on: 16/12/2010
 *      Author: arturo
 */

#pragma once

class ofxBase3DVideo: public ofBaseVideo{
public:
	virtual unsigned char 	* getDepthPixels()=0;		// grey scale values
	virtual float* getDistancePixels()=0;
	virtual unsigned char * getCalibratedRGBPixels()=0;


	virtual ofTexture &		getDepthTextureReference()=0;
};
