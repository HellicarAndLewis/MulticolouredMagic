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
 * ModeDisplay.h
 * ReacticklesMagicMac
 *
 * Created by Marek Bereza on 13/06/2011.
 *
 */
#include "constants.h"
#include "ImageCache.h"

// in seconds - display time is how long it stays on the screen before fading
// and the fade time is how long it takes to fade out.
#define MODE_DISPLAY_TIME 1
#define MODE_FADE_TIME 1
class ModeDisplay {
public:
	ofImage **modes;
	int numModes;
	int mode;
	float lastTimeChanged;
	ModeDisplay() {
		mode = 0;
		numModes = 3;
		lastTimeChanged = 0;
	}
	
	void setup() {
		modes = new ofImage*[3];
		for(int i = 0; i < numModes; i++) {
			modes[i] = ImageCache::getImage(IMAGE_ROOT + "mode"+(ofToString(i+1))+".png");
			modes[i]->setAnchorPercent(0.5, 0.5);
		}
	}
	
	void setMode(int mode) {
		this->mode = mode;
		lastTimeChanged = ofGetElapsedTimef();
	}
	int getMode() {
		return mode;
	}
	
	void draw() {
		float timeSinceLastChange = ofGetElapsedTimef() - lastTimeChanged;
		// should we draw?
		if(timeSinceLastChange>0 && timeSinceLastChange<MODE_DISPLAY_TIME+MODE_FADE_TIME) {
			float alpha = 0;
			if(timeSinceLastChange<MODE_DISPLAY_TIME) {
				// we're just displaying
				alpha = ofMap(timeSinceLastChange, 0, 0.2, 0, 1, true);
			} else {
				// we're fading out
				alpha = ofMap(timeSinceLastChange - MODE_DISPLAY_TIME, 0, MODE_FADE_TIME, 1, 0, true);
			}
			ofSetColor(255, 255, 255, 255*alpha);
			modes[mode]->draw(WIDTH/2, HEIGHT/2);
		}
	}
};