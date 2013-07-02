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
 *  HoldToggle.h, created by Marek Bereza on 12/12/2012.
 */


#pragma once
#include "Control.h"
#include "RingDrawer.h"

class HoldToggle: public xmlgui::Control {
public:
	RingDrawer ringDrawer;
	
	xmlgui::Listener *listener;
	vector<ofImage> images;
	void setup(string name, bool &val) {
		id = name;
		names = ofSplitString(name, "|");
		for(int i = 0; i < names.size(); i++) {
			images.push_back(ofImage());
			images[i].loadImage(names[i]+".png");
			images[i].setAnchorPercent(0.5, 0.5);
		}
		
		pointToValue(&val);
		on = false;
		touchDownStart = 1000000;
		
	}
	
	
	void addListener(xmlgui::Listener *l) {
		this->listener = l;
	}
	
	void draw() {
		float t = ofMap(ofGetElapsedTimef(), touchDownStart, touchDownStart+0.5, 0, 1, true);

		if(down) {
			ofSetHexColor(0xFFFFFF);
		} else {
			ofSetHexColor(0x999999);
		}
		//ofRect(*this);
		ofPoint centre = (*this).getCenter();
		if(down) {
			ringDrawer.drawRing(centre, width/2, t, width*0.8/2, bval(value)?0x640000:0);
		}
		
		
		if(down) {
			ofSetHexColor(0xFFFFFF);
		} else {
			ofSetHexColor(0x999999);
		}
		
		
		images[bval(value)?1:0].setAnchorPercent(0.5, 0.5);
		float off = 0;
		if(names[bval(value)?1:0]=="play") off = 10;
		images[bval(value)?1:0].draw(centre.x+off, centre.y);

		
		if(down) {
			if(t>=1) {
				// do it
				bval(value) = !bval(value);
				xmlgui::Event e(this, xmlgui::Event::TOUCH_UP);
				if(listener!=NULL) listener->controlChanged(&e);
				touchDownStart = 1000000;
			}
		}
		
		ofSetHexColor(0);
	}
	
	
	
	bool on;
	vector<string> names;
	float touchDownStart;

	bool touchDown(int x, int y, int id) {
		if(inside(x, y)) {
			touchDownStart = ofGetElapsedTimef();
			down = true;
			return true;
		}
		return false;
	}
	bool touchMoved(int x, int y, int id) {
		if(inside(x, y)) {
			down = true;
			return true;
		}
		down = false;
		return false;
	}
	
	bool touchUp(int x, int y, int id){
		down = false;
		if(inside(x, y)) {
			return true;
		}
		return false;
	}
	
};