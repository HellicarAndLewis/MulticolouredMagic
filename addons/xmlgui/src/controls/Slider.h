/*
 *  GuiSlider.h
 *  Gui
 *
 *  Created by Marek Bereza on 11/02/2010.
 *
 */

#pragma once

#include "Control.h"
#include "LabeledControl.h"
#include <math.h>
class Slider: public LabeledControl {
public:

	bool vertical;
	float min;
	float max;
	int bgColor;
	int fgColor;
	int borderColor;
	bool stepped;
	bool showValue;

	string sliderBGUrl;
	string sliderFGUrl;
	string sliderHandleUrl;
	ofImage *sliderBG, *sliderFG, *sliderHandle;
	Slider(): LabeledControl() {
		sliderBG = sliderFG = sliderHandle = NULL;
		vertical = false;
		height = 20;
		width = 100;
		stepped = false;
		value = new float[1];
		fval(value) = 0.5;
		min = 0;
		max = 1;
		bgColor = 0x505050;
		fgColor = 0x960000;
		borderColor = 0xFFFFFF;
		sliderBGUrl = "";
		sliderFGUrl = "";
		sliderHandleUrl = "";
		showValue = false;
	}

	void load() {
		if(fval(value)<min) fval(value) = min;
		if(fval(value)>max) fval(value) = max;
		sliderBG = xmlgui::Resources::getImage(sliderBGUrl);
		sliderFG = xmlgui::Resources::getImage(sliderFGUrl);
		sliderHandle = xmlgui::Resources::getImage(sliderHandleUrl);
		if(sliderBG!=NULL) {
			scalable = false;
			width = sliderBG->getWidth();
			height = sliderBG->getHeight();
		}

	}



	void draw() {
		//printf("%f %f %f %f\n", x, y, width, height);
		if(sliderBG!=NULL) {
			ofSetHexColor(0xFFFFFF);
			sliderBG->draw(x, y);
		} else {
			setRGBA(bgColor);
			ofRect(x, y, width, height);
		}

		float val = (fval(value)-min)/(max-min);

		if(sliderFG!=NULL) {
			ofSetHexColor(0xFFFFFF);
			ofVec2f abs = getAbsolutePosition();
			if(vertical) maskOn(abs.x, abs.y + height-height*val, width, height*val);
			else maskOn(abs.x, abs.y, width*val, height);
			sliderFG->draw(x, y);
			//ofRect(0, 0, ofGetWidth(), ofGetHeight());
			maskOff();
		} else {
			setRGBA(fgColor);

			if(vertical) ofRect(x, y+height-height*val, width, height*val);
			else ofRect(x, y, width*val, height);
		}

		if(sliderHandle!=NULL) {
			ofSetHexColor(0xFFFFFF);
			if(vertical) {

				sliderHandle->draw(x, y + (1.f - val)*(height - sliderHandle->getHeight()));
			} else {
				sliderHandle->draw(x+val*(width-sliderHandle->getWidth()), y);
			}
		}
		ofSetColor(255, 255, 255);
		if(showValue) {

			if(stepped) {
				string lab = name + "  " + ofToString((int)__round(fval(value)));
				drawCustomLabel(lab, x, y-3);
			} else {
				string lab = name + "  " + ofToString(fval(value), 3);
				drawCustomLabel(lab, x, y-3);
			}
		} else {
			drawLabel(x, y-3);
		}
		if(sliderBG==NULL) {
			setRGBA(borderColor);
			ofNoFill();
			ofRect(*this);
			ofFill();
		}
	}
	// round() not supported in vs2010
	float __round(float number) {
		return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
	}

	bool touchDown(int _x, int _y, int touchId) {
		float val = 0;
		if(vertical) {
			val = 1 - (_y-y)/height;
		} else {
			val = (_x-x)/width;
		}
		
		fval(value) = ofMap(val, 0, 1, min, max, true);
		if(stepped) {
			fval(value) = __round(fval(value));
		}
		
		return true;
	}

	bool touchMoved(int _x, int _y, int touchId) {
		touchDown(_x, _y, touchId);
		return true;
	}

	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("Vertical", "vertical", "toggle", &vertical));
		params.push_back(ParameterInfo("Min", "min", "floatfield", &min));
		params.push_back(ParameterInfo("Max", "max", "floatfield", &max));
		params.push_back(ParameterInfo("Stepped", "stepped", "toggle", &stepped));
		params.push_back(ParameterInfo("Value", "value", "floatfield", value));
		params.push_back(ParameterInfo("Show Value", "showvalue", "toggle", &showValue));
		params.push_back(ParameterInfo("BG Color", "bgColor", "colourpicker", &bgColor));
		params.push_back(ParameterInfo("Slider Color", "fgColor", "colourpicker", &fgColor));
		params.push_back(ParameterInfo("Border Color", "borderColor", "colourpicker", &borderColor));
		params.push_back(ParameterInfo("Slider BG", "sliderBGUrl", "file", &sliderBGUrl));
		params.push_back(ParameterInfo("Slider FG", "sliderFGUrl", "file", &sliderFGUrl));
		params.push_back(ParameterInfo("Slider Handle", "sliderHandleUrl", "file", &sliderHandleUrl));
	}

	string valueToString() {
		return ofToString(fval(value), 9);
	}

	void valueFromString(string inp) {
		fval(value) = atof(inp.c_str());
		//printf("Got value from string %s: %f\n", controlId.c_str(), fval(value));
	}
};
