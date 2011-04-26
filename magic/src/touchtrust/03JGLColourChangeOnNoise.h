/*
 *  ExampleApp.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"
#include "msaColor.h"

class ColourChangeOnNoiseApp: public Reactickle {
	
	void setup() {
		
		noiseColour.setHSV(ofRandom(0.f,360.f), 1, 1);
		
	}
	
	void update() {
		float timeNow = ofGetElapsedTimef();
		
		float timeSinceLastCircle = timeNow - timeOfLastNewCircle;
		
		if((volume > 0.9f) && (timeSinceLastCircle > 0.1f )) {
			
//			float noisePosition = ofGetElapsedTimef();
//			float greenOffset = 4.231f;
//			float blueOffset = 3.141529f;
//			
//			float redComponent = 255*ofNoise(noisePosition);
//			float greenComponent = 255*ofNoise(noisePosition+greenOffset);
//			float blueComponent =  255*ofNoise(noisePosition+blueOffset);
//			
//			noiseColour.r = redComponent;
//			noiseColour.g = greenComponent;
//			noiseColour.b = blueComponent;
			
			noiseColour.setHSV(ofRandom(0,360), 1, 1);
			
			timeOfLastNewCircle = timeNow;
		}
	}
	
	void draw() {
			//ofSetColor(0xFF0000);
			//ofRect(0, 0, ofGetWidth()*volume, ofGetHeight());
			//ofSetColor(noiseColour.r, noiseColour.g, noiseColour.b);
		noiseColour.setGL();
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
	}
	
	float timeOfLastNewCircle;
	int colourPosition;
	msaColor noiseColour;
};