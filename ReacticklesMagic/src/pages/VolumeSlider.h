/**
 * VolumeSlider.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 13/06/2011.
 *
 */

#include "InteractiveObject.h"
#include "ImageCache.h"
#include "constants.h"
#include "Settings.h"

class VolumeSlider: public InteractiveObject {
public:
	
	void setup() {
		x = 870;
		y = 77+55;
		sliderBG = ImageCache::getImage(IMAGE_ROOT+"volumeSliderBG.png");
		width = sliderBG->getWidth();
		height = sliderBG->getHeight();
		sliderHandle = ImageCache::getImage(IMAGE_ROOT+"sliderHandle.png");
		sliderHandle->setAnchorPercent(0.5, 0.5);
		value = &Settings::getInstance()->settings["volume"];
	}
	void draw() {
		ofSetHexColor(0xFFFFFF);
		sliderBG->draw(x, y);
		float yy = ofMap(*value, 0, 1, 389+this->y, 69+this->y, true);
		sliderHandle->draw(x + sliderBG->getWidth()/2, yy);
	}
	
	bool touchDown(float x, float y, int touchId) {
		if(inside(x, y)) {
			*value = ofMap(y, 69+this->y, 389+this->y, 1, 0, true);
			return true;
			
		}
		return false;
	}
	
	bool touchUp(float x, float y, int touchId) {
		
		touchDown(x, y, touchId);
		if(inside(x, y)) {
			Settings::getInstance()->save();
			return true;
		}
		return false;
	}
	
	bool touchMoved(float x, float y, int touchId) {
		return touchDown(x, y, touchId);
		
	}
private:
	float *value;
	ofImage *sliderBG;
	ofImage *sliderHandle;
};