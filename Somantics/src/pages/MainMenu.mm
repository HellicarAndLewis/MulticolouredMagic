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
	scrollView.setup(0, 100, WIDTH, HEIGHT - 100);
	
	initMenu();
	
	settingsButton.setup("settings", ofVec2f(50, 50), IMAGE_ROOT + "settingsButton.png", IMAGE_ROOT + "settingsButtonDown.png");
	aboutButton.setup("about", ofVec2f(150, 50), IMAGE_ROOT + "aboutButton.png", IMAGE_ROOT + "aboutButtonDown.png");
	
	items.push_back(&aboutButton);
	items.push_back(&settingsButton);
	items.push_back(&scrollView);
	
	aboutButton.setListener(this);
	settingsButton.setListener(this);
	scrollView.setListener(this);
	if(IPAD) {
		bgImage = ImageCache::getImage("img/bgIPad.png");
	} else if(HI_RES) {
		bgImage = ImageCache::getImage("img/bgIPhone4.png");
	} else {
		bgImage = ImageCache::getImage("img/bgIPhone.png");
	}
	logo = ImageCache::getImage(IMAGE_ROOT + "logo.png");
}



void MainMenu::buttonPressed(string name) {

	if(name=="settings") {
		ReactickleApp::instance->showSettings();
	} else if(name=="about") {
		ReactickleApp::instance->showAbout();
	}
}



void MainMenu::draw() {	
	ofSetHexColor(0xFFFFFF);
	bgImage->draw(0, 0, ofGetWidth(), ofGetHeight());
	logo->draw(WIDTH/2, HEIGHT - 20);
	Container::draw();
}
