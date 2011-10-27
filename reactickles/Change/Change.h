/*
 *  Change.h
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"

class Change: public Reactickle {
    

	void setup();
	bool touchDown(float x, float y, int id);
	void trigger();
	void update();
	void draw();
    
    int getNumModes() {
		return 3;
	}
    
 
    
	
	float timeOfLastNewCircle;
	int colourPosition;
	ofColor noiseColour;
};