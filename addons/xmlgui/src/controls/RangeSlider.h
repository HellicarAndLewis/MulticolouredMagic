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
 *  RangeSlider.h, created by Marek Bereza on 05/11/2012.
 */


#pragma once

#include "Control.h"
#include "LabeledControl.h"
#include <math.h>
class RangeSlider: public LabeledControl {
public:

	bool vertical;
	float min;
	float max;
	int bgColor;
	int fgColor;
	int borderColor;
	bool stepped;
	bool showValue;
	ofVec2f lastTouch;

	string sliderBGUrl;
	string sliderFGUrl;
	string sliderHandleUrl;
	ofImage *sliderBG, *sliderFG, *sliderHandle;
	RangeSlider(): LabeledControl() {
		sliderBG = sliderFG = sliderHandle = NULL;
		vertical = false;
		height = 20;
		width = 100;
		stepped = false;
		value = new float[2];
		faval(value, 0) = 0.3333;
		faval(value, 1) = 0.6667;
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


	void limitValues() {
		if(faval(value,0)<min) faval(value,0) = min;
		if(faval(value,0)>max) faval(value,0) = max;
		if(faval(value,1)<min) faval(value,1) = min;
		if(faval(value,1)>max) faval(value,1) = max;
	}

	void load() {
		limitValues();


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

		float val1 = (faval(value, 0)-min)/(max-min);
		float val2 = (faval(value, 1)-min)/(max-min);

		float minVal = MIN(val1, val2);
		float maxVal = MAX(val1, val2);
		float size = maxVal - minVal;

		if(sliderFG!=NULL) {
			ofSetHexColor(0xFFFFFF);
			ofVec2f abs = getAbsolutePosition();
			if(vertical) maskOn(abs.x, abs.y + height-height*maxVal, width, height*size);
			else maskOn(abs.x + width*minVal, abs.y, width*size, height);
			sliderFG->draw(x, y);
			//ofRect(0, 0, ofGetWidth(), ofGetHeight());
			maskOff();
		} else {
			setRGBA(fgColor);

			if(vertical) ofRect(x, y+height-height*maxVal, width, height*size);
			else ofRect(x + width*minVal, y, width*size, height);
		}

		if(sliderHandle!=NULL) {
			ofSetHexColor(0xFFFFFF);
			if(vertical) {

				sliderHandle->draw(x, y + (1.f - minVal)*(height - sliderHandle->getHeight()));
				sliderHandle->draw(x, y + (1.f - maxVal)*(height - sliderHandle->getHeight()));
			} else {
				sliderHandle->draw(x+minVal*(width-sliderHandle->getWidth()), y);
				sliderHandle->draw(x+maxVal*(width-sliderHandle->getWidth()), y);
			}
		}
		ofSetColor(255, 255, 255);
		if(showValue) {

			if(stepped) {
				string lab = name + "  " + ofToString((int)__round(faval(value, 0))) + " - " + ofToString((int)__round(faval(value, 1)));
				drawCustomLabel(lab, x, y-3);
			} else {
				string lab = name + "  " + ofToString(faval(value, 0), 3) + " - " + ofToString(faval(value, 1), 3);
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

	bool touchMoved(int _x, int _y, int touchId) {

		float val = 0;


		if(vertical) {
			val = 1 - (_y-y)/height;
		} else {
			val = (_x-x)/width;

		}

		// val is now normalized

		// so scale it
		val = val*(max-min) + min;

		// and step if needed
		if(stepped) {
			val = __round(val);
		}

		// make sure they're in order
		float mn = MIN(faval(value, 0), faval(value, 1));
		float mx = MAX(faval(value, 0), faval(value, 1));
		faval(value, 0) = mn;
		faval(value, 1) = mx;

		// whichever one is closest gets it
		float distToMin = ABS(val - faval(value, 0));
		float distToMax = ABS(val - faval(value, 1));

		bool moving = false;

		// if we're in between both ends, maybe we drag
		if(mn<=val && mx>=val) {
			float minDist = MIN(distToMin, distToMax);
			// unscale it
			minDist /= (max-min);
			//printf("Mindist: %f\n", minDist);
			if(minDist>0.025) {
				moving = true;
			}
		}


		if(moving) {
			if(lastTouch.x!=-1 && lastTouch.y!=-1) {
				// so we are moving
				float delta = 0;
				// calculate normalized difference
				if(vertical) {
					delta = _y - lastTouch.y;
					delta /= -height;
				} else {
					delta = _x - lastTouch.x;
					delta /= width;
				}

				// scale
				delta *= max - min;
				faval(value, 0) += delta;
				faval(value, 1) += delta;
				limitValues();
			}
		} else {

			if(distToMin<distToMax) {
				faval(value, 0) = val;
			} else {
				faval(value, 1) = val;
			}
		}
		lastTouch = ofVec2f(_x, _y);

		return true;
	}

	bool touchDown(int _x, int _y, int touchId) {
		lastTouch = ofVec2f(-1, -1);
		touchMoved(_x, _y, touchId);
		return true;
	}

	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		float * val = (float*)value;
		params.push_back(ParameterInfo("Vertical", "vertical", "toggle", &vertical));
		params.push_back(ParameterInfo("Min", "min", "floatfield", &min));
		params.push_back(ParameterInfo("Max", "max", "floatfield", &max));
		params.push_back(ParameterInfo("Stepped", "stepped", "toggle", &stepped));
		params.push_back(ParameterInfo("Value", "min val", "floatfield", &val[0]));
		params.push_back(ParameterInfo("Value", "max val", "floatfield", &val[1]));
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

