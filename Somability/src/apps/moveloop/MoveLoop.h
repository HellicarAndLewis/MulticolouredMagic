//
//  MoveLoop.h
//  Somability
//
//  Created by Marek Bereza on 25/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Somability_MoveLoop_h
#define Somability_MoveLoop_h
#include "Reactickle.h"

class MoveLoop: public Reactickle {
public:
	void start();
	void stop();
	void setup();
	void update();
	void draw();
	ofxCvGrayscaleImage prevImg;
	ofxCvGrayscaleImage diffImg;
	float movement;
	float lastMovement;
	int count;
	bool recording;
	deque<unsigned char*> buff;
	bool needsKinect() { return true; }
};

#endif
