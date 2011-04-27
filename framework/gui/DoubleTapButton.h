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

/**
 * double tap button class
 */
class DoubleTapButton: public SimpleButton {
public:
	virtual bool touchUp(float xx, float yy, int tid) {
		
		if(currTouchId==tid) {
			currTouchId = -1;
			down = false;
			if(inside(xx, yy)) {
				if(listener!=NULL) listener->buttonPressed(name);
			}
		}
		return down;
		
	}
};