/*
 *  GuiText.h
 *  Gui
 *
 *  Created by Marek Bereza on 28/03/2010.
 *
 */


#pragma once

#include "Control.h"
class Text: public xmlgui::Control {
public:

	int color;
	Text(): Control() {

		color = 0xFFFFFF;
		height = 20;
		width = 70;
		value = new string;
	}


	void draw() {
		setRGBA(color);
		xmlgui::Resources::drawString(sval(value), x+3, y+14);
	}

	void getParameterInfo(vector<ParameterInfo> &params) {
		params.push_back(ParameterInfo("Value", "value","text",value));
		params.push_back(ParameterInfo("Text Color", "color", "colourpicker", &color));
	}

	string valueToString() { return sval(value); }
	void valueFromString(string inp) { sval(value) = inp; }
};
