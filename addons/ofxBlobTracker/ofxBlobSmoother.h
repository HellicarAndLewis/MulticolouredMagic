/**
 * ofxBlobSmoother.h
 * KinectTracker
 *
 * Created by Marek Bereza on 10/02/2011.
 *
 */

#pragma once

#include "ofMain.h"

/**
 * Used internally by ofxBlobTracker.
 *
 * To use, just run your blobs through the 3 touch* methods
 * here - blobMoved should affect the variable in the parameter
 * as it's passed by reference.
 */
class ofxBlobSmoother {
public:
	
	ofxBlobSmoother();
	
	void blobEntered(ofVec3f pos, int blobId);
	void blobMoved(ofVec3f &blob, int blobId);
	void blobExited(int blobId);
	void setSmoothness(float smoothness);

private:
	float smoothness;
	map<int,ofVec3f> blobs;
};