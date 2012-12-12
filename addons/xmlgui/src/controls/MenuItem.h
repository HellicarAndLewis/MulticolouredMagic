/**
 * MenuItem.h
 * emptyExample
 *
 * Created by Marek Bereza on 27/06/2011.
 *
 */
#pragma once
#include "Control.h"
#include "Resources.h"
class MenuItem: public xmlgui::Control {
public:
	MenuItem(): Control() {
		width = 100;
		height = 20;
	}
	void draw() {
		/*if(down) {
			ofSetHexColor(0);
		} else*/ if(over) {
			ofSetHexColor(0xCCCCCC);
		} else {
			ofSetHexColor(0xFFFFFF);
		}
		ofRect(x, y, width, height);
		/*if(down) ofSetHexColor(0xFFFFFF);
		else */ofSetHexColor(0);
		xmlgui::Resources::drawString(name, x + 3, y + 14);
	}
	
};