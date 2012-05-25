//
//  Skeleton.h
//  Somability
//
//  Created by Marek Bereza on 24/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Somability_Skeleton_h
#define Somability_Skeleton_h

#include "ofxOpenNI.h"

class Skeletons {
public:
	static Skeletons &getInstance() {
		static Skeletons * inst = NULL;
		if(inst==NULL) {
			printf("Creating new skeleton instance\n");
			inst = new Skeletons();
		}
		return *inst;
	}
	int size() {
		return openni->getNumTrackedUsers();
	}
	ofxOpenNIUser &getUser(int index) {
		return openni->getTrackedUser(index);
	}
	void setOpenNI(ofxOpenNI *openni) {
		this->openni = openni;
	}
	
private:
	ofxOpenNI *openni;
	Skeletons() {}
};

#endif
