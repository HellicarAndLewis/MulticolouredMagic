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
	Reactickle *r = NULL;
	if(name=="expand") {
		r = new Expand();
	} else if(name=="orbit") {
		r = new Orbit();
	} else if(name=="flip") {
		r = new Flip();
	} else if(name=="follow") {
		r = new Follow();
	} else if(name=="trail") {
		r = new Trail();
	} else if(name=="grid") {
		r = new Grid();
	} else if(name=="cascade") {
		r = new Cascade();
	} else if(name=="change") {
		r = new Change();
	} else if(name=="find") {
		r = new Find();
	} else if(name=="trace") {
		r = new Trace();
	}
	if(r!=NULL) {
		ReactickleApp::instance->launchReactickle(r);
	} else {
		printf("Unknown reactickle! '%s'\n", name.c_str());
	}
}
