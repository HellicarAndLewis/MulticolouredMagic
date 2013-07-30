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

/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  SampleGui.h, created by Marek Bereza on 11/12/2012.
 */

#include "SimpleGui.h"
#include "MiniSampler.h"
#include "Pad.h"
#include "HoldToggle.h"

class SoundBoxGui: public xmlgui::Listener {
public:
	
	xmlgui::SimpleGui gui;
	int numPads;

	ofImage title;

	HoldToggle activator;
	bool guiActive;
	void setup() {
		guiActive = false;
		title.loadImage("settings-title.png");
		activator.set(ofGetWidth() - 10 - 120, 10, 120, 120);
		activator.setup("settings|close", guiActive);
		gui.y = 140;
		gui.setWidth(450);
		gui.addSlider("Number of Pads", numPads, 1, 11)->height = 40;
		gui.addSegmented("Loop", (int&)MiniSampler::looping, "OFF|ON")->size(100, 40);
		gui.addSegmented("Trigger", Pad::triggerType, "DIRECT|LATCH")->height=40;
		gui.addListener(this);
		activator.addListener(this);
		
	}
	
	void controlChanged(xmlgui::Event *e) {
	
		
		if(e->control->id=="settings|close") {
			gui.setEnabled(guiActive);
			
		}
	}
	void enableGui() {
		gui.setEnabled(true);
	}
	
	void draw() {
		
		if(gui.isEnabled()) {
			
			ofEnableAlphaBlending();
			ofSetColor(0, 0, 0, 100);
			ofRect(0, 0, ofGetWidth(), ofGetHeight());
			ofSetColor(255);
			title.draw(20,20);
		}
		activator.draw();
	}
	
	
	void touchDown(int id, float x, float y) {
		activator.touchDown(x, y, id);
	}
	
	
	void touchUp(int id, float x, float y) {
		activator.touchUp(x, y, id);
	}
	
	void touchMoved(int id, float x, float y) {
		activator.touchMoved(x, y, id);
	}
};



