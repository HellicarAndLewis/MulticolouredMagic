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

#include "Corridors.h"
#include "Silhouettes.h"
#include "Windmills.h"
#include "Painter.h"
#include "Sparkles.h"
#include "Mirror.h"
//#include "Cascades.h"
#include "Paths.h"
#include "Tunnel.h"


void MainMenu::initMenu() {
	addReactickleButton(new ReactickleButton("Paths"));
	addReactickleButton(new ReactickleButton("Corridors"));
	addReactickleButton(new ReactickleButton("Windmills"));

	addReactickleButton(new ReactickleButton("Tunnel"));    
	addReactickleButton(new ReactickleButton("Silhouette"));

	
	if(HAS_CAMERA) {
		addReactickleButton(new ReactickleButton("Ghost"));
		addReactickleButton(new ReactickleButton("Painter"));
		addReactickleButton(new ReactickleButton("Slitscan"));
		addReactickleButton(new ReactickleButton("Kaleidoscope"));
	}
	addReactickleButton(new ReactickleButton("Sparkles"));
	//addReactickleButton(new ReactickleButton("Cascades"));
	
	
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
	} else if(name=="Ghost") {
		r = new Mirror(MIRROR_AMBIENT_LAPSE);
	} else if(name=="Slitscan") {
		r = new Mirror(MIRROR_SLITSCAN);
	//} else if(name == "Cascades") {
	//	r = new Cascades();
	}else if(name == "Paths") {
		r = new Paths();
	}else if(name == "Tunnel") {
		r = new Tunnel();
	}
	r->titleImage = ImageCache::getImage(IMAGE_ROOT + "apps/names/" + name + ".png");
	r->titleImage->setAnchorPercent(0.5, 0.5);
	if(r!=NULL) {	
		ReactickleApp::instance->launchReactickle(r);
	} else {
		printf("Couldn't find reactickle '%s'!!\n", name.c_str());
	}

}
