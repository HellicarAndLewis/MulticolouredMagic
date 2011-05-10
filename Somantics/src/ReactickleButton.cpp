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
	border.setup(ImageCache::getImage("img/dropShadow.png"), 4);
	this->name = name;
	listener = NULL;
	currTouchId = -1;
	down = false;
}

void ReactickleButton::draw() {
	ofSetHexColor(0xFFFFFF);
	screenshot->draw(x, y, width, height);
	if(down) {
		ofVec2f points[4];
		points[0] = ofVec2f(x, y);
		points[1] = ofVec2f(x+width, y);
		points[2] = ofVec2f(x+width, y+height);
		points[3] = ofVec2f(x, y+height);
		border.draw(points, ofColor(255, 255, 255, 255));
	}
	ofDrawBitmapString(name, x+2, y+16);
}

void ReactickleButton::setListener(ReactickleButtonListener *listener) {
	this->listener = listener;
}


bool ReactickleButton::touchDown(float xx, float yy, int tid) {
	if(inside(xx, yy)) {
		currTouchId = tid;
		down = true;
		startX = xx;
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
		if(inside(xx, yy) && ABS(startX - xx)<2) {
			printf("%d\n", ABS(startX - xx));
			if(listener!=NULL) listener->reactickleSelected(name);
		}
	}
	return down;
	
}