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
	

	initMenu();
	
	reactickleButtonCount = 0;

	//logo.setup(ofVec2f(WIDTH/2 - 150, 35), IMAGE_ROOT + "logo.png"); 
	//add(&logo);
	
	
	if(IPAD) {
		bgImage = ImageCache::getImage("img/bgIPad.png");
	} else if(HI_RES) {
		bgImage = ImageCache::getImage("img/bgIPhone4.png");
	} else {
		bgImage = ImageCache::getImage("img/bgIPhone.png");
	}

}

void MainMenu::addReactickleButton(ReactickleButton *reactickleButton) {

	reactickleButton->width = 160;
	reactickleButton->height = 120;
	
	reactickleButton->x = 20 + reactickleButtonCount*(reactickleButton->width + 20);
	reactickleButton->y = 20;

	this->add(reactickleButton);
	reactickleButton->setListener(this);
	reactickleButtonCount++;
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
//	bgImage->draw(0, 0, WIDTH, HEIGHT);
	Container::draw();
}
