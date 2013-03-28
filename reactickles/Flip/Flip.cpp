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
 * Inversion.cpp
 * magic
 *
 * Created by Marek Bereza on 13/04/2011.
 *
 */

#include "Flip.h"
#include "ReactickleApp.h"
#include "constants.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif

void Flip::start() {
	pos.push_back(ofGetWindowSize()/2);
	lastPos = pos.back();
	currShapeId = MAGIC_CIRCLE;
}

void Flip::draw() {
	int colorIndex = Settings::getInstance()->settings["fgColor"];

	int color1 = 0x000000;
	int color2 = 0xAAAAAA;
	int color3 = 0xFFFFFF;

	if(colorIndex!=20) {
		color3 = ColorPicker::colors[colorIndex];
		ofColor cc = ofColor::fromHex(color3);
		cc.setBrightness(100);
		color2 = cc.getHex();
	}




	if(pos.back().x>WIDTH/2) {
		int t = color1;
		color1 = color2;
		color2 = t;
	}

	ofSetHexColor(color1);
	ofRect(0, 0, WIDTH/2, HEIGHT);

	ofSetHexColor(color2);
	ofRect(WIDTH/2, 0, WIDTH/2, HEIGHT);

	ofSetHexColor(color3);
	drawShape(currShapeId, pos.back(), 400);

	while(pos.size()>100) {
		pos.pop_front();
	}
}

void Flip::update() {
	if(mode==0) {
		currShapeId = MAGIC_CIRCLE;
	} else {
		float w2 = WIDTH/2;
		if((lastPos.x<w2 && pos.back().x>w2) || (lastPos.x>w2 && pos.back().x<w2)) {
            if(mode == 1){
                if (currShapeId == MAGIC_CIRCLE){
                    currShapeId = MAGIC_CROSS;
                }else{
                    currShapeId = MAGIC_CIRCLE;
                }
            }else{
                currShapeId++;
                currShapeId %= NUM_MAGIC_SHAPES;
            }

#ifndef TARGET_OF_IPHONE
            ofxOscMessage m;
            m.setAddress( "/shapechange" );
            m.addIntArg( currShapeId );
            ReactickleApp::instance->sender.sendMessage( m );
#endif
		}

		lastPos = pos.back();
	}
}

bool Flip::touchDown(float x, float y, int touchId) {
	touches.push_back(FlipTouch(x, y, touchId));
	ofVec2f lastPos;
	if(pos.size()>0) {
		lastPos = pos.back();
	}
	pos.push_back((ofVec2f(x, y)*0.05+lastPos*0.95));



	return true;
}
bool Flip::touchMoved(float x, float y, int touchId) {
	ofVec2f lastPos;
	if(pos.size()>0) {
		lastPos = pos.back();
	}
	pos.push_back((ofVec2f(x, y)*0.05+lastPos*0.95));
	for(int i = 0; i < touches.size(); i++) {
		if(touchId==touches[i].touchId) {
			touches[i].x = x;
			touches[i].y = y;
			return true;
		}
	}

	return touchDown(x, y, touchId);

}
bool Flip::touchUp(float x, float y, int touchId) {
	for(int i = 0; i < touches.size(); i++) {
		if(touchId==touches[i].touchId) {
			touches.erase(touches.begin()+i);
			return true;
		}
	}
	return true;
}

void Flip::modeChanged() {
#ifndef TARGET_OF_IPHONE
    ofxOscMessage m;
    m.setAddress("/modechange");
    m.addIntArg( mode );
    ReactickleApp::instance->sender.sendMessage( m );
#endif
}
