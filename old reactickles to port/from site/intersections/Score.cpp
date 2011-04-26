/*
 *  Score.cpp
 *  intersect
 *
 *  Created by Ben Jones on 11/04/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Score.h"

void Score::increase() {
	totalScore++;
}

void Score::decrease() {
	totalScore--;
}

int Score::returnScore() {
	return totalScore;
}

void Score::reset() {
	totalScore = 0;
}