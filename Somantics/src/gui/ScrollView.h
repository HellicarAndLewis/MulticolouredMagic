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
 * ScrollView.h
 * Somantics
 *
 * Created by Marek Bereza on 11/05/2011.
 *
 */
#include "constants.h"
#include "SimpleButton.h"
class ScrollView: public InteractiveObject {
public:
	SimpleButtonListener *listener;
	bool scrollingEnabled;
	void setup(float x, float y, float width, float height, int itemsPerCol = 3) {
		
		scrollingEnabled = true;
		listener = NULL;
		scrollOffset = 0;

		deltaX = 0;
		touchX = 0;
		touching = false;
		
		PADDING = 12*WIDTH_SCALE;
		
		
		this->itemsPerCol = itemsPerCol;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		

	}
	
	void setListener(SimpleButtonListener *listener) {
		this->listener = listener;
	}
	
	
	void add(InteractiveObject *item) {
		items.push_back(item);
		
		totalWidth = ((items.size()+1)/2)*(items[0]->width+PADDING);
	}
	
	// this is a list of all the things that can be interacted with
	vector<InteractiveObject*> items;
	
	void draw() {
		//printf("%f %f %f %f\n", x, y, width, height);
		arrange();
		
		if(!touching) {
			
			// pulling the top
			if(scrollOffset>0) {
				deltaX = -scrollOffset*0.1;
				
				
				// pulling the bottom
				// 
			} else if(totalWidth + scrollOffset < width) {
				
				deltaX = (width - (totalWidth + scrollOffset))*0.1;
				
			} else {
				// normal momentum
				deltaX *= 0.9;
				
			}
			if(ABS(deltaX)<1) deltaX = 0;
			scrollOffset += deltaX;
		}

		for(int i = 0; i < items.size(); i++) {
			items[i]->draw();
		}
	}
	int PADDING;
	void arrange() {

		int rowHeight = items[0]->height+PADDING;
		int colWidth = items[0]->width+PADDING;
		
		
		for(int i = 0; i < items.size(); i++) {
			int row = 0;
			if(i>4) row = 2;
			else if(i>2) row = 1;

			
			int col = i;
			if(i>4) col = i - 5;
			else if(i>2) col = i - 3;
			
			items[i]->x = colWidth*col + scrollOffset + PADDING + x;
			items[i]->y = rowHeight*row + y + PADDING;
		
		}
	}
	
	
	bool touchDown(float x, float y, int touchId) {
		if(scrollingEnabled && inside(x, y)) {
			touchX = x;
			touching = true;
		}
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchDown(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}
	
	bool touchMoved(float x, float y, int touchId) {
		if(scrollingEnabled) {
			
			if(!inside(x, y)) {
				touching = false;
				return false;
			}
			deltaX = x - touchX;
			scrollOffset += deltaX;
			touchX = x;
		}
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchMoved(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}
	
	bool touchUp(float x, float y, int touchId) {
		if(scrollingEnabled) {
			touching = false;
		}
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchUp(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}
	
	
	// how much we're scrolled away from zero
	float scrollOffset;
	
	// scrolling touch stuff
	bool touching;
	float touchX;
	float deltaX;
	float totalWidth;
	int itemsPerCol;
};