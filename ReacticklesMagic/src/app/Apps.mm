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


#include "Expand.h"
#include "Orbit.h"
#include "Flip.h"
#include "Follow.h"
#include "Trail.h"
#include "Grid.h"
#include "Cascade.h"
#include "Change.h"
#include "Find.h"
#include "Trace.h"


void MainMenu::initMenu() {
	reactickleButtons.push_back(new ReactickleButton("expand"));
	reactickleButtons.push_back(new ReactickleButton("orbit"));
	reactickleButtons.push_back(new ReactickleButton("flip"));
	reactickleButtons.push_back(new ReactickleButton("follow"));
	reactickleButtons.push_back(new ReactickleButton("trail"));
	reactickleButtons.push_back(new ReactickleButton("grid"));
	reactickleButtons.push_back(new ReactickleButton("cascade"));
	reactickleButtons.push_back(new ReactickleButton("change"));
	reactickleButtons.push_back(new ReactickleButton("find"));
	reactickleButtons.push_back(new ReactickleButton("trace"));
}

void MainMenu::reactickleSelected(string name) {
	printf("Starting %s!\n", name.c_str());
	if(name=="expand") {
		ReactickleApp::instance->launchReactickle(new Expand());
	} else if(name=="orbit") {
		ReactickleApp::instance->launchReactickle(new Orbit());
	} else if(name=="flip") {
		ReactickleApp::instance->launchReactickle(new Flip());
	} else if(name=="follow") {
		ReactickleApp::instance->launchReactickle(new Follow());
	} else if(name=="trail") {
		ReactickleApp::instance->launchReactickle(new Trail());
	} else if(name=="grid") {
		ReactickleApp::instance->launchReactickle(new Grid());
	} else if(name=="cascade") {
		ReactickleApp::instance->launchReactickle(new Cascade());
	} else if(name=="change") {
		ReactickleApp::instance->launchReactickle(new Change());
	} else if(name=="find") {
		ReactickleApp::instance->launchReactickle(new Find());
	} else if(name=="trace") {
		ReactickleApp::instance->launchReactickle(new Trace());
	}
}
