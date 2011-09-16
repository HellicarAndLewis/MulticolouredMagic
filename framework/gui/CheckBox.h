/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  CheckBox.h, created by Marek Bereza on 16/09/2011.
 */
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


/**
 * Really simple checkbox class
 */
class CheckBox: public InteractiveObject {
	
	
	
	
protected:
	ofImage *unchecked;;
	ofImage *checked;
	
	int currTouchId;
	string name;
	bool down;
	float alpha;
	bool *value;
public:
	
	
	
	void setup(string name, ofVec2f centre, string uncheckedUrl, string checkedUrl, bool *value) {
		centre.x = (int)centre.x;
		centre.y = (int)centre.y;

		this->value = value;
		
		down = false;
		this->name = name;
		currTouchId = -1;
		alpha = 1;
		if(checkedUrl=="") {
			checked = NULL;
		} else {
			checked = ImageCache::getImage(checkedUrl);
		}
		
		if(uncheckedUrl=="") {
			unchecked = NULL;
		} else {
			unchecked = ImageCache::getImage(uncheckedUrl);
		}
		
		float w = 0, h = 0;
		if(unchecked!=NULL) {
			w = unchecked->getWidth();
			h = unchecked->getHeight();
		}
		setFromCenter(ofPoint(centre.x, centre.y), w, h);
		
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
				*value ^= 1;
			}
		}
		return down;
		
	}
	

	
	
	virtual void draw() {
		x = (int)x;
		y = (int)y;
		ofSetColor(255, 255, 255, alpha*255.f);
		if(*value) {
			checked->draw(x, y);
		} else {
			unchecked->draw(x, y);
		}			
	}
};


