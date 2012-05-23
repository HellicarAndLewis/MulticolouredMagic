//
//  MistingMirror.h
//  Somability
//
//  Created by Marek Bereza on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Somability_MistingMirror_h
#define Somability_MistingMirror_h

#include "Reactickle.h"

class MistingMirror: public Reactickle {

public:
	void start();
	void stop();
	
	void setup();
	
	void update();
	void draw();
	
	ofImage img;

	ofxCvGrayscaleImage mask;
	int frameNum;
	bool needsKinect() { return true;} 
};


#endif
