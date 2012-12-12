/*
 *  Gui2DSlider.h
 *  Gui
 *
 *  Created by Marek Bereza on 12/02/2010.
 *
 */
#pragma once

#include "LabeledControl.h"

class Slider2D: public LabeledControl {
public:
	
	float minX;
	float minY;
	float maxX;
	float maxY;
	bool showValue;
	
	Slider2D(): LabeledControl() {
		minX = -1;
		minY = -1;
		maxX = 1;
		maxY = 1;
		height = 100;
		width = 100;
		
		value = new float[2];
		faval(value, 0) = 0.5;
		faval(value, 1) = 0.5;
		showValue = false;
	}
	
	void draw() {
		
		ofSetColor(80, 80, 80);
		ofRect(x, y, width, height);
		ofSetColor(255, 255, 255);
		float xVal = ofMap(faval(value, 0), minX, maxX, 0, 1);
		float yVal = ofMap(faval(value, 1), minY, maxY, 0, 1);
		
		ofCircle(x+xVal*width,y+yVal*height, 3);
		if(showValue) {
			drawCustomLabel(name + "    " + ofToString(faval(value, 0), 3) + "  " + ofToString(faval(value, 1), 3), x, y);
		} else {
			drawLabel(x, y);
		}
		
	}
	
	bool touchDown(int _x, int _y, int touchId) {
		faval(value, 1) = ofMap((_y-y)/height, 0, 1, minY, maxY);
		faval(value, 0) = ofMap((_x-x)/width, 0, 1, minX, maxX);
		return true;
	}
	
	bool touchMoved(int _x, int _y, int touchId) {
		touchDown(_x, _y, touchId);
		return true;
	}
	
	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("x", "xval", "slider", value));
		params.push_back(ParameterInfo("y", "yval", "slider", ((float*)value)+1));
		params.push_back(ParameterInfo("min x", "minX", "slider", &minX));
		params.push_back(ParameterInfo("max x", "maxX", "slider", &maxX));
		params.push_back(ParameterInfo("min y", "minY", "slider", &minY));
		params.push_back(ParameterInfo("max y", "maxY", "slider", &maxY));
	}
	
	
	string valueToString() { 
		return ofToString(faval(value, 0), 9) + "," + ofToString(faval(value, 1), 9);		
	}
	
	void valueFromString(string inp) { 
		vector<string> vals = ofSplitString(inp, ",");
		if(vals.size()==2) {
			faval(value, 0) = atof(vals[0].c_str());
			faval(value, 1) = atof(vals[1].c_str());
		}
	}
};