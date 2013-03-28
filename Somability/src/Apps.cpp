/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
#include "HandShooter.h"


void MainMenu::initMenu() {
	//addReactickleButton(new SimpleReactickleButton("Pendulum"));
	addReactickleButton(new SimpleReactickleButton("Misting Mirror"));
	addReactickleButton(new SimpleReactickleButton("Echo"));
	addReactickleButton(new SimpleReactickleButton("Ghost"));
	addReactickleButton(new SimpleReactickleButton("Stickman"));
	addReactickleButton(new SimpleReactickleButton("Cannon Ball"));
	addReactickleButton(new SimpleReactickleButton("Multi Cannonball"));
	addReactickleButton(new SimpleReactickleButton("Catcher"));
//	addReactickleButton(new SimpleReactickleButton("MoveLoop"));

    addReactickleButton(new SimpleReactickleButton("HandPendulum"));
	addReactickleButton(new SimpleReactickleButton("HandShooter"));
	
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
	} else if(name=="HandShooter") {
		r = new HandShooter();
	}
    
	/*r->titleImage = ImageCache::getImage(IMAGE_ROOT + "apps/names/" + name + ".png");
	r->titleImage->setAnchorPercent(0.5, 0.5);*/
	if(r!=NULL) {	
		ReactickleApp::instance->launchReactickle(r);
	} else {
		printf("Couldn't find reactickle '%s'!!\n", name.c_str());
	}

}
