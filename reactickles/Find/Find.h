/*
 *  Find.h
 *
 *
 */

#include "Reactickle.h"
#include "msaColor.h"

class Find: public Reactickle {
	
	void setup() {
		findColour.setHSV(ofRandom(0.f,360.f), 1, 1);
	}
	
	void update() {
	}
	
	void draw() {
		findColour.setGL();
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	msaColor findColour;
};