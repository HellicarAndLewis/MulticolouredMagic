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
 * DoubleTapButton.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#pragma once
#include "ofMain.h"
#include "SimpleButton.h"
#define HOLD_TIME 1
/**
 * double tap button class
 */
class HoldButton: public SimpleButton {
public:


	bool holdMode;
	float touchStart;
	bool buttonPressed;

	/**
	 * If hold mode is set to true, you need to hold
	 * down on the button to activate it. If it's false
	 * it just works like a normal button.
	 */
	void setHoldMode(bool holdMode) {
		this->holdMode = holdMode;
	}


	bool touchDown(float xx, float yy, int tid) {

        buttonPressed = false;
		if(inside(xx, yy)) {
			touchStart = ofGetElapsedTimef();
			currTouchId = tid;
			down = true;
		}

		return down;
	}



	virtual bool touchUp(float xx, float yy, int tid) {

		if(currTouchId==tid) {
			currTouchId = -1;
			down = false;
			if(inside(xx, yy)) {
				// if we're not in hold mode, just act like a normal button.
				if(!holdMode) {
					listener->buttonPressed(name);
				}
				/*if(listener!=NULL) {
					if(ofGetElapsedTimef() - touchStart>HOLD_TIME) {
						listener->buttonPressed(name);
					}
				}*/
				return true;
			}
		}
		return down;

	}



	virtual void draw() {
		x = (int)x;
		y = (int)y;
		ofSetColor(255, 255, 255, alpha*255.f);
		if(down) {


			// if we're in hold mode we need to
			// look at the timer and decide whether
			// to trigger.
			if(holdMode && listener!=NULL) {
				upImg->draw(x, y);
				float a = ofMap(ofGetElapsedTimef(), touchStart, touchStart+HOLD_TIME, 0, 1, true);
				ofSetColor(255, 255, 255, alpha*255.f*a);
				dnImg->draw(x, y);
				if(buttonPressed==false && ofGetElapsedTimef() - touchStart>HOLD_TIME) {
					buttonPressed = true;
					listener->buttonPressed(name);
					down = false;
				}
			} else {
				dnImg->draw(x, y);
			}
			ofSetHexColor(0xFFFFFF);
		} else {
			glColor4f(1, 1, 1, alpha*0.3);
			upImg->draw(x, y);
		}
	}
};


