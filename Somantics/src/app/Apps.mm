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
#include "Cascades.h"
#include "Paths.h"
#include "Tunnel.h"


void MainMenu::initMenu() {
	addReactickleButton(new ReactickleButton("Corridors"));
	addReactickleButton(new ReactickleButton("Silhouette"));
	addReactickleButton(new ReactickleButton("Windmills"));
	addReactickleButton(new ReactickleButton("Painter"));
	addReactickleButton(new ReactickleButton("Sparkles"));
	addReactickleButton(new ReactickleButton("Kaleidoscope"));
	addReactickleButton(new ReactickleButton("Slitscan"));
	addReactickleButton(new ReactickleButton("Ambient Lapse"));
	addReactickleButton(new ReactickleButton("Cascades"));
	addReactickleButton(new ReactickleButton("Paths"));
	addReactickleButton(new ReactickleButton("Tunnel"));    
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
	} else if(name=="Kaleidoscope") {
		r = new Mirror(MIRROR_KALEIDOSCOPE);
	} else if(name=="Ambient Lapse") {
		r = new Mirror(MIRROR_AMBIENT_LAPSE);
	} else if(name=="Slitscan") {
		r = new Mirror(MIRROR_SLITSCAN);
	} else if(name == "Cascades") {
		r = new Cascades();
	}else if(name == "Paths") {
		r = new Paths();
	}else if(name == "Tunnel") {
		r = new Tunnel();
	}
	
	if(r!=NULL) {	
		ReactickleApp::instance->launchReactickle(r);
	} else {
		printf("Couldn't find reactickle '%s'!!\n", name.c_str());
	}

}
