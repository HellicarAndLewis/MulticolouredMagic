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

class HoldToggle: public xmlgui::Control {
public:
	xmlgui::Listener *listener;
	void setup(string name, bool &val) {
		names = ofSplitString(name, "|");
		pointToValue(&val);
		on = false;
		touchDownStart = 1000000;
	}
	
	void addListener(xmlgui::Listener *l) {
		this->listener = l;
	}
	
	void draw() {

		if(down) {
			ofSetHexColor(0x999999);
		} else {
			ofSetHexColor(0xFFFFFF);
		}
		ofRect(*this);
		
		
		float t = ofMap(ofGetElapsedTimef(), touchDownStart, touchDownStart+0.5, 0, 1, true);
		if(down) {
			if(t==0) {
			} else if(t<1) {
				ofSetHexColor(0xFFFFFF);
				ofRectangle r = *this;
				r.width *= t;
				ofRect(r);
			} else {
				// do it
				bval(value) = !bval(value);
				touchDownStart = 1000000;
			}
		}
		
		ofSetHexColor(0);
		ofNoFill();
		ofRect(*this);
		ofFill();
		ofDrawBitmapString(bval(value)?names[1]:names[0], x+3, y+height-5);
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