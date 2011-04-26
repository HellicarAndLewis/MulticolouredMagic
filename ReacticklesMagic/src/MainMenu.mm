/**
 * MainMenu.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

#include "MainMenu.h"
#include "constants.h"
#include "ImageCache.h"
#include "ReactickleApp.h"

void MainMenu::setup() {
	// add all the buttons for the different Reactickles
	
	initMenu();
	
	// copy the reactickle list to the items list - the items list
	// is the one used to propagating events.
	for(int i = 0; i < reactickleButtons.size(); i++) {
		
		// add a button listener
		reactickleButtons[i]->setListener(this);
		
		// add it to the display/interaction hierarchy
		items.push_back(reactickleButtons[i]);
	}
	scrollRect.x = 0;
	scrollRect.width = WIDTH;
	scrollRect.y = 100;
	scrollRect.height = HEIGHT - scrollRect.y;
	scrollOffset = 0;
	deltaY = 0;
	touchY = 0;
	touching = false;
}




// this method arranges the reacticklesButtons nicely
void MainMenu::arrange() {
	int itemsPerRow = 3;
	int rowHeight = reactickleButtons[0]->height+10;
	int colWidth = reactickleButtons[0]->width+10;
	
	
	for(int i = 0; i < reactickleButtons.size(); i++) {
		int col = i % itemsPerRow;
		int row = i / itemsPerRow;
		reactickleButtons[i]->x = colWidth*col;
		reactickleButtons[i]->y = rowHeight*row + scrollRect.y + scrollOffset;
		if(totalHeight<reactickleButtons[i]->y + reactickleButtons[i]->height) {
			totalHeight = reactickleButtons[i]->y + reactickleButtons[i]->height;
		}
	}
}

void MainMenu::draw() {
	
	arrange();
	
	if(!touching) {
		
		// pulling the top
		if(scrollOffset>0) {
			deltaY = -scrollOffset*0.1;
			
			
			// pulling the bottom
		} else if(ABS(scrollOffset)>totalHeight-scrollRect.height) {
			deltaY = (ABS(scrollOffset)-(totalHeight-scrollRect.height))*0.1;
			
		} else {
			// normal momentum
			deltaY *= 0.9;
			
		}
		if(ABS(deltaY)<1) deltaY = 0;
		scrollOffset += deltaY;
	}
	
	
	
	ofSetHexColor(0xFFFFFF);
	ofDrawBitmapString("Reactickles" , 20, 20);
	
	for(int i = 0; i < items.size(); i++) {
		items[i]->draw();
	}
	ofNoFill();
	ofRect(scrollRect);
	ofFill();
}

void MainMenu::touchDown(float x, float y, int touchId) {
	if(scrollRect.inside(x, y)) {
		touchY = y;
		touching = true;
	}
	for(int i = 0; i < items.size(); i++) {
		if(items[i]->touchDown(x, y, touchId)) {
			return;
		}
	}
}

void MainMenu::touchMoved(float x, float y, int touchId) {
	deltaY = y - touchY;
	scrollOffset += deltaY;
	touchY = y;
	for(int i = 0; i < items.size(); i++) {
		if(items[i]->touchMoved(x, y, touchId)) {
			return;
		}
	}
}

void MainMenu::touchUp(float x, float y, int touchId) {
	touching = false;
	for(int i = 0; i < items.size(); i++) {
		if(items[i]->touchUp(x, y, touchId)) {
			return;
		}
	}
}


