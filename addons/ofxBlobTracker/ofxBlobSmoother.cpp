/**
 * ofxBlobSmoother.cpp
 * KinectTracker
 *
 * Created by Marek Bereza on 10/02/2011.
 *
 */


#include "ofxBlobSmoother.h"
ofxBlobSmoother::ofxBlobSmoother() {
	smoothness = 0.8;
}
void ofxBlobSmoother::blobEntered(ofVec3f pos, int blobId) {
	blobs[blobId] = pos;
}

void ofxBlobSmoother::blobMoved(ofVec3f &blob, int blobId) {
	blob = blob*(1.f - smoothness) + blobs[blobId]*smoothness;
	blobs[blobId] = blob;
}


void ofxBlobSmoother::blobExited(int blobId) {
	blobs.erase(blobId);
}

void ofxBlobSmoother::setSmoothness(float smoothness) {
	this->smoothness = smoothness;
}