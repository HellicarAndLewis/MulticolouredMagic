/*
 *  Trace.h
 *
 *
 */

#include "Reactickle.h"
#include "msaColor.h"

class Trace: public Reactickle {
	
	void setup() {
		traceColour.setHSV(ofRandom(0.f,360.f), 1, 1);
	}
	
	void update() {
	}
	
	void draw() {
		traceColour.setGL();
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	msaColor traceColour;
};