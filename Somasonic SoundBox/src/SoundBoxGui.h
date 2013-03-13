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

class SoundBoxGui: public xmlgui::Listener {
public:
	
	ofRectangle activator;
	bool overActivator;
	
	xmlgui::SimpleGui gui;
	int numPads;
	int holdCount;

	void setup() {
		holdCount = 0;
		overActivator = false;
		activator.set(10, 10, 70, 30);

		gui.setWidth(500);
		gui.addSlider("Number of Pads", numPads, 1, 11)->height = 40;
		gui.addSegmented("loop", (int&)MiniSampler::looping, "OFF|ON")->size(100, 40);
		gui.addSegmented("trigger", Pad::triggerType, "MOMENTARY|TOGGLE")->height=40;
		gui.addPushButton("OK")->size(100, 40);
		gui.addListener(this);
	}
	
	void controlChanged(xmlgui::Event *e) {
		if(e->control->id=="OK") {
			gui.setEnabled(false);
		}
	}
	void enableGui() {
		gui.setEnabled(true);
	}
	
	void draw() {
		int MAX_HOLD_COUNT = 30;
		if(!gui.isEnabled()) {
			if(overActivator) {
				holdCount++;
			} else {
				holdCount = 0;
			}
			if(holdCount>MAX_HOLD_COUNT) {
				enableGui();
				holdCount = 0;
			}
		}
		if(!gui.isEnabled()) {
			glColor4f(1, 1, 1, 0.5);
			ofRect(activator);
			glColor4f(1,1,1,1);
			ofRect(activator.x, activator.y, activator.width*ofMap(holdCount, 0, MAX_HOLD_COUNT, 0, 1), activator.height);
			
			ofSetHexColor(0);
			ofDrawBitmapString("MENU", activator.x+3, activator.y+15);
		} else {
			ofEnableAlphaBlending();
			ofSetColor(0, 0, 0, 60);
			ofRect(0, 0, ofGetWidth(), ofGetHeight());
		}
	}
	
	
	void touchDown(int id, float x, float y) {
		if(!gui.isEnabled()) {
			overActivator = activator.inside(x, y);
		}
	}
	
	
	void touchUp(int id, float x, float y) {
		if(!gui.isEnabled()) {
			overActivator = activator.inside(x, y);
			
		}
		
		overActivator = false;
	}
	
	void touchMoved(int id, float x, float y) {
		if(!gui.isEnabled()) {
			overActivator = activator.inside(x, y);
		}
	
	}
};



