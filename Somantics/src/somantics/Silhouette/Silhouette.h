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
#include "BrushedLine.h"
#include "ImageCache.h"
#pragma once
class Silhouette {
public:
	
	Silhouette() {
#ifdef TARGET_OF_IPHONE
		line.setup(lineImage, 50);
#else
		line.setup(lineImage, 35);
#endif
	}
	
	static void setup() {
		static ofImage *img = NULL;
		if(img==NULL) {
			img = ImageCache::getImage("img/blob.png");
		}
		lineImage = img;
	}
	
	void setSize(float size) {
		line.setSize(size);
	}
	bool touchDown(float x, float y, int touchId) {
		if(touches.size()==0) {
			touches[touchId] = ofVec2f(x,y);
			return true;
		} else {
			//map<int,ofVec2f>::iterator it;
			//for(it = touches.begin(); it != touches.end(); it++) {
			//	if(ABS(x-(*it).second.x)<minTouchDistance) {
					touches[touchId] = ofVec2f(x,y);
					return true;
			//	}
			//}
			
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
		return touches.size()==0;
	}
	
	// first 
	void sortPoints(ofVec2f *points, int numPoints) {
		if(numPoints==0) return;
		// first, find centre
		ofVec2f centre;
		for(int i = 0; i < numPoints; i++) {
			centre += points[i];
		}
		
		centre /= numPoints;
		
		
		// work out the angle between the centre and each point
		float angles[numPoints];
		
		for(int i = 0; i < numPoints; i++) {
			ofVec2f diff = centre - points[i];
			angles[i] = atan2(diff.y, diff.x);

		}

		// bubble sort from http://www.cplusplus.com/forum/articles/24830/
		
		// we sort the angles, and use the sorting order to sort the points in parallel
		bool bDone = false; // this flag will be used to check whether we have to continue the algorithm
		
		
		while(!bDone) {
			bDone = true; // assume that the array is currently sorted
			for(int i = 0;i != numPoints-1; ++i) { // for every element in the array     ( notice: this can be a bit optimized, see http://en.wikipedia.org/wiki/Bubblesort#Optimizing_bubble_sort )
				if(angles[i] > angles[i+1]) { // compare the current element with the following one
				
					// They are in the wrong order, swap them
					float a = angles[i];
					angles[i] = angles[i+1];
					angles[i+1] = a;
					
					// sort points in parallel
					ofVec2f p = points[i];
					points[i] = points[i+1];
					points[i+1] = p;
					
					bDone = false; // since we performed a swap, the array needs to be checked to see if it is sorted
					// this is done in the next iteration of the while
				}
			}
		}
		
		
	}
	
	void addPoint(ofVec2f p) {
		
	}
	
	void draw() {
		map<int,ofVec2f>::iterator it;

		ofVec2f *border = new ofVec2f[touches.size()];

		
	
		
		int i = 0;
		for(it = touches.begin(); it != touches.end(); it++) {
			ofVec2f t = (*it).second;
			border[i] = t;
			i++;
		}

		
		sortPoints(border, touches.size());
		
	/*	ofBeginShape();
		for(i = 0; i < touches.size(); i++) {
			ofVertex(border[i].x, border[i].y);
		}
		ofEndShape(true);
		
		*/
		draw(border, touches.size());
		
		delete [] border;
	}
	void draw(ofVec2f *border, int size) {
		
		line.drawLines(border, size, true);
		snapshot.clear();
		for(int i = 0; i < size; i++) {
			snapshot.push_back(border[i]);
		}
	}
	vector<ofVec2f> snapshot;
	
	vector<ofVec2f> getSnapshot() {
		return snapshot;
	}
	
	map<int,ofVec2f> touches;
	BrushedLine line;
	static ofImage *lineImage;
};