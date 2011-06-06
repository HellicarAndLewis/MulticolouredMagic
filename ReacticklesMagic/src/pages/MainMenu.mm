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
	logo = ImageCache::getImage(IMAGE_ROOT + "logo.png");
	logo->setAnchorPercent(0.5, 1);
	// copy the reactickle list to the items list - the items list
	// is the one used to propagating events.
	for(int i = 0; i < reactickleButtons.size(); i++) {
		
		// add a button listener
		reactickleButtons[i]->setListener(this);
		
		// add it to the display/interaction hierarchy
		add(reactickleButtons[i]);
	}
	
	
	settingsButton.setup("settings", ofVec2f(50, 50), IMAGE_ROOT + "settingsButton.png", IMAGE_ROOT + "settingsButtonDown.png");
	aboutButton.setup("about", ofVec2f(150, 50), IMAGE_ROOT + "aboutButton.png", IMAGE_ROOT + "aboutButtonDown.png");
	
	add(&aboutButton);
	add(&settingsButton);
	
	aboutButton.setListener(this);
	settingsButton.setListener(this);
	
	// setup scrolling stuff
	scrollRect.x = 0;
	scrollRect.width = WIDTH;
	scrollRect.y = 150;
	scrollRect.height = HEIGHT - scrollRect.y;
	scrollOffset = 0;
	deltaX = 0;
	touchX = 0;
	touching = false;
	
	
	if(IPAD) {
		bgImage = ImageCache::getImage("img/bgIPad.png");
	} else if(HI_RES) {
		bgImage = ImageCache::getImage("img/bgIPhone4.png");
	} else {
		bgImage = ImageCache::getImage("img/bgIPhone.png");
	}
	
	
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
	int itemsPerCol = 2;
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
	ofSetHexColor(0xFFFFFF);
	bgImage->draw(0, 0, WIDTH, HEIGHT);
	logo->draw(WIDTH/2, 35+logo->getHeight());
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
	Container::draw();
}

bool MainMenu::touchDown(float x, float y, int touchId) {
	if(scrollRect.inside(x, y)) {
		touchX = x;
		touching = true;
	}

	return Container::touchDown(x, y, touchId);
}

bool MainMenu::touchMoved(float x, float y, int touchId) {
	deltaX = x - touchX;
	scrollOffset += deltaX;
	touchX = x;
	return Container::touchMoved(x, y, touchId);
}

bool MainMenu::touchUp(float x, float y, int touchId) {
	touching = false;
	return Container::touchUp(x, y, touchId);
}


