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
 * MainMenu.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

#include "MainMenu.h"
#include "constants.h"
#include "ImageCache.h"
#include "ReactickleApp.h"

void MainMenu::setup() {
	
	// add all the buttons for the different Reactickles
	scrollView.setup(37, 135, WIDTH, HEIGHT - 200);
	scrollView.scrollingEnabled = false;

	initMenu();
	
	settingsButton.setup("settings", ofVec2f(WIDTH/2 - 63, HEIGHT - 50), IMAGE_ROOT + "settingsButton.png", IMAGE_ROOT + "settingsButtonDown.png");
	aboutButton.setup("about", ofVec2f(WIDTH/2 + 45, HEIGHT - 50), IMAGE_ROOT + "aboutButton.png", IMAGE_ROOT + "aboutButtonDown.png");
	
	logo.setup(ofVec2f(WIDTH/2 - 150, 35), IMAGE_ROOT + "logo.png"); 
	add(&logo);
	add(&aboutButton);
	add(&settingsButton);
	add(&scrollView);
	
	aboutButton.setListener(this);
	settingsButton.setListener(this);
	scrollView.setListener(this);
	if(IPAD) {
		bgImage = ImageCache::getImage("img/bgIPad.png");
	} else if(HI_RES) {
		bgImage = ImageCache::getImage("img/bgIPhone4.png");
	} else {
		bgImage = ImageCache::getImage("img/bgIPhone.png");
	}

}

void MainMenu::addReactickleButton(ReactickleButton *reactickleButton) {
	scrollView.add(reactickleButton);
	reactickleButton->setListener(this);
}

void MainMenu::buttonPressed(string name) {

	if(name=="settings") {
		ReactickleApp::instance->showSettings();
	} else if(name=="about") {
		ReactickleApp::instance->showAbout();
	}
}



void MainMenu::draw() {	
	ofSetHexColor(0xFFFFFF);
	bgImage->draw(0, 0, WIDTH, HEIGHT);
	Container::draw();
}
