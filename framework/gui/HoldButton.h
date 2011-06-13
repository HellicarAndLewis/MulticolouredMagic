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
	
	
	/**
	 * If hold mode is set to true, you need to hold
	 * down on the button to activate it. If it's false
	 * it just works like a normal button.
	 */
	void setHoldMode(bool holdMode) {
		this->holdMode = holdMode;
	}
	
	
	bool touchDown(float xx, float yy, int tid) {
		
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
				if(ofGetElapsedTimef() - touchStart>HOLD_TIME) {
					listener->buttonPressed(name);
					down = false;
				}
			} else {
				dnImg->draw(x, y);
			}
			ofSetHexColor(0xFFFFFF);
		} else {
			upImg->draw(x, y);
		}
	}
};


