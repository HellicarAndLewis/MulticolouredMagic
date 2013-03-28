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
		r->name = name;
		ReactickleApp::instance->launchReactickle(r);
	} else {
		printf("Unknown reactickle! '%s'\n", name.c_str());
	}
}
