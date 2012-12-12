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
 *  IntSlider.h, created by Marek Bereza on 07/02/2012.
 */



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
class IntSlider: public LabeledControl {
public:

	bool vertical;
	int min;
	int max;
	int bgColor;
	int fgColor;
	int borderColor;
	bool showValue;

	string sliderBGUrl;
	string sliderFGUrl;
	string sliderHandleUrl;
	ofImage *sliderBG, *sliderFG, *sliderHandle;
	IntSlider(): LabeledControl() {
		sliderBG = sliderFG = sliderHandle = NULL;
		vertical = false;
		height = 20;
		width = 100;

		value = new int[1];
		ival(value) = 0;
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
		if(ival(value)<min) ival(value) = min;
		if(ival(value)>max) ival(value) = max;
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

		float val = ((float)ival(value)-min)/(float)(max-min);

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


			string lab = name + "  " + ofToString(ival(value), 3);
			drawCustomLabel(lab, x, y-3);

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

		if(vertical) {
			float val = 1 - (float)(_y-y)/height;
			ival(value) = round((float)val*((float)max-min) + min);

		} else {
			float val = (float)(_x-x)/width;
			ival(value) = round((float)val*(max-min) + min);

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
		params.push_back(ParameterInfo("Min", "min", "intfield", &min));
		params.push_back(ParameterInfo("Max", "max", "intfield", &max));
		params.push_back(ParameterInfo("Value", "value", "intfield", value));
		params.push_back(ParameterInfo("Show Value", "showvalue", "toggle", &showValue));
		params.push_back(ParameterInfo("BG Color", "bgColor", "colourpicker", &bgColor));
		params.push_back(ParameterInfo("Slider Color", "fgColor", "colourpicker", &fgColor));
		params.push_back(ParameterInfo("Border Color", "borderColor", "colourpicker", &borderColor));
		params.push_back(ParameterInfo("Slider BG", "sliderBGUrl", "file", &sliderBGUrl));
		params.push_back(ParameterInfo("Slider FG", "sliderFGUrl", "file", &sliderFGUrl));
		params.push_back(ParameterInfo("Slider Handle", "sliderHandleUrl", "file", &sliderHandleUrl));
	}

	string valueToString() {
		return ofToString(ival(value));
	}

	void valueFromString(string inp) {
		ival(value) = atoi(inp.c_str());
		//printf("Got value from string %s: %f\n", controlId.c_str(), fval(value));
	}
};
