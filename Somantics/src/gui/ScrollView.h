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
	void setup(float x, float y, float width, float height, int itemsPerCol = 2) {
		
		listener = NULL;
		scrollOffset = 0;

		deltaX = 0;
		touchX = 0;
		touching = false;
		
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
	}
	
	// this is a list of all the things that can be interacted with
	vector<InteractiveObject*> items;
	
	void draw() {
		arrange();
		
		if(!touching) {
			
			// pulling the top
			if(scrollOffset>0) {
				deltaX = -scrollOffset*0.1;
				
				
				// pulling the bottom
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
	
	void arrange() {
		int PADDING = 10*WIDTH_SCALE;
		int rowHeight = items[0]->height+PADDING;
		int colWidth = items[0]->width+PADDING;
		
		
		for(int i = 0; i < items.size(); i++) {
			int col = i / itemsPerCol;
			int row = i % itemsPerCol;
			items[i]->x = colWidth*col + scrollOffset + PADDING;
			items[i]->y = rowHeight*row + y + PADDING;
			if(totalWidth<items[i]->x + items[i]->width) {
				totalWidth = items[i]->x + items[i]->width;
			}
		}
	}
	
	
	bool touchDown(float x, float y, int touchId) {
		if(inside(x, y)) {
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
		deltaX = x - touchX;
		scrollOffset += deltaX;
		touchX = x;
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchMoved(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}
	
	bool touchUp(float x, float y, int touchId) {
		touching = false;
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