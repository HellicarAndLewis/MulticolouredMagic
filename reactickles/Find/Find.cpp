/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  Find.cpp
 *
 *  Created by Marek Bereza on 27/10/2011.
 */

#include "Find.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif
#include "Settings.h"
#include "ofxOsc.h"
#include "ReactickleApp.h"



void Find::setup() {
	currShapeID = 0;

	mode = 0;

	newShapePositionAndColour();

	posOfShape = targetPosOfShape;
	findColour = targetFindColour;

	timeOfLastInteraction = ofGetElapsedTimef();
}

void Find::newShapePositionAndColour(){


	int colorIndex = Settings::getInstance()->settings["fgColor"];
	if(colorIndex==20) {
		targetFindColour.setHsb(ofRandom(0.f,255), 255,255);
	} else {
		targetFindColour = ofColor::fromHex(ColorPicker::colors[colorIndex]);
	}



	targetPosOfShape = ofVec2f(ofRandom(0.f, WIDTH), ofRandom(0.f, HEIGHT));
	radius = ofRandom(100.f, 260.f);

	if(mode>0) {
		if(mode == 1){
			if (currShapeID == MAGIC_CIRCLE){
				currShapeID = MAGIC_CROSS;
			}else{
				currShapeID = MAGIC_CIRCLE;
			}
		}else{
			currShapeID++;
			currShapeID %= NUM_MAGIC_SHAPES;
		}
	}else{
		currShapeID = MAGIC_CIRCLE;
	}

#ifndef TARGET_OF_IPHONE
	ofxOscMessage m;
	m.setAddress( "/shapechange" );
	m.addIntArg( currShapeID );
	ReactickleApp::instance->sender.sendMessage( m );
#endif

}

void Find::update() {
	float timeNow = ofGetElapsedTimef();

	float timeSinceLastInteraction = timeNow - timeOfLastInteraction;

	if((volume > volumeThreshold) && (timeOfLastInteraction > 0.3f )){
		newShapePositionAndColour();

		timeOfLastInteraction = timeNow;
	}

	float l = 0.7;
	posOfShape = posOfShape * l + targetPosOfShape * (1.f - l);
	findColour = findColour * l + targetFindColour * (1.f - l);

}

void Find::draw() {
	ofSetColor(findColour);
	drawShape(currShapeID, posOfShape, radius);
}

bool Find::touchDown(float x, float y, int touchId){
	float forgiveness = 2.f;

	ofVec2f touchPoint = ofVec2f(x,y);

	ofVec2f difference = posOfShape - touchPoint;

	if(difference.length() < forgiveness + radius){
		newShapePositionAndColour();
	}

	return true;
}

bool Find::touchMoved(float x, float y, int touchId){
	return touchDown(x, y, touchId);
}

bool Find::touchUp(float x, float y, int touchId){
	return true;
}

