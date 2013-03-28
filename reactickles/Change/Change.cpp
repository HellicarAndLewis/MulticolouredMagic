
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
 *  Change.cpp
 *
 *  Created by Marek Bereza on 27/10/2011.
 */
#include "Settings.h"
#include "Change.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif




void Change::setup() {

	//		noiseColour.setHSV(ofRandom(0.f,360.f), 1, 1);
	noiseColour.setHsb(0,0,0);
}

bool Change::touchDown(float x, float y, int id) {
	trigger();
	return true;
}

void Change::trigger() {
	if(mode == 0){
		if(noiseColour != ofColor(0,0,0)){
			noiseColour.set(0,0,0);
		}else{
			int colorIndex = Settings::getInstance()->settings["fgColor"];
			if(colorIndex==20) {
				noiseColour.set(255,255,255);
			} else {
				noiseColour.setHex(ColorPicker::colors[colorIndex]);
			}

		}

	}else if(mode == 1){
		if(noiseColour == ofColor(0,0,0)){

			int colorIndex = Settings::getInstance()->settings["fgColor"];
			if(colorIndex==20) {
				noiseColour.setHsb(ofRandom(0,255), 255,255);
			} else {
				noiseColour.setHex(ColorPicker::colors[colorIndex]);
			}



		}else{
			noiseColour.setHsb(0,0,0);
		}

	}else{
		noiseColour.setHsb(ofRandom(0,255), 255, 255);
	}



	timeOfLastNewCircle = ofGetElapsedTimef();
}



void Change::update() {
	float timeNow = ofGetElapsedTimef();

	float timeSinceLastCircle = timeNow - timeOfLastNewCircle;
	if((volume > volumeThreshold) && (timeSinceLastCircle > 0.3f )){

		trigger();
	}
}

void Change::draw() {
	ofSetColor(noiseColour);
	ofRect(0, 0, WIDTH, HEIGHT);
}

