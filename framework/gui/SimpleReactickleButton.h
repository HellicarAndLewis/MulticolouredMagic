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
