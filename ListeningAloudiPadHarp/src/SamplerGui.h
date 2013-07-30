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
#include "RecordButton.h"
#include "HoldToggle.h"

class SamplerGui: public xmlgui::Listener {
public:
	List *listyList;
	HoldToggle activator;
	xmlgui::SimpleGui gui;
	int input;
	int scale;
#define INPUT_CAMERA 0
#define INPUT_ACCELEROMETER 1
#define INPUT_TOUCH 2
	
	int key;
	float noteRange;
	int showCamera;
	
	int soundId;
	
	int useYAxisAsVolume;
	int showGridLines;
	RecordButton recordButton;
	bool guiActive;
	ofImage title;
	void setup() {
		recordButton.setup();
		title.loadImage("settings-title.png");
		useYAxisAsVolume = 0;
		showGridLines = 0;
		activator.set(ofGetWidth() - 10 - 120, 10, 120, 120);
		guiActive = false;
		activator.setup("settings|close", guiActive);
		input = INPUT_TOUCH;
		scale = 0;
		mustLoadSound = false;
		key = 0;
		soundId = 0;
		recording = false;
		showCamera = true;
		noteRange = 16;
		gui.setWidth(450);
		gui.setAutoLayoutPadding(25);
		gui.addSegmented("Input", input, "Camera|Accelerometer|Touch")->height = 40;
		
		gui.addSegmented("Scale", scale, "PENTATONIC|MAJOR|MINOR|CHROMATIC")->height = 40;
		gui.addSegmented("Key", key, "C|C#|D|D#|E|F|F#|G|G#|A|A#|B")->height = 40;
		Slider *s = gui.addSlider("Note Range", noteRange, 1, 30);
		s->height = 40;
		s->stepped = true;
		
		
		gui.addSegmented("Vary Volume", useYAxisAsVolume, "NO|YES")->size(90, 40);
		
		gui.addChild(&recordButton);
		gui.addTitle("Appearance");
		gui.addSegmented("Show Camera", showCamera, "NO|YES")->size(90, 40);
		gui.addSegmented("Show Grid Lines", showGridLines, "NO|YES")->size(90, 40);
		


		

		
		ofDirectory samples;
		int numSounds = samples.listDir("sounds");
		vector<string> sounds;
		for(int i = 0; i < numSounds; i++) {
			printf("Sample: '%s'\n", samples.getName(i).c_str());
			sounds.push_back(samples.getName(i));
		}
		
		listyList = gui.addList("Sound", soundId, sounds);

		printf("List of things: %d\n", listyList->items.size());
		listyList->itemHeight = 24;
		listyList->height = 560;
//		gui.addPushButton("Press and hold to record a sound")->size(500, 40);
//		gui.addPushButton("OK")->size(100, 40);
		gui.addListener(this);
		gui.y = 140;
		activator.addListener(this);
	}
	
	void controlChanged(xmlgui::Event *e) {

		if(e->type==xmlgui::Event::TOUCH_UP && e->control->id=="Sound") {
			List *l = (List*)gui.getControlById("Sound");
			string s = l->getSelectedString();
			string newSoundFile = ofToDataPath("sounds/" + s);
			if(soundFile!=newSoundFile) {
				mustLoadSound = true;
				soundFile = newSoundFile;
			}
		}

		if(e->control->id=="Press and hold to record a sound") {
			if(e->type==xmlgui::Event::TOUCH_DOWN) {
				printf("Start recording\n");
				recording = true;
			} else if(e->type==xmlgui::Event::TOUCH_UP) {
				printf("Stop recording\n");
				recording = false;
			}
			
		}
		if(e->control->id=="settings|close") {
			gui.setEnabled(guiActive);
			if(guiActive) {
			} else {
				//ofSoundStreamStop();
				//ofSoundStreamSetup(2, 0, ofGetAppPtr(), 44100, 512, 4);
				gui.setEnabled(false);
			}
		}
	}

	void draw() {
		
		if(gui.isEnabled()) {
			
			ofEnableAlphaBlending();
			
			ofSetColor(0, 0, 0, 160);
			ofRect(0, 0, ofGetWidth(), ofGetHeight());
			ofSetColor(255);
			title.draw(20, 20);
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
	bool mustLoadSound;
	string soundFile;
	bool recording;
};



