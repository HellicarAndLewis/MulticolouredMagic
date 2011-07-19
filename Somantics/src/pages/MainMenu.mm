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
	scrollView.setup(0, 100, WIDTH, HEIGHT - 200);
	
	initMenu();
	
	settingsButton.setup("settings", ofVec2f(WIDTH/2 - 66, HEIGHT - 50), IMAGE_ROOT + "settingsButton.png", IMAGE_ROOT + "settingsButtonDown.png");
	aboutButton.setup("about", ofVec2f(WIDTH/2 + 54, HEIGHT - 50), IMAGE_ROOT + "aboutButton.png", IMAGE_ROOT + "aboutButtonDown.png");
	
	logo.setup(ofVec2f(WIDTH/2 - 150, 35), IMAGE_ROOT + "logo.png"); 
	add(&logo);
	add(&aboutButton);
	add(&settingsButton);
	add(&scrollView);
	
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

}

void MainMenu::addReactickleButton(ReactickleButton *reactickleButton) {
	scrollView.add(reactickleButton);
	reactickleButton->setListener(this);
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
	bgImage->draw(0, 0, WIDTH, HEIGHT);
	Container::draw();
}
