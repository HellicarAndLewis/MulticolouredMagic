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
	
	
	settingsButton.setup("settings", ofVec2f(50, 50), IMAGE_ROOT + "settingsButton.png", IMAGE_ROOT + "settingsButtonDown.png");
	aboutButton.setup("about", ofVec2f(150, 50), IMAGE_ROOT + "aboutButton.png", IMAGE_ROOT + "aboutButtonDown.png");
	
	items.push_back(&aboutButton);
	items.push_back(&settingsButton);
	
	aboutButton.setListener(this);
	settingsButton.setListener(this);
	
	// setup scrolling stuff
	scrollRect.x = 0;
	scrollRect.width = WIDTH;
	scrollRect.y = 100;
	scrollRect.height = HEIGHT - scrollRect.y;
	scrollOffset = 0;
	deltaX = 0;
	touchX = 0;
	touching = false;
}



void MainMenu::buttonPressed(string name) {
	if(name=="settings") {
		ReactickleApp::instance->showSettings();
	} else if(name=="about") {
		ReactickleApp::instance->showAbout();
	}
}

// this method arranges the reacticklesButtons nicely
void MainMenu::arrange() {
	int itemsPerCol = 3;
	int PADDING = 10*WIDTH_SCALE;
	int rowHeight = reactickleButtons[0]->height+PADDING;
	int colWidth = reactickleButtons[0]->width+PADDING;
	
	
	for(int i = 0; i < reactickleButtons.size(); i++) {
		int col = i / itemsPerCol;
		int row = i % itemsPerCol;
		reactickleButtons[i]->x = colWidth*col + scrollOffset + PADDING;
		reactickleButtons[i]->y = rowHeight*row + scrollRect.y + PADDING;
		if(totalWidth<reactickleButtons[i]->x + reactickleButtons[i]->width) {
			totalWidth = reactickleButtons[i]->x + reactickleButtons[i]->width;
		}
	}
}

void MainMenu::draw() {
	
	arrange();
	
	if(!touching) {
		
		// pulling the top
		if(scrollOffset>0) {
			deltaX = -scrollOffset*0.1;
			
			
			// pulling the bottom
		} else if(ABS(scrollOffset)>totalWidth-scrollRect.width) {
			deltaX = (ABS(scrollOffset)-(totalWidth-scrollRect.width))*0.1;
			
		} else {
			// normal momentum
			deltaX *= 0.9;
			
		}
		if(ABS(deltaX)<1) deltaX = 0;
		scrollOffset += deltaX;
	}
	
	
	
	ofSetHexColor(0xFFFFFF);
	ofDrawBitmapString(ofToString(ofGetFrameRate(), 2), 20, 20);
	
	for(int i = 0; i < items.size(); i++) {
		items[i]->draw();
	}
	ofNoFill();
	ofRect(scrollRect);
	ofFill();
}

void MainMenu::touchDown(float x, float y, int touchId) {
	if(scrollRect.inside(x, y)) {
		touchX = x;
		touching = true;
	}
	for(int i = 0; i < items.size(); i++) {
		if(items[i]->touchDown(x, y, touchId)) {
			return;
		}
	}
}

void MainMenu::touchMoved(float x, float y, int touchId) {
	deltaX = x - touchX;
	scrollOffset += deltaX;
	touchX = x;
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


