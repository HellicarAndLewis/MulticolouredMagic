/*
 *  GuiIntField.h
 *  Gui
 *
 *  Created by Marek Bereza on 11/02/2010.
 *
 */


#pragma once

#include "LabeledControl.h"
class IntField: public LabeledControl {
public:
	
	IntField(): LabeledControl() {
		
		height = 20;
		width = 70;
		value = new int[1];
		ival(value) = 0;
	}
		// round() not supported in vs2010
	float __round(float number) {
		return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
	}
	void draw() {
		
		ofSetColor(50, 50, 50);
		ofRect(x, y, width, height);
		ofNoFill();
		ofRect(x, y, width, height);
		ofFill();
		ofSetColor(255, 255, 255);
		if(focus && ((int)__round(ofGetElapsedTimef()*2.5))%2==0) {
			xmlgui::Resources::drawString(ofToString(ival(value)) + "|", x+3, y+14);
		} else {
			xmlgui::Resources::drawString(ofToString(ival(value)), x+3, y+14);
		}
		drawLabel(x+3, y);
		
		
	}
	bool keyPressed(int key) {
		if(key>='0' && key<='9') { // if it's a printable char
			ival(value) *= 10;
			ival(value) += key - '0';
			
			return true;
		} else if(key==8 || key==127) { // delete
			ival(value) /= 10;
			return true;
		} else if(key==10 || key==13) {
			// this is a return
			return true;
		}
		return false;
	}
	
	bool touchDown(int x, int y, int id) {
		
		if(inside(x, y)) {
			parent->setKeyboardFocus(this);
			return true;
		} else {
			return false;
		}
	}
	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("Value","value", "intfield", value));
	}
	
	string valueToString() { return ofToString(ival(value)); }
	void valueFromString(string inp) { ival(value) = atoi(inp.c_str()); }
};
