/**
 * ModeDisplay.h
 * ReacticklesMagicMac
 *
 * Created by Marek Bereza on 13/06/2011.
 *
 */
#include "constants.h"
#include "ImageCache.h"

// in seconds - display time is how long it stays on the screen before fading
// and the fade time is how long it takes to fade out.
#define MODE_DISPLAY_TIME 1
#define MODE_FADE_TIME 1
class ModeDisplay {
public:
	ofImage **modes;
	int numModes;
	int mode;
	float lastTimeChanged;
	ModeDisplay() {
		mode = 0;
		numModes = 3;
		lastTimeChanged = 0;
	}
	
	void setup() {
		modes = new ofImage*[3];
		for(int i = 0; i < numModes; i++) {
			modes[i] = ImageCache::getImage(IMAGE_ROOT + "mode"+(ofToString(i+1))+".png");
			modes[i]->setAnchorPercent(0.5, 0.5);
		}
	}
	
	void setMode(int mode) {
		this->mode = mode;
		lastTimeChanged = ofGetElapsedTimef();
	}
	
	void draw() {
		float timeSinceLastChange = ofGetElapsedTimef() - lastTimeChanged;
		// should we draw?
		if(timeSinceLastChange>0 && timeSinceLastChange<MODE_DISPLAY_TIME+MODE_FADE_TIME) {
			float alpha = 0;
			if(timeSinceLastChange<MODE_DISPLAY_TIME) {
				// we're just displaying
				alpha = ofMap(timeSinceLastChange, 0, 0.2, 0, 1, true);
			} else {
				// we're fading out
				alpha = ofMap(timeSinceLastChange - MODE_DISPLAY_TIME, 0, MODE_FADE_TIME, 1, 0, true);
			}
			ofSetColor(255, 255, 255, 255*alpha);
			modes[mode]->draw(WIDTH/2, HEIGHT/2);
		}
	}
};