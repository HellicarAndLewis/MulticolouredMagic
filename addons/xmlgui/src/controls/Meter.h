/*
 *  GuiMeter.h
 *  Gui
 *
 *  Created by Marek Bereza on 05/05/2010.
 *
 */

#pragma once

#include "LabeledControl.h"

#define hexValR(A)  ((A >> 16) & 0xff)
#define hexValG(A) ((A >> 8) & 0xff)
#define hexValB(A) ((A >> 0) & 0xff)


class Meter: public LabeledControl {
public:

	bool vertical;
	int bgColor;
	int fgTopColor;
	int fgBottomColor;
	float min;
	float max;

	string bgUrl;
	string fgUrl;

	ofImage *bg, *fg;

	// for drawing the vertex array for gradient
	float points[12];
	unsigned char colors[12];

	Meter(): LabeledControl() {
		min = 0;
		max = 1;
		vertical = true;
		height = 20;
		width = 100;

		value = new float[1];
		fval(value) = 0.f;
		bgColor = 0x505050;
		fgTopColor = 0xFF0000;
		fgBottomColor = 0x960000;
		bgUrl = fgUrl = "";
		calcColorArray();
		bg = NULL;
		fg = NULL;

	}


	void maskOn(int _x, int _y, int _w, int _h) {
		glEnable(GL_SCISSOR_TEST);
		glScissor(_x, ofGetHeight()-(_y+_h), _w, _h);
	}
	void maskOff() {
		glDisable(GL_SCISSOR_TEST);
	}






	void calcColorArray() {

		colors[0] = colors[3] = hexValR(fgTopColor);
		colors[1] = colors[4] = hexValG(fgTopColor);
		colors[2] = colors[5] = hexValB(fgTopColor);

		colors[6] = colors[9] =  hexValR(fgBottomColor);
		colors[7] = colors[10] = hexValG(fgBottomColor);
		colors[8] = colors[11] = hexValB(fgBottomColor);
	}

	void load() {
		bg = xmlgui::Resources::getImage(bgUrl);
		fg = xmlgui::Resources::getImage(fgUrl);

		if(bg!=NULL) {
			scalable = false;
			width = bg->getWidth();
			height = bg->getHeight();
		}
		calcColorArray();


	}
	void draw() {
		if(bg!=NULL) {
			ofSetHexColor(0xFFFFFF);
			bg->draw(x, y);
		} else {
			setRGBA(bgColor);
			ofRect(x, y, width, height);
		}

		ofPoint abs = getAbsolutePosition();
		float v = (fval(value)-min)/(max-min);
		if(vertical) maskOn(abs.x, abs.y + height-height*v, width, height*v);
		else maskOn(abs.x, abs.y, width*v, height);

		if(fg!=NULL) {
			ofSetHexColor(0xFFFFFF);
			fg->draw(x, y);
		} else {

			points[0] = x;
			points[1] = y;
			points[2] = 0;

			points[3] = x+width;
			points[4] = y;
			points[5] = 0;

			points[6] = x+width;
			points[7] = y+height;
			points[8] = 0;

			points[9] = x;
			points[10] = y+height;
			points[11] = 0;
#ifndef TARGET_OF_IPHONE
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, &points[0]);
			glColorPointer(3, GL_UNSIGNED_BYTE, 0, &colors[0]);
			glDrawArrays(GL_QUADS, 0, 12);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
#endif



//			ofRect(x, y, width, height);
		}

		maskOff();

		drawLabel();
	}




	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("Vertical", "vertical", "toggle", &vertical));
		params.push_back(ParameterInfo("Min", "min", "floatfield", &min));
		params.push_back(ParameterInfo("Max", "max", "floatfield", &max));
		params.push_back(ParameterInfo("BG Color", "bgColor", "colourpicker", &bgColor));
		params.push_back(ParameterInfo("Top Color", "fgTopColor", "colourpicker", &fgTopColor));
		params.push_back(ParameterInfo("Bottom Color", "fgBottomColor", "colourpicker", &fgBottomColor));
		params.push_back(ParameterInfo("BG Image", "bgUrl", "file", &bgUrl));
		params.push_back(ParameterInfo("Meter Image", "fgUrl", "file", &fgUrl));
	}
};
