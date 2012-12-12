/*
 *  GuiButton.h
 *  Gui
 *
 *  Created by Marek Bereza on 11/02/2010.
 *
 */
#pragma once

#include "LabeledControl.h"
class PushButton: public LabeledControl {
public:

	string upImgUrl;
	string downImgUrl;
	ofImage *upImg, *downImg;
	int upColor;
	int downColor;
	int overColor;
	PushButton(): LabeledControl() {
		height = 20;
		width = 110;
		upImg = downImg = NULL;
		upImgUrl = downImgUrl = "";
		upColor = 0x555555;
		downColor = 0;
		overColor = 0xCCCCCC;
	}

	void load() {
		upImg = xmlgui::Resources::getImage(upImgUrl);
		downImg = xmlgui::Resources::getImage(downImgUrl);
		if(upImg!=NULL) {
			scalable = false;
			width = upImg->getWidth();
			height = upImg->getHeight();
		} else if(downImg!=NULL) {
			scalable = false;
			width = downImg->getWidth();
			height = downImg->getHeight();
		}
	}


	void draw() {

		if(down) {
			if(downImg!=NULL) {
				ofSetHexColor(0xFFFFFF);
				downImg->draw(x, y);
			} else {
				setRGBA(downColor);
				ofRect(x, y, width, height);
			}
		} else if(over && upImg==NULL && downImg==NULL) { // draw grey bg for nice menus
			setRGBA(overColor);
			ofRect(x, y, width, height);
		} else {
			setRGBA(upColor);
			if(upImg!=NULL) {
				upImg->draw(x, y);
			} else {
				ofRect(x, y, width, height);
			}
		}

		drawLabel(x+3, y+14);
	}


	virtual void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("Button Up", "upImgUrl", "file", &upImgUrl));
		params.push_back(ParameterInfo("Button Down", "downImgUrl", "file", &downImgUrl));
		params.push_back(ParameterInfo("Up Color", "upColor", "colourpicker", &upColor));
		params.push_back(ParameterInfo("Down Color", "downColor", "colourpicker", &downColor));
		params.push_back(ParameterInfo("over Color", "overColor", "colourpicker", &overColor));

	}
};
