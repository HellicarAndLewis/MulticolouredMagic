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
 * Corridor.h
 * CorridorsDemo
 *
 * Created by Marek Bereza on 10/05/2011.
 *
 */
#include "constants.h"

class Corridor {
public:
	Corridor() {
		curtainSpeed = 0.4; // 0 is forever, 1 is instantaneous
		
		fingerWidth = 40;
		minTouchDistance = 60;
		startX = 0;
		endX = WIDTH;
	}
	
	bool touchDown(float x, float y, int touchId) {
		if(touches.size()==0) {
			touches[touchId] = ofVec2f(x,y);
			return true;
		} else {
			map<int,ofVec2f>::iterator it;
			for(it = touches.begin(); it != touches.end(); it++) {
				if(ABS(x-(*it).second.x)<minTouchDistance) {
					touches[touchId] = ofVec2f(x,y);
					return true;
				}
			}
			
		}
		return false;
	}
	
	
	bool touchMoved(float x, float y, int touchId) {
		if(touches.find(touchId)!=touches.end()) {
			touches[touchId].x = x;
			touches[touchId].y = y;
			return true;
		}
		return false;
	}
	
	bool touchUp(int touchId) {
		if(touches.find(touchId)!=touches.end()) {
			touches.erase(touchId);
			return true;
		} else {
			return false;
		}
	}
	
	bool dead() {
		return touches.size()==0 && startX<fingerWidth/2 + 1 && endX>WIDTH-fingerWidth/2 - 1;
	}
	
	void draw() {
		map<int,ofVec2f>::iterator it;
		float targetStartX = WIDTH;
		float targetEndX = 0;
		for(it = touches.begin(); it != touches.end(); it++) {
			ofVec2f t = (*it).second;
			if(t.x>targetEndX) targetEndX = t.x;
			if(t.x<targetStartX) targetStartX = t.x;
		}
		
		if(targetEndX==0) targetEndX = WIDTH;
		if(targetStartX==WIDTH) targetStartX = 0;
		
		targetStartX -= fingerWidth/2;
		targetEndX += fingerWidth/2;
		
		startX = ofLerp(startX, targetStartX, curtainSpeed);
		endX = ofLerp(endX, targetEndX, curtainSpeed);
		ofRect(0, 0, startX, HEIGHT);
		ofRect(endX, 0, WIDTH-endX, HEIGHT);
	}
	
	float curtainSpeed;
	float minTouchDistance;
	float fingerWidth;
	float startX, endX;
	map<int,ofVec2f> touches;
};