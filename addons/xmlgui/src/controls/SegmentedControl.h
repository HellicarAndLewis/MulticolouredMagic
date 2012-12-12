/*
 *  GuiSegmentedControl.h
 *  Gui
 *
 *  Created by Marek Bereza on 13/02/2010.
 *
 */

#pragma once

#include "LabeledControl.h"
#include "PushButton.h"



class SegmentedControl: public LabeledControl {
public:


	string options;
	bool vertical;
	vector<string> opts;
	int fgColor;
	int bgColor;
	int borderColor;

	SegmentedControl(): LabeledControl() {
		value = new int[1];
		ival(value) = 0;
		height = 20;
		vertical = false;
		fgColor = 0xC80000;
		borderColor = 0;
		bgColor = 0x444444;
	}

	void load() {
		opts = ofSplitString(options, "|");
		//height = 20;
		if(value==NULL) {
			value = new int[1];
			ival(value) = 0;
		}

	}
	void addOption(string opt) {
		if(options=="") options = opt;
		else options += string("|") + opt;
		opts = ofSplitString(options, "|");
	}
	void draw() {
		drawLabel(x, y-3);
		int size = opts.size();
		if(size==0) {
			ofSetColor(100, 100, 100);
			ofRect(x,y,width,height);
		}


		if(vertical) {
			for(int i = 0; i < size; i++) {
				ofRectangle r(x, y+(height/size)*i, width, (height/size)-3);


				if(i==ival(value)) {
					setRGBA(fgColor);
					ofRect(r);
				} else {
					setRGBA(bgColor);
					ofRect(r);
				}

				setRGBA(labelColor);
				xmlgui::Resources::drawString(opts[i], x+3, y + (height/size)*(i+1)-3);
				setRGBA(borderColor);
				ofNoFill();
				ofRect(r);
				ofFill();
			}
		} else {
			for(int i = 0; i < size; i++) {

				ofRectangle r(x+(width/size)*i, y, (width/size)-3, height);
				if(i==ival(value)) {
					setRGBA(fgColor);
					ofRect(r);
				} else {
					setRGBA(bgColor);
					ofRect(r);
				}

				setRGBA(labelColor);
				xmlgui::Resources::drawString(opts[i], x+(width/size)*i+3, y+height-3);
				setRGBA(borderColor);
				ofNoFill();
				ofRect(r);
				ofFill();
			}
		}

	}

	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		ofJoinString(opts, "|");
		params.push_back(ParameterInfo("Options", "options","textfield",&options));
		params.push_back(ParameterInfo("Value", "value","intfield",value));
		params.push_back(ParameterInfo("vertical", "vertical", "toggle", &vertical));
		params.push_back(ParameterInfo("Border Color", "borderColor", "colourpicker", &borderColor));
		params.push_back(ParameterInfo("Selected Color", "fgColor", "colourpicker", &fgColor));
		params.push_back(ParameterInfo("BG Color", "bgColor", "colourpicker", &bgColor));

	}


	bool touchDown(int _x, int _y, int touchId) {
		if(vertical) {
			ival(value) = (int)((float)opts.size()*(_y-y)/height);
		} else {
			ival(value) = (int)((float)opts.size()*(_x-x)/width);
		}
		return true;
	}
	bool touchMoved(int _x, int _y, int touchId) {
		return touchDown(_x, _y, touchId);
	}

	string valueToString() {
		return ofToString(ival(value));
	}

	void valueFromString(string inp) {
		ival(value) = atoi(inp.c_str());
	}
};
