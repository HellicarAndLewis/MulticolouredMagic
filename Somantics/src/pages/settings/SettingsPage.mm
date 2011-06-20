/**
 * SettingsPage.mm
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "SettingsPage.h"
#include "constants.h"
#include "ImageCache.h"
#include "constants.h"

void SettingsPage::setup() {
	
	
	settingsTitle.setup(ofVec2f(39, 85), IMAGE_ROOT + "settingsTitle.png");
	colourPickerTitle.setup(ofVec2f(276, 110), IMAGE_ROOT + "colourPickerTitle.png");
	colorPicker.setup();
	slider.setup();
	slider.y += 57;
	
	if(IPAD) {
		bgImage = ImageCache::getImage("img/bgIPad.png");
	} else if(HI_RES) {
		bgImage = ImageCache::getImage("img/bgIPhone4.png");
	} else {
		bgImage = ImageCache::getImage("img/bgIPhone.png");
	}
	
	logo.setup(ofVec2f(WIDTH/2 - 150, 35), IMAGE_ROOT + "logo.png");



	add(&settingsTitle);
	add(&colourPickerTitle);
	add(&colorPicker);
	add(&slider);
	add(&logo);	
	
	resetButton.setup("reset", ofVec2f(987, 53), IMAGE_ROOT+"reset.png", IMAGE_ROOT+"resetDown.png");
	add(&resetButton);
	resetButton.setListener(this);
}


void SettingsPage::buttonPressed(string name) {
	if(name=="reset") {
		Settings::getInstance()->reset();
		colorPicker.reset();
	}
}

void SettingsPage::draw() {	
	ofSetHexColor(0xFFFFFF);
	bgImage->draw(0, 0, ofGetWidth(), ofGetHeight());
	//settingsTitle->draw(39, 35);
//	colourPickerTitle->draw(260, 59);
	//logo->draw(WIDTH/2, HEIGHT - 20);
	Container::draw();
}
