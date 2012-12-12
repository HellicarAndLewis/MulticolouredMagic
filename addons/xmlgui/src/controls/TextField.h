/*
 *  GuiTextField.h
 *  Gui
 *
 *  Created by Marek Bereza on 11/02/2010.
 *
 */

#pragma once

#include "LabeledControl.h"
class TextField: public LabeledControl {
public:

	TextField(): LabeledControl() {
		
		height = 20;
		width = 70;
		value = new string;
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
			xmlgui::Resources::drawString(sval(value) + "|", x+3, y+14);
		} else {
			xmlgui::Resources::drawString(sval(value), x+3, y+14);
		}
		drawLabel(x+3, y);
		
		
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
		if(key>=32 && key<=126) { // if it's a printable char
			sval(value) += (char*)&key;
			return true;
		} else if((key==8 || key==127) && sval(value).size()>0) { // delete
			sval(value) = sval(value).erase(sval(value).size()-1);
			return true;
		} else if(key==10 || key==13) {
			// this is a return
			return true;
		}
		return false;
	}
	
	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("Value", "value","textfield",value));
	}
	string valueToString() { return sval(value); }
	void valueFromString(string inp) { sval(value) = inp; }
};