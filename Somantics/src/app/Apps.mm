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

#include "Corridors.h"
#include "Silhouettes.h"
#include "Windmills.h"
#include "Painter.h"
#include "Sparkles.h"
#include "Mirror.h"


void MainMenu::initMenu() {
	addReactickleButton(new ReactickleButton("Corridors"));
	addReactickleButton(new ReactickleButton("Silhouette"));
	addReactickleButton(new ReactickleButton("Windmills"));
	addReactickleButton(new ReactickleButton("Painter"));
	addReactickleButton(new ReactickleButton("Sparkles"));
	addReactickleButton(new ReactickleButton("Mirror"));
	addReactickleButton(new ReactickleButton("Slitscan"));
	addReactickleButton(new ReactickleButton("Ambient Lapse"));
}

void MainMenu::reactickleSelected(string name) {
	printf("Launching '%s'\n", name.c_str());
	Reactickle *r = NULL;
	
	if(name=="Corridors") {
		r = new Corridors();
	} else if(name=="Silhouette") {
		r = new Silhouettes();
	} else if(name=="Windmills") {
		r = new Windmills();
	} else if(name=="Painter") {
		r = new Painter();
	} else if(name=="Sparkles") {
		r = new Sparkles();
	} else if(name=="Mirror") {
		r = new Mirror(MIRROR_MIRROR);
	} else if(name=="Ambient Lapse") {
		r = new Mirror(MIRROR_AMBIENT_LAPSE);
	} else if(name=="Slitscan") {
		r = new Mirror(MIRROR_SLITSCAN);
	}
	
	if(r!=NULL) {	
		ReactickleApp::instance->launchReactickle(r);
	} else {
		printf("Couldn't find reactickle '%s'!!\n", name.c_str());
	}

}
