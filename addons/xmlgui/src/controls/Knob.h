/*
 *  GuiKnob.h
 *  Gui
 *
 *  Created by Marek Bereza on 15/04/2010.
 *
 */


#pragma once

#include "LabeledControl.h"

class Knob: public LabeledControl {
public:

	float min;
	float max;
	int bgColor;
	int fgColor;
	bool stepped;
	bool direct;
	float touchAngle;
	float minAngle;
	float maxAngle;
	string bgImageUrl, needleImageUrl;
	ofImage *bgImage, *needleImage;

	Knob(): LabeledControl() {
		direct = false;
		touchAngle = 0;
		height = 80;
		width = 80;
		stepped = false;
		value = new float[1];
		fval(value) = 0.5;
		min = 0;
		max = 1;
		bgColor = 0x505050;
		fgColor = 0x960000;
		maxAngle = 330;
		minAngle = 30;
		bgImageUrl = needleImageUrl = "";
		bgImage = needleImage = NULL;
	}

	void load() {
		if(fval(value)<min) fval(value) = min;
		if(fval(value)>max) fval(value) = max;


		bgImage = xmlgui::Resources::getImage(bgImageUrl);
		needleImage = xmlgui::Resources::getImage(needleImageUrl);
		if(needleImage!=NULL) {
			needleImage->setAnchorPercent(0.5, 0.5);
		}
		if(bgImage!=NULL) {
			scalable = false;
			width = bgImage->getWidth();
			height = bgImage->getHeight();
		}

	}



	void draw() {
		float radius = width/2;
		ofPoint center = ofPoint(x + radius, y + radius);

		if(bgImage!=NULL) {
			ofSetHexColor(0xFFFFFF);
			bgImage->draw(x,y, width, height);
		} else {
			setRGBA(bgColor);
			ofCircle(center.x, center.y, radius);
		}

		float angle = (fval(value)-min)/(max-min);

		angle *= (maxAngle - minAngle);
		angle += minAngle;


		if(needleImage!=NULL) {
			glPushMatrix();
			glTranslatef(x + radius, y+radius, 0);
			glRotatef(angle, 0, 0, 1);
			ofSetHexColor(0xFFFFFF);
			needleImage->draw(0,0, width, height);
			glPopMatrix();
		} else {
			setRGBA(fgColor);
			ofLine(center.x, center.y, center.x + radius*cos(ofDegToRad(angle)), center.y + radius*sin(ofDegToRad(angle)));
			ofSetColor(255, 255, 255);
		}
		drawLabel();
	}




	bool touchDown(int _x, int _y, int touchId) {

		ofPoint fromCenter = ofPoint((_x-x)-(width/2), (_y-y)-(width/2));
		touchAngle = atan2(fromCenter.y, fromCenter.x);
		if(direct) {
			directControl(touchAngle);
		}
		return true;
	}


		// round() not supported in vs2010
	float __round(float number) {
		return number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5);
	}

	void directControl(float angle) {

		// limit the angle
		//if(angle>maxAngle) angle = maxAngle;
		//else if(angle<minAngle) angle = minAngle;

		if(angle<0) angle += 360;
		// convert angle to value
		angle -= minAngle;
		angle /= maxAngle - minAngle;
		angle *= max - min;
		angle += min;
		fval(value) = angle;


		if(fval(value)>max) {
			//printf("Limiting max because %f > max\n", fval(value));
			fval(value) = max;

		} else if(fval(value)<min) {
			//printf("Limiting min because %f < min\n", fval(value));
			fval(value) = min;
		}


		// do stepped if needed
		if(stepped) {
			fval(value) = __round(fval(value));
		}

	}

	bool touchMoved(int _x, int _y, int touchId) {
		ofPoint fromCenter = ofPoint((_x-x)-(width/2), (_y-y)-(width/2));
		float newTouchAngle = ofRadToDeg(atan2(fromCenter.y, fromCenter.x));

		if(direct) {
			directControl(newTouchAngle);
		} else {
			float diff = newTouchAngle-touchAngle;
			diff /= maxAngle - minAngle; // this is the normalized version of how much the value has changed
			diff *= max - min; // this is the value scaled version.


			// this stops that weird jump thing happening from atan2 wrapping
			if(newTouchAngle>0 && touchAngle<0 || newTouchAngle<0 && touchAngle>0) {
				touchAngle = newTouchAngle;
				return true;
			}
			fval(value) += diff;

			if(fval(value)>max) fval(value) = max;
			else if(fval(value)<min) fval(value) = min;

			touchAngle = newTouchAngle;


			if(stepped) {
				fval(value) = __round(fval(value));
			}
		}

		return true;
	}
		// round() not supported in vs2010

	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("Min", "min", "floatfield", &min));
		params.push_back(ParameterInfo("Max", "max", "floatfield", &max));
		params.push_back(ParameterInfo("Stepped", "stepped", "toggle", &stepped));
		params.push_back(ParameterInfo("Direct Control", "direct", "toggle", &direct));
		params.push_back(ParameterInfo("Value", "value", "floatfield", value));
		params.push_back(ParameterInfo("Min Angle", "minAngle", "floatfield", &minAngle));
		params.push_back(ParameterInfo("Max Angle", "maxAngle", "floatfield", &maxAngle));
		params.push_back(ParameterInfo("BG Color", "bgColor", "colourpicker", &bgColor));
		params.push_back(ParameterInfo("Dial Color", "fgColor", "colourpicker", &fgColor));
		params.push_back(ParameterInfo("Background Image", "bgImage", "file", &bgImageUrl));
		params.push_back(ParameterInfo("Needle Image", "needleImage", "file", &needleImageUrl));
	}

	string valueToString() {
		return ofToString(fval(value), 9);
	}

	void valueFromString(string inp) {
		fval(value) = atof(inp.c_str());
	}
};
