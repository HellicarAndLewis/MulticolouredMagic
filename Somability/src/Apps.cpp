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
#include "SimpleReactickleButton.h"

#include "Pendulum.h"
#include "MistingMirror.h"
#include "Echo.h"
#include "Ghost.h"
#include "Stickman.h"
#include "Catcher.h"
#include "MoveLoop.h"
#include "CannonBall.h"
#include "MultiCannonball.h"
#include "HandPendulum.h"


void MainMenu::initMenu() {
	//addReactickleButton(new SimpleReactickleButton("Pendulum"));
	addReactickleButton(new SimpleReactickleButton("Misting Mirror"));
	addReactickleButton(new SimpleReactickleButton("Echo"));
	addReactickleButton(new SimpleReactickleButton("Ghost"));
	addReactickleButton(new SimpleReactickleButton("Stickman"));
	addReactickleButton(new SimpleReactickleButton("Cannon Ball"));
	addReactickleButton(new SimpleReactickleButton("Catcher"));
	addReactickleButton(new SimpleReactickleButton("MoveLoop"));
	addReactickleButton(new SimpleReactickleButton("Multi Cannonball"));
    addReactickleButton(new SimpleReactickleButton("HandPendulum"));
	
	//addReactickleButton(new ReactickleButton("Cascades"));

	
}

void MainMenu::reactickleSelected(string name) {
	printf("Launching '%s'\n", name.c_str());
	Reactickle *r = NULL;
	
	if(name=="Pendulum") {
		r = new Pendulum();
	} else if(name=="MoveLoop") {
		r = new MoveLoop();
	} else if(name=="Misting Mirror") {
		r = new MistingMirror();
	} else if(name=="Echo") {
		r = new Echo();
	} else if(name=="Ghost") {
		r = new Ghost();
	} else if(name=="Stickman") {
		r = new Stickman();
	} else if(name=="Catcher") {
		r = new Catcher();
	} else if(name=="Cannon Ball") {
		r = new CannonBall();
	} else if(name=="Multi Cannonball") {
		r = new MultiCannonball();
	} else if(name=="HandPendulum") {
		r = new HandPendulum();
	}
    
	/*r->titleImage = ImageCache::getImage(IMAGE_ROOT + "apps/names/" + name + ".png");
	r->titleImage->setAnchorPercent(0.5, 0.5);*/
	if(r!=NULL) {	
		ReactickleApp::instance->launchReactickle(r);
	} else {
		printf("Couldn't find reactickle '%s'!!\n", name.c_str());
	}

}
