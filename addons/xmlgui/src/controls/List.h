/*
 *  GuiDropDown.h
 *  Gui
 *
 *  Created by Marek Bereza on 05/05/2010.
 *
 */

#pragma once

#define SCROLL_NONE 0
#define SCROLL_UP 2
#define SCROLL_DOWN -2

#include "LabeledControl.h"

#define hexValR(A)  ((A >> 16) & 0xff)
#define hexValG(A) ((A >> 8) & 0xff)
#define hexValB(A) ((A >> 0) & 0xff)


class List: public LabeledControl {
public:

	int bgColor;
	int fgColor;

	int scrollOffset;
	int itemHeight;
	int scrollerWidth;
	int scrolling;
	bool dragging;

	string options;
	List(): LabeledControl() {
		bgColor = 0x333333;
		fgColor = 0xFFFFFF;
		dragging = false;
		scrolling = SCROLL_NONE;
		itemHeight = scrollerWidth = 22;
		scrollOffset = 0;
		value = new int[1];
		ival(value) = -1;
		width = 100;
		height = 100;
		x = y = 0;
	}

	void load() {
		items = ofSplitString(options, "|");

	}

	void addItem(string tem) {
		items.push_back(tem);
	}
	void clearItems() {
		items.clear();
	}

	string getSelectedString() {
		if(ival(value)==-1) return "";
		else return items[ival(value)];
	}

	void setSelection(string itemName) {
		for(int i = 0; i < items.size(); i++) {
			if(items[i]==itemName) {
				ival(value) = i;
				return;
			}
		}
		ival(value) = -1;
	}
	void draw() {

		scrollOffset += scrolling;
		if(dragging) {
			scrolling = SCROLL_NONE;
		}
		if(scrollOffset>0) scrollOffset = 0;

		if(needsScrollbar() && items.size()*itemHeight+scrollOffset<height) {
			scrollOffset = height - items.size()*itemHeight;
		}

		setRGBA(bgColor);
		ofRect(x, y, width, height);

		//glEnable(GL_SCISSOR_TEST);

		ofNoFill();
		setRGBA(fgColor);
		ofRect(x, y, width, height);

		ofPoint abs = getAbsolutePosition();
		//maskOn(abs.x, abs.y, width, height);




		for(int i =0; i < items.size(); i++) {
			setRGBA(fgColor);


			ofRect(x, scrollOffset + y + i*itemHeight, width-scrollerWidth, itemHeight);

			if(i==ival(value)) ofSetHexColor(0x00FF00);
			xmlgui::Resources::drawString(items[i], x+5, scrollOffset + y + (i+1)*itemHeight-4);

			// only draw as much as we need
			//if((i+1)*itemHeight>height) break;
		}
		ofNoFill();
		if(needsScrollbar()) setRGBA(fgColor);
		else setRGBA(blendColor(fgColor, bgColor, 0.2));
		ofLine(x+width-scrollerWidth, y+height/2, x+width, y+height/2);
		ofLine(x+width-scrollerWidth, y, x+width-scrollerWidth, y+height);
		xmlgui::Resources::drawString("UP", 4+x+width-scrollerWidth, y+height/2 - 5);
		xmlgui::Resources::drawString("DN", 4+x+width-scrollerWidth, y+height/2 + 15);
		//maskOff();
		ofFill();
		drawLabel();
	}


	int blendColor(int color1, int color2, float amt) {
		float r = hexValR(color1)*amt + hexValR(color2)*(1.f-amt);
		float g = hexValG(color1)*amt + hexValG(color2)*(1.f-amt);
		float b = hexValB(color1)*amt + hexValB(color2)*(1.f-amt);

		return colorFloat255ToHex(r, g, b);
	}

	int colorFloat255ToHex(float r, float g, float b) {
		int rr = r;
		int gg = g;
		int bb = b;
		return (rr << 16) + (gg << 8) + bb;
	}


	bool needsScrollbar() {
		return items.size()*itemHeight>height;
	}
	bool touchDown(int _x, int _y, int touchId) {
		if(_x>x+width-scrollerWidth && needsScrollbar()) {
			// scrolling with scroll bars
			float yy = _y - y;
			yy /= height;
			if(yy<0.5) {
				scrolling = SCROLL_UP;
			} else {
				scrolling = SCROLL_DOWN;
			}

		} else {
			scrolling = SCROLL_NONE;
			lastMouse = ofPoint(_x, _y);
		}
		return true;
	}

	bool touchMoved(int _x, int _y, int touchId) {
		if(_x>x+width-scrollerWidth) {

		} else if(needsScrollbar()) {
			dragging = true;
			scrolling = _y - lastMouse.y;
			// do some drag scrolling
			lastMouse = ofPoint(_x, _y);
		}
		return true;
	}


	bool touchUp(int _x, int _y, int touchId) {
		printf("%d %d %d\n", dragging, _x==lastMouse.x, _y==lastMouse.y);
		if(!dragging && ofDistSquared(_x, _y, lastMouse.x, lastMouse.y)<50) {
			
			// click!
			printf("Click zone\n");
			float offset = (float)(_y - y - scrollOffset)/itemHeight;
			int i = floor(offset);
			if(i>=0 && i < items.size()) {
				ival(value) = i;

#pragma warning this was uncommented code before I imported the widgets to the new ofxXmlGui
				if(parent!=NULL) {
					xmlgui::Event e(this, xmlgui::Event::TOUCH_UP);
					for(int i = 0; i < parent->listeners.size(); i++) {
						parent->listeners[i]->controlChanged(&e);
					}
				}
			}
		} else {
			touchMoved(_x, _y, touchId);
		}
		dragging = false;
		scrolling = SCROLL_NONE;
		return true;
	}

	void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("BG Color", "bgColor", "colourpicker", &bgColor));
		params.push_back(ParameterInfo("FG Color", "fgColor", "colourpicker", &fgColor));
		params.push_back(ParameterInfo("Options", "options","textfield",&options));
	}



	ofPoint lastMouse;
	vector<string> items;
	string valueToString() { return ofToString(ival(value)); }
	void valueFromString(string inp) { ival(value) = atoi(inp.c_str()); }
};
