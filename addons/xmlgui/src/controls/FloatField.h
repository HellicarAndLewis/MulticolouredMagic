/*
 *  GuiFloatField.h
 *  Gui
 *
 *  Created by Marek Bereza on 11/02/2010.
 *
 */


#pragma once

#include "LabeledControl.h"
class FloatField: public LabeledControl {
public:

	int bgColor;
	int fgColor;
	FloatField(): LabeledControl() {

		height = 20;
		width = 70;
		value = new float[1];
		fval(value) = 0;
		fgColor = 0xFFFFFF;
		bgColor = 0x323232;
	}

		// round() not supported in vs2010
	float __round(float number) {
		return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
	}

	void draw() {

		setRGBA(bgColor);
		ofRect(x, y, width, height);
		setRGBA(fgColor);
		ofNoFill();
		ofRect(x, y, width, height);
		ofFill();
		if(focus && ((int)__round(ofGetElapsedTimef()*2.5))%2==0) {
			xmlgui::Resources::drawString(ofToString(fval(value),3) + "|", x+3, y+14);
		} else {
			xmlgui::Resources::drawString(ofToString(fval(value),3), x+3, y+14);
		}
		drawLabel(x, y-3);


	}
	bool keyPressed(int key) {
		if(key>='0' && key<='9') { // if it's a printable char
			fval(value) *= 10;
			fval(value) += key - '0';

			return true;
		} else if(key==8 || key==127) { // delete
			fval(value) /= 10;
			if(ABS(fval(value))<0.01) fval(value) = 0;
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
		params.push_back(ParameterInfo("Value","value", "floatfield", value));
		params.push_back(ParameterInfo("BG Color", "bgColor", "colourpicker", &bgColor));
		params.push_back(ParameterInfo("FG Color", "fgColor", "colourpicker", &fgColor));
	}

	string valueToString() { return ofToString(fval(value)); }
	void valueFromString(string inp) { fval(value) = atof(inp.c_str()); }
};
