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

//
//  SimpleReactickleButton.h
//  Somability
//
//  Created by Marek Bereza on 22/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Somability_SimpleReactickleButton_h
#define Somability_SimpleReactickleButton_h

#include "ReactickleButton.h"

class SimpleReactickleButton: public ReactickleButton {
public:
	SimpleReactickleButton(string name): ReactickleButton(name) {}
	void draw() {
		if(down) {
			ofSetHexColor(0x660000);
			ofRect(*this);
		}
		
		ofNoFill();
		ofSetHexColor(0xFFFFFF);
		ofRect(*this);
		ofFill();
		
		
		ofDrawBitmapString(name, x+10, y+20);
		

	}
	
	bool touchDown(float xx, float yy, int tid) {
		printf("Down\n");
		if(inside(xx, yy)) {
			currTouchId = tid;
			down = true;
		}
		
		return down;
	}
	
	bool touchMoved(float xx, float yy, int tid) {
		if(inside(xx, yy) && tid==currTouchId) {
			down = true;
		} else {
			down = false;
		}
		return down;
	}
	
	bool touchUp(float xx, float yy, int tid) {
		
		
		if(currTouchId==tid) {
			currTouchId = -1;
			down = false;
			if(inside(xx, yy)) {
				//printf("%d\n", ABS(startX - xx));
				if(listener!=NULL) listener->reactickleSelected(name);
			}
		}
		return down;
		
	}
	
protected:
	void setup(string name) {
		width = 100;
		height = 80;
	}
};

#endif
