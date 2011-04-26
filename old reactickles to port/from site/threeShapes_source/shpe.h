/*
 *  shpe.h
 *  emptyExample
 *
 *  Created by Joseph Scully on 27/02/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"

class shpe{
public:
	void setup(int sizeE);
	void reset();
	void update(int x, int y);
	void draw(int x, int y);
	int getState();
	
	
	int drawState;
	int sizeE;
	

};