/*
 *  ofxBlobTracker.cpp
 *  ofxBlobTrackerExample
 *
 *  Created by Marek Bereza on 31/01/2011.
 *
 */

#include "ofxBlobTracker.h"

ofxBlobTracker::ofxBlobTracker() {
	for (int i=0;i<MAX_NUM_BLOBS*2;i++) {
		tuioPointSmoothed[i] = NULL;
	}
	bVerbose = false;
	smoothing = 0;
	lastId = 0;
	minTrackDistance = 0.2;
}

void ofxBlobTracker::addListener(ofxBlobListener *listener) {
	listeners.push_back(listener);
}


ofxBlob *ofxBlobTracker::updateKalman(int id, ofxBlob *blob) {
	id %= MAX_NUM_BLOBS;
	if (id>=MAX_NUM_BLOBS) return NULL;
	if(tuioPointSmoothed[id*2] == NULL) {
		tuioPointSmoothed[id*2] = new ofxCvKalman(blob->x);
		tuioPointSmoothed[id*2+1] = new ofxCvKalman(blob->y);
	} else {
		blob->x = tuioPointSmoothed[id*2]->correct(blob->x);
		blob->y = tuioPointSmoothed[id*2+1]->correct(blob->y);
	}
	
	return blob;
}

void ofxBlobTracker::clearKalman(int id) {
	id %= MAX_NUM_BLOBS;
	if (id>=MAX_NUM_BLOBS) return;
	if(tuioPointSmoothed[id*2]) {
		delete tuioPointSmoothed[id*2];
		tuioPointSmoothed[id*2] = NULL;
		delete tuioPointSmoothed[id*2+1];
		tuioPointSmoothed[id*2+1] = NULL;
	}
}


int ofxBlobTracker::getNextAvailableBlobId() {
	/*printf("There are already %d blobs\n", lastBlobs.size());
	for(int i = 0; i < lastBlobs.size(); i++) {
		printf("\t\tblob %d = %f %f\n", lastBlobs[i]->id, lastBlobs[i]->x, lastBlobs[i]->y);
	}*/
	/*for(int id = 0; id < MAX_NUM_BLOBS; id++) {
		bool foundId = false;

		for(int i = 0; i < lastBlobs.size(); i++) {
			if(lastBlobs[i]->id==id) {
				foundId = true;
				continue;
			}
		}
		
		if(!foundId) {
			//printf("New blob ID: %d!\n", id);
			return id;
		}
		
	}
	return 0;*/
	int currId = (lastId+1);//%MAX_NUM_BLOBS;
	lastId = currId;
	return currId;
}
ofxBlob *ofxBlobTracker::newBlob(ofVec3f coords) {
	ofxBlob *blob = new ofxBlob();
	blob->x = coords.x;
	blob->y = coords.y;
	blob->z = coords.z;
	blob->id = getNextAvailableBlobId();
	blob->touched = true;
	lastBlobs.push_back(blob);
	return blob;
}
void ofxBlobTracker::updateBlob(int id, ofVec3f *blob) {
	for(int i = 0; i < lastBlobs.size(); i++) {
		if(lastBlobs[i]->id==id) {
			lastBlobs[i]->x = blob->x;
			lastBlobs[i]->y = blob->y;
			lastBlobs[i]->z = blob->z;
			lastBlobs[i]->touched = true;
			return;
		}
	}
}
void ofxBlobTracker::untouchLastBlobs() {
	for(int i = 0; i < lastBlobs.size(); i++) {
		lastBlobs[i]->touched = false;
	}
}

void ofxBlobTracker::track(vector<ofVec2f> &blobs) {
	vector<ofVec3f> poop;
	for(int i = 0; i < blobs.size(); i++) {
		poop.push_back(ofVec3f(blobs[i].x, blobs[i].y, 0));
	}
	track(poop);
}
void ofxBlobTracker::track(vector<ofVec3f> &blobs) {
	blobSmoother.setSmoothness(smoothing);
	smoothedBlobs.clear();
	untouchLastBlobs();
	for(int i = 0; i < blobs.size() && i < MAX_NUM_BLOBS; i++) {
		
		// skip any NaN's (causes ofxTuioWrapper to run out of memory)
		if(blobs[i].x!=blobs[i].x || blobs[i].y!=blobs[i].y) {
			continue;
		}
		ofxBlob *blob = getClosestBlob(blobs[i]);
		
		// new blob!
		if(blob==NULL || blob->distance(blobs[i])>minTrackDistance) {

			ofxBlob *b = newBlob(blobs[i]);
			updateKalman(b->id, b);
			notifyAllListeners(*b, b->id, ofxBlobTracker_entered);
			
		// updated blob
		} else {
			blob = updateKalman(blob->id, blob);
			updateBlob(blob->id, &blobs[i]);
			notifyAllListeners(*blob, blob->id, ofxBlobTracker_moved);
		}
	}
	// dead blob
	// delete any untouched blobs
	for(int i = 0; i < lastBlobs.size(); i++) {
		if(lastBlobs[i]->touched==false) {
			notifyAllListeners(*lastBlobs[i], lastBlobs[i]->id, ofxBlobTracker_exited);
			delete lastBlobs[i];
			lastBlobs.erase(lastBlobs.begin()+i);
			i--;
		}
	}
}

ofxBlob *ofxBlobTracker::getClosestBlob(ofVec3f &blob) {
	if(lastBlobs.size()==0) return NULL;
	float minSqrDist = FLT_MAX;
	int minI = -1;
	for(int i = 0; i < lastBlobs.size(); i++) {
		float diffX = blob.x - lastBlobs[i]->x;
		float diffY = blob.y - lastBlobs[i]->y;
		float sqrDist = diffX*diffX + diffY*diffY;
		if(sqrDist<minSqrDist) {
			minI = i;
			minSqrDist = sqrDist;
		}
	}
	if(minI==-1) return NULL; // should never happen.
	return lastBlobs[minI];
}

void ofxBlobTracker::notifyAllListeners(ofVec3f pos, int id, ofxBlobEventType type) {

	// pass blob through smoother first
	switch(type) {
		case ofxBlobTracker_entered:	blobSmoother.blobEntered(pos, id);	break;
		case ofxBlobTracker_moved:		blobSmoother.blobMoved(pos, id);	break;
		case ofxBlobTracker_exited:		blobSmoother.blobExited(id);		break;
	}
	
	// add blob to local smoothed blob list
	switch(type) {
		case ofxBlobTracker_entered:
		case ofxBlobTracker_moved:		
			smoothedBlobs[id] = pos;	
			break;
		case ofxBlobTracker_exited:		
			smoothedBlobs.erase(id);	
			break;
	}
	
	// then send to listeners
	for(int i = 0; i < listeners.size(); i++) {
		switch(type) {
			case ofxBlobTracker_entered:
				blobSmoother.blobEntered(pos, id);
				listeners[i]->blobEntered(pos, id);
				break;
			case ofxBlobTracker_moved:
				blobSmoother.blobMoved(pos, id);
				listeners[i]->blobMoved(pos, id);
				break;
			case ofxBlobTracker_exited:
				blobSmoother.blobExited(id);
				listeners[i]->blobExited(pos, id);
				break;
		}
	}
	
	
	if(bVerbose) {
		string t = "";
		switch(type) {
			case ofxBlobTracker_entered: t = "entered"; break;
			case ofxBlobTracker_moved: t = "moved"; break;
			case ofxBlobTracker_exited: t = "exited"; break;
		}
		printf("[ofxBlobTracker: ] blob %d %s, (%f.2, %f.2)\n", id, t.c_str(), pos.x, pos.y);
	}
}

void ofxBlobTracker::draw(float x,float y) {
	draw(x, y, getWidth(), getHeight());
}
deque<ofVec2f> blobStore;
void ofxBlobTracker::draw(float x,float y,float w, float h) {
	// stroked rect
	ofEnableAlphaBlending();
	ofSetColor(0, 0, 0, 70);
	ofRect(x, y, w, h);
	ofSetHexColor(0xFFFFFF);
	
	ofNoFill();
	ofRect(x, y, w, h);
	
	glPushMatrix();
	glTranslatef(x, y, 0);
	ofSetColor(0,150, 0);
	
	map<int,ofVec3f>::iterator it;
	for(it = smoothedBlobs.begin(); it!=smoothedBlobs.end(); it++) {
		ofCircle((*it).second.x*w, (*it).second.y*h, 5);
		ofDrawBitmapString("id: "+ofToString((*it).first), (*it).second.x*w, (*it).second.y*h);
		blobStore.push_back((*it).second);
	}

	while(blobStore.size()>50) {
		blobStore.pop_front();
	}
	deque<ofVec2f>::iterator itr;
	for(itr = blobStore.begin(); itr!=blobStore.end(); itr++) {
		ofCircle((*itr).x*w,(*itr).y*h, 5);
	}
	glPopMatrix();
	ofFill();
	
}

float ofxBlobTracker::getWidth() {
	return 320;
}

float ofxBlobTracker::getHeight() {
	return 240;
}


void ofxBlobTracker::setVerbose(bool bVerbose) {
	this->bVerbose = bVerbose;
}