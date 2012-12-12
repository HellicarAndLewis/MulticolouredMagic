/*
 *  GuiDoubleField.h
 *  Snowboard
 *
 *  Created by Marek Bereza on 06/12/2010.
 *
 */


#pragma once

#include "LabeledControl.h"
class DoubleField: public LabeledControl {
public:
	
	DoubleField(): LabeledControl() {
		
		height = 20;
		width = 70;
		value = new double[1];
		dval(value) = 0;
	}
	
	
	
	void draw() {
		
		ofSetColor(50, 50, 50);
		ofRect(x, y, width, height);
		ofNoFill();
		ofRect(x, y, width, height);
		ofFill();
		ofSetColor(255, 255, 255);
		if(focus && ((int)__round(ofGetElapsedTimef()*2.5))%2==0) {
			xmlgui::Resources::drawString(ofToString(dval(value),3) + "|", x+3, y+14);
		} else {
			xmlgui::Resources::drawString(ofToString(dval(value),3), x+3, y+14);
		}
		drawLabel(x+3, y);
		
		
	}
		// round() not supported in vs2010
	float __round(float number) {
		return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
	}
	bool touchDown(int x, int y, int id) {
		
		if(inside(x, y)) {
			parent->setKeyboardFocus(this);
			return true;
		} else {
			return false;
		}
	}
	
	bool keyPressed(int key) {
		if(key>='0' && key<='9') { // if it's a printable char
			dval(value) *= 10;
			dval(value) += key - '0';
			
			return true;
		} else if(key==8 || key==127) { // delete
			dval(value) /= 10;
			if(ABS(dval(value))<0.01) dval(value) = 0;
			return true;
		} else if(key==10 || key==13) {
			// this is a return
			return true;
		}
		return false;
	}
	
	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("Value","value", "doublefield", value));
	}
	
	string valueToString() { return ofToString(dval(value)); }
	void valueFromString(string inp) { dval(value) = atof(inp.c_str()); }
};
