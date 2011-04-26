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
#include "01JGLCircleGetsBigger.h"
#include "02JGLGridOfSquaresToCircles.h"
#include "03JGLColourChangeOnNoise.h"
#include "ClapBang.h"
#include "AudioBalloonApp.h"
#include "Circles2D.h"
#include "ClapClock.h"
#include "CircleSwarm.h"
#include "Inversion.h"
#include "Expander.h"

void MainMenu::initMenu() {
	reactickleButtons.push_back(new ReactickleButton("expander", IMAGE_ROOT + "defaultScreenshot.jpg"));
	reactickleButtons.push_back(new ReactickleButton("clap clock", IMAGE_ROOT + "defaultScreenshot.jpg"));
	reactickleButtons.push_back(new ReactickleButton("inversion", IMAGE_ROOT + "defaultScreenshot.jpg"));
	reactickleButtons.push_back(new ReactickleButton("circle swarm", IMAGE_ROOT + "defaultScreenshot.jpg"));
	reactickleButtons.push_back(new ReactickleButton("circles 2d", IMAGE_ROOT + "defaultScreenshot.jpg"));
	reactickleButtons.push_back(new ReactickleButton("squares to circles", IMAGE_ROOT + "defaultScreenshot.jpg"));
	reactickleButtons.push_back(new ReactickleButton("clap bang", IMAGE_ROOT + "defaultScreenshot.jpg"));
	reactickleButtons.push_back(new ReactickleButton("colour change on noise", IMAGE_ROOT + "defaultScreenshot.jpg"));
	reactickleButtons.push_back(new ReactickleButton("circle bigger", IMAGE_ROOT + "defaultScreenshot.jpg"));
	
	
	

}

void MainMenu::reactickleSelected(string name) {
	printf("Starting %s!\n", name.c_str());
	if(name=="expander") {
		ReactickleApp::instance->launchReactickle(new Expander());
	} else if(name=="clap clock") {
		ReactickleApp::instance->launchReactickle(new ClapClock());
	} else if(name=="inversion") {
		ReactickleApp::instance->launchReactickle(new Inversion());
	} else if(name=="circle swarm") {
		ReactickleApp::instance->launchReactickle(new CircleSwarm());
	} else if(name=="circles 2d") {
		ReactickleApp::instance->launchReactickle(new Circles2D());
	} else if(name=="squares to circles") {
		ReactickleApp::instance->launchReactickle(new GridOfSquaresApp());
	} else if(name=="clap bang") {
		ReactickleApp::instance->launchReactickle(new ClapBang());
	} else if(name=="colour change on noise") {
		ReactickleApp::instance->launchReactickle(new ColourChangeOnNoiseApp());
	} else if(name=="circle bigger") {
		ReactickleApp::instance->launchReactickle(new CircleBiggerApp());
	}
}
