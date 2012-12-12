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

class SoundBoxGui: public xmlgui::Listener {
public:
	
	ofRectangle activator;
	bool overActivator;
	
	xmlgui::SimpleGui gui;
	int numPads;


	void setup() {
		overActivator = false;
		activator.set(10, 10, 70, 30);

		gui.setWidth(500);
		gui.addSlider("Number of Pads", numPads, 1, 11)->height = 40;
		gui.addSegmented("loop", (int&)MiniSampler::looping, "OFF|ON")->size(100, 40);
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
		if(!gui.isEnabled()) {
			if(overActivator) ofSetHexColor(0xFF0000);
			else ofSetHexColor(0xFFFFFF);
			ofRect(activator);
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
			if(overActivator) {
				enableGui();
			}
		}
		
		overActivator = false;
	}
	
	void touchMoved(int id, float x, float y) {
		if(!gui.isEnabled()) {
			overActivator = activator.inside(x, y);
		}
	}
};



