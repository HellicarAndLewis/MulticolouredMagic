/*
 *  Change.h
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"
#include "msaColor.h"

class Change: public Reactickle {
	
	void setup() {
		
		noiseColour.setHSV(ofRandom(0.f,360.f), 1, 1);
		
	}
	
	void update() {
		float timeNow = ofGetElapsedTimef();
		
		float timeSinceLastCircle = timeNow - timeOfLastNewCircle;
		
		if((volume > 0.9f) && (timeSinceLastCircle > 0.1f )) {
			
			noiseColour.setHSV(ofRandom(0,360), 1, 1);
			
			timeOfLastNewCircle = timeNow;
		}
	}
	
	void draw() {
		noiseColour.setGL();
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	float timeOfLastNewCircle;
	int colourPosition;
	msaColor noiseColour;
};