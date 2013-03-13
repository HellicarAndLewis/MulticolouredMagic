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

class SamplerGui: public xmlgui::Listener {
public:
	
	ofRectangle activator;
	bool overActivator;
	
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
	void setup() {
		holdCount = 0;
		overActivator = false;
		activator.set(10, 10, 70, 30);
		input = INPUT_TOUCH;
		scale = 0;
		mustLoadSound = false;
		key = 0;
		soundId = 0;
		recording = false;
		showCamera = true;
		noteRange = 16;
		gui.setWidth(500);
		gui.addSegmented("Input", input, "Front Camera|Accelerometer|Touch")->height = 40;
		
		gui.addSegmented("Scale", scale, "PENTATONIC|MAJOR|MINOR|CHROMATIC")->height = 40;
		gui.addSegmented("Key", key, "C|C#|D|D#|E|F|F#|G|G#|A|A#|B")->height = 40;
		gui.addSegmented("Show Camera", showCamera, "NO|YES")->height = 40;
		Slider *s = gui.addSlider("Note Range", noteRange, 5, 30);

		
		s->height = 40;
		s->stepped = true;
		
		ofDirectory samples;
		int numSounds = samples.listDir("sounds");
		vector<string> sounds;
		for(int i = 0; i < numSounds; i++) {
			printf("Sample: '%s'\n", samples.getName(i).c_str());
			sounds.push_back(samples.getName(i));
		}
		
		List *l = gui.addList("Sound", soundId, sounds);
		l->itemHeight = 40;
		l->height = 160;
		//gui.addPushButton("Press and hold to record a sound")->size(500, 40);
		gui.addPushButton("OK")->size(100, 40);
		gui.addListener(this);
	}
	
	void controlChanged(xmlgui::Event *e) {
		if(e->control->id=="OK") {
			gui.setEnabled(false);
		}
		if(e->control->id=="Sound") {
			mustLoadSound = true;
			List *l = (List*)gui.getControlById("Sound");
			string s = l->getSelectedString();
			soundFile = ofToDataPath("sounds/" + s);
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
	}
	void enableGui() {
		gui.setEnabled(true);
	}
	
	void draw() {
		int MAX_HOLD_COUNT = 20;
		if(!gui.isEnabled()) {
			if(overActivator) {
				holdCount++;
			} else {
				holdCount = 0;
			}
			
			if(holdCount>MAX_HOLD_COUNT) {
				gui.setEnabled(true);
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
			ofSetColor(0, 0, 0, 100);

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
	bool mustLoadSound;
	string soundFile;
	bool recording;
	int holdCount;
};



