/*
 *  Button.h
 *
 *  Created by Marek Bereza on 16/01/2011.
 *  Copyright 2011 Marek Bereza. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"
#include "ImageCache.h"
#include "ofVec2f.h"
#include "InteractiveObject.h"

class SimpleButtonListener {
public:
	virtual void buttonPressed(string buttonName) = 0;
};

/**
 * Really simple button class
 */
class SimpleButton: public InteractiveObject {
private:
	ofImage *upImg;
	ofImage *dnImg;

	
	
protected:
	int currTouchId;
	string name;
	SimpleButtonListener *listener;
	bool down;
	float alpha;
	
public:
	
	
	
	void setup(string name, ofVec2f centre, string upImgUrl, string dnImgUrl = "") {
		centre.x = (int)centre.x;
		centre.y = (int)centre.y;
		listener = NULL;
		down = false;
		this->name = name;
		currTouchId = -1;
		alpha = 1;
		upImg = ImageCache::getImage(upImgUrl);

		if(dnImgUrl=="") {
			dnImg = NULL;
		} else {
			dnImg = ImageCache::getImage(dnImgUrl);
		}

	 
		setFromCenter(ofPoint(centre.x, centre.y), upImg->getWidth(), upImg->getHeight());

	}
	
	
	void setAlpha(float alpha) {
		this->alpha = alpha;
	}
	bool touchDown(float xx, float yy, int tid) {
		
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
	
	void setListener(SimpleButtonListener *listener) {
		this->listener = listener;
	}
		
	
	virtual void draw() {
		x = (int)x;
		y = (int)y;
		ofSetColor(255, 255, 255, alpha*255.f);
		if(down) {
			if(dnImg!=NULL) {
				dnImg->draw(x, y);
			} else {
				ofSetHexColor(0xFFCCCC);
				upImg->draw(x, y);
			}
		} else {
			upImg->draw(x, y);
		}
	}
};