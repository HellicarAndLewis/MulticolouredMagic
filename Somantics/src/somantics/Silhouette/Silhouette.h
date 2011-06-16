/**
 * Corridor.h
 * CorridorsDemo
 *
 * Created by Marek Bereza on 10/05/2011.
 *
 */
#include "BrushedLine.h"
#include "ImageCache.h"

class Silhouette {
public:
	
	Silhouette() {
		line.setup(lineImage, 50);
	}
	
	static void setup() {
		static ofImage *img = NULL;
		if(img==NULL) {
			img = ImageCache::getImage("img/blob.png");
		}
		lineImage = img;
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
	
	
	void draw() {
		map<int,ofVec2f>::iterator it;
		
		ofVec2f border[touches.size()];

		
	
		
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
		line.drawLines(border, touches.size(), true);
		
	}
	
	
	map<int,ofVec2f> touches;
	BrushedLine line;
	static ofImage *lineImage;
};