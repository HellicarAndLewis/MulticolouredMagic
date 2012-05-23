//
//  Ghost.h
//  Somability
//
//  Created by Marek Bereza on 23/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Somability_Ghost_h
#define Somability_Ghost_h

#include "Reactickle.h"
class Ghost: public Reactickle {
	
public:

	void start();
	void stop();
	
	void setup();
	void update();
	void draw();
	
	int frameNum;
	
	deque<ofImage*> imgs;
	ofImage img;
	bool needsKinect() { return true; }
};
#endif
