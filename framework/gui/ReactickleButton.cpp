/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
	this->setup(name);
	this->name = name;
	listener = NULL;
	currTouchId = -1;
	down = false;
}
void ReactickleButton::setup(string name) {
	screenshot = ImageCache::getImage(IMAGE_ROOT+"apps/"+name+".png");
	width = screenshot->getWidth();
	height = screenshot->getHeight();
	
	//height *= 0.8;
	border.setup(ImageCache::getImage("img/dropShadow.png"), 4);
}
void ReactickleButton::draw() {
	if(down) {
		ofSetHexColor(0x999999);
	} else {
		ofSetHexColor(0xFFFFFF);
	}
	screenshot->draw(x, y, width, height);
	//ofSetHexColor(0xFF0000);
	//ofDrawBitmapString(name, x, y);
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
		if(inside(xx, yy) && ABS(startX - xx)<10) {
			//printf("%d\n", ABS(startX - xx));
			if(listener!=NULL) listener->reactickleSelected(name);
		}
	}
	return down;
	
}