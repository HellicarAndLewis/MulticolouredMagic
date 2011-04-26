/*
 *  Score.h
 *  intersect
 *
 *  Created by Ben Jones on 11/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _SCORE
#define _SCORE

#include "ofMain.h"

class Score {
	
public:
	
	int totalScore;
	
	void increase();
	void decrease();
	int returnScore();
	void reset();
	
};

#endif
