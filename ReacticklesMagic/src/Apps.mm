/**
 * Apps.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

/*
 * HOW TO ADD AN APP
 * 
 * 1. Include the header file
 * 2. Add a button for it in initMenu()
 * 3. Add an else if() in reactickleSelected()
 */

#include "MainMenu.h"
#include "constants.h"
#include "ReactickleApp.h"


#include "ClapClock.h"


void MainMenu::initMenu() {
	reactickleButtons.push_back(new ReactickleButton("clap clock", IMAGE_ROOT + "defaultScreenshot.jpg"));
	/*reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));
	 reactickleButtons.push_back(new ReactickleButton("", IMAGE_ROOT + "defaultScreenshot.jpg"));*/
}

void MainMenu::reactickleSelected(string name) {
	printf("Starting %s!\n", name.c_str());
	if(name=="clap clock") {
		
		ReactickleApp::instance->launchReactickle(new ClapClock());
	}
}
