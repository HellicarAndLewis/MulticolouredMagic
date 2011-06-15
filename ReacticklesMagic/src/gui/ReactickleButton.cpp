/**
 * ReactickleButton.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

#include "ReactickleButton.h"
#include "ImageCache.h"
#include "constants.h"

ReactickleButton::ReactickleButton(string name) {
	screenshot = ImageCache::getImage(IMAGE_ROOT+"apps/"+name+".png");
	width = screenshot->getWidth();
	height = screenshot->getHeight();
	
	height *= 0.8;
	border.setup(ImageCache::getImage("img/dropShadow.png"), 4);
	this->name = name;
	listener = NULL;
	currTouchId = -1;
	down = false;
}

void ReactickleButton::draw() {
	if(down) {
		ofSetHexColor(0x999999);
	} else {
		ofSetHexColor(0xFFFFFF);
	}
	screenshot->draw(x, y-20);
	ofSetHexColor(0xFF0000);
	ofDrawBitmapString(name, x, y);
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
		if(inside(xx, yy) && ABS(startX - xx)<5) {
			//printf("%d\n", ABS(startX - xx));
			if(listener!=NULL) listener->reactickleSelected(name);
		}
	}
	return down;
	
}