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
 *  RecordButton.h, created by Marek Bereza on 13/03/2013.
 */

#include "LabeledControl.h"

class RecordButtonListener {
public:
	virtual void recordingStarted() = 0;
	virtual void recordingEnded() = 0;
};

class RecordButton: public LabeledControl {
public:
	RecordButtonListener *recListener;
	RecordButton(): LabeledControl() {
		recListener = NULL;
		name = "PRESS TO RECORD";
		width = 140;
		height = 40;
		wasRecording = false;
	}
	
	bool wasRecording;
	
	void draw() {
		
		if(down && !wasRecording) {
			if(recListener!=NULL) recListener->recordingStarted();
		} else if(!down && wasRecording) {
			if(recListener!=NULL) recListener->recordingEnded();
		}
		
		
		wasRecording = down;
		if(down) {
			ofSetHexColor(0xFF0000);
		} else {
			ofSetHexColor(0x990000);
		}
		
		ofRect(*this);
		
		ofSetHexColor(0xFFFFFF);
		if(down) {
			ofDrawBitmapString("RECORDING", x + 3, y+16);
		} else {
			ofDrawBitmapString("HOLD DOWN TO RECORD", x + 3, y+16);
		}
		
		
		
	}
	
	
	
};