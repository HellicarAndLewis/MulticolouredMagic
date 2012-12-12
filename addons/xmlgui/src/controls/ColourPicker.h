/*
 *  GuiColourPicker.h
 *  Gui
 *
 *  Created by Marek Bereza on 12/04/2010.
 *
 */

#pragma once

#include "LabeledControl.h"
class ColourPicker: public LabeledControl {
public:

	ColourPicker(): LabeledControl() {

		height = 55;
		width = 70;
		value = new int[1];
		ival(value) = 0;
	}



	void draw() {



		setRGBA(ival(value));
		ofRect(x, y, width, height);

		float h4 = height/4;
		ofSetColor(255, 255, 255);
		ofNoFill();
		ofRect(x, y, width, height);
		ofLine(x, y + h4,  x+width, y + h4);
		ofLine(x, y + h4*2,  x+width, y + h4*2);
		ofLine(x, y + h4*3,  x+width, y + h4*3);


		float c = ((ival(value)&0xFF0000)>>16);
		c /= 255.f;
		ofLine(x + width*c, y, x + width*c, y+h4);


		c = ((ival(value)&0xFF00)>>8);
		c /= 255.f;
		ofLine(x + width*c, y+h4, x + width*c, y+h4*2);


		c = ival(value)&0xFF;
		c /= 255.f;
		ofLine(x + width*c, y+h4*2, x + width*c, y+h4*3);


		c = 255 - ((ival(value)&0xFF000000)>>24);
		c /= 255.f;
		ofLine(x + width*c, y+h4*3, x + width*c, y+height);
		ofFill();

		xmlgui::Resources::drawString("red", x+3, y+h4-5);
		xmlgui::Resources::drawString("green", x+3, y+h4*2 - 5);
		xmlgui::Resources::drawString("blue", x+3, y+h4*3 - 5);
		xmlgui::Resources::drawString("alpha", x+3, y+height - 5);
		drawLabel(x+3, y);


	}


	bool touchDown(int _x, int _y, int touchId) {



		if(_y-y<height/4) { // r value
			ival(value) &= 0x0000FFFF;
			int red = (255.f*(_x-x)/width);
			ival(value) += red << 16;
		} else if(_y-y<(height*2)/4) { // g value
			ival(value) &= 0x00FF00FF;
			int green = (255.f*(_x-x)/width);
			ival(value) += green << 8;

		} else if(_y-y<(height*3)/4) { // b value
			ival(value) &= 0x00FFFF00;
			int blue = (255.f*(_x-x)/width);
			ival(value) += blue;

		} else { // a value
			ival(value) &= 0x00FFFFFF;
			int alpha = 255 - (255.f*(_x-x)/width);
			ival(value) += alpha << 24;

		}
		return true;
		/*
		if(_y-y<height/3) { // r value
			ival(value) &= 0x0000FFFF;
			int red = (255.f*(_x-x)/width);
			ival(value) += red << 16;
		} else if(_y-y<(height*2)/3) { // g value
			ival(value) &= 0x00FF00FF;
			int green = (255.f*(_x-x)/width);
			ival(value) += green << 8;
		} else { // b value
			ival(value) &= 0x00FFFF00;
			int blue = (255.f*(_x-x)/width);
			ival(value) += blue;

		}
		return true;*/
	}



	bool touchMoved(int _x, int _y, int touchId) {
		touchDown(_x, _y, touchId);
		return true;
	}



	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("Value","value", "intfield", value));
	}

	string valueToString() { return ofToString(ival(value)); }
	void valueFromString(string inp) { ival(value) = atoi(inp.c_str()); }
};
