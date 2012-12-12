/*
 *  GuiPanner.h
 *  Snowboard
 *
 *  Created by Marek Bereza on 09/12/2010.
 *

 *  TODO: Doesn't work for graphics files, just plain colours I don't think.
 */


#pragma once

#include "Slider.h"
class Panner: public Slider {
public:


	void draw() {

		if(sliderBG!=NULL) {
			ofSetHexColor(0xFFFFFF);
			sliderBG->draw(x, y);
		} else {
			setRGBA(bgColor);
			ofRect(x, y, width, height);
		}

		float val = (fval(value)-min)/(max-min);

		if(sliderFG!=NULL) {
			ofSetHexColor(0xFFFFFF);
			ofPoint abs = getAbsolutePosition();
			if(vertical) maskOn(abs.x, abs.y + height-height*val, width, height*val);
			else maskOn(abs.x, abs.y, width*val, height);
			sliderFG->draw(x, y);
			maskOff();
		} else {
			setRGBA(fgColor);

			if(vertical) ofRect(x, y + height - height*val , width, height*val - height/2);
			else ofRect(x+width/2, y, width*val - width/2, height);
		}

		if(sliderHandle!=NULL) {
			ofSetHexColor(0xFFFFFF);
			if(vertical) {

				sliderHandle->draw(x, y + (1.f - val)*(height - sliderHandle->getHeight()));
			} else {
				sliderHandle->draw(x+val*(width-sliderHandle->getWidth()), y);
			}
		}
		ofSetColor(255, 255, 255);
		if(showValue) {

			if(stepped) {
				string lab = name + "  " + ofToString((int)__round(fval(value)));
				drawCustomLabel(lab, x, y-3);
			} else {
				string lab = name + "  " + ofToString(fval(value), 3);
				drawCustomLabel(lab, x, y-3);
			}
		} else {
			drawLabel(x, y-3);
		}
	}
};
