/**
 * ReactickleButton.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

#include "ReactickleButton.h"
#include "ImageCache.h"
ReactickleButton::ReactickleButton(string name, string screenshotUrl) {
	screenshot = ImageCache::getImage(screenshotUrl);
	width = screenshot->getWidth();
	height = screenshot->getHeight();
	this->name = name;
	listener = NULL;
	currTouchId = -1;
	down = false;
}

void ReactickleButton::draw() {
	ofSetHexColor(0xFFFFFF);
	screenshot->draw(x, y, width, height);
	ofDrawBitmapString(name, x+2, y+16);
}

void ReactickleButton::setListener(ReactickleButtonListener *listener) {
	this->listener = listener;
}


bool ReactickleButton::touchDown(float xx, float yy, int tid) {
	if(inside(xx, yy)) {
		currTouchId = tid;
		down = true;
		startY = yy;
	}
	
	return down;
}

bool ReactickleButton::touchMoved(float xx, float yy, int tid) {
	if(inside(xx, yy) && tid==currTouchId) {
		down = true;
	} else {
		down = false;
	}
	return down;
}

bool ReactickleButton::touchUp(float xx, float yy, int tid) {
	
	if(currTouchId==tid) {
		currTouchId = -1;
		down = false;
		if(inside(xx, yy) && ABS(startY - yy)<2) {
			if(listener!=NULL) listener->reactickleSelected(name);
		}
	}
	return down;
	
}