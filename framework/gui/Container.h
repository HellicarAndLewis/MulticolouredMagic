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
 * Container.h
 * SomanticsMac
 *
 * Created by Marek Bereza on 11/05/2011.
 *
 */
#pragma once
#include "InteractiveObject.h"

class Container: public InteractiveObject {
public:
	virtual bool touchDown(float x, float y, int touchId) {
		x -= this->x;
		y -= this->y;
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchDown(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}
	
	virtual bool touchMoved(float x, float y, int touchId) {
		x -= this->x;
		y -= this->y;
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchMoved(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}
	
	virtual bool touchUp(float x, float y, int touchId) {
		x -= this->x;
		y -= this->y;
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchUp(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}

	
	virtual void draw() {
		glPushMatrix();
		glTranslatef(x, y, 0);
		for(int i = 0; i < items.size(); i++) {
			items[i]->draw();
		}
		glPopMatrix();
	}
	void add(InteractiveObject *obj) {
		items.push_back(obj);
	}
	void add(InteractiveObject &obj) {
		items.push_back(&obj);
	}
protected:
	vector<InteractiveObject*> items;
};