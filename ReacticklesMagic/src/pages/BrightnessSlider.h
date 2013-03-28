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
 * BrightnessSlider.h
 * Somantics
 *
 * Created by Marek Bereza on 06/06/2011.
 *
 */
#include "InteractiveObject.h"
#include "ImageCache.h"
#include "constants.h"
#include "Settings.h"

class BrightnessSlider: public InteractiveObject {
public:
	
	void setup() {
		x = 770;
		y = 77+55;
		sliderBG = ImageCache::getImage(IMAGE_ROOT+"sliderBG.png");
		width = sliderBG->getWidth();
		height = sliderBG->getHeight();
		sliderHandle = ImageCache::getImage(IMAGE_ROOT+"sliderHandle.png");
		sliderHandle->setAnchorPercent(0.5, 0.5);
		value = &Settings::getInstance()->settings["brightness"];
	}
	void draw() {
		ofSetHexColor(0xFFFFFF);
		sliderBG->draw(x, y);
		float yy = ofMap(*value, 0, 1, 389+this->y, 69+this->y, true);
		sliderHandle->draw(x + sliderBG->getWidth()/2, yy);
	}
	
	bool touchDown(float x, float y, int touchId) {
		if(inside(x, y)) {
			*value = ofMap(y, 69+this->y, 389+this->y, 1, 0, true);
			return true;
			
		}
		return false;
	}
	
	bool touchUp(float x, float y, int touchId) {
		
		touchDown(x, y, touchId);
		if(inside(x, y)) {
			Settings::getInstance()->save();
			return true;
		}
		return false;
	}
	
	bool touchMoved(float x, float y, int touchId) {
		return touchDown(x, y, touchId);
		
	}
private:
	float *value;
	ofImage *sliderBG;
	ofImage *sliderHandle;
};