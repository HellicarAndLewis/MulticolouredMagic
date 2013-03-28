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


