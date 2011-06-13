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
	
	settingsTitle.setup(ofVec2f(39, 35+55), IMAGE_ROOT + "settingsTitle.png");	
	colourPickerTitle.setup(ofVec2f(273, 115), IMAGE_ROOT + "colourPickerTitle.png");
	
	
	colorPicker.setup();
	slider.setup();
	volumeSlider.setup();
	

	
	if(IPAD) {
		bgImage.setup(ofVec2f(), "img/bgIPad.png");
	} else if(HI_RES) {
		bgImage.setup(ofVec2f(), "img/bgIPhone4.png");
	} else {
		bgImage.setup(ofVec2f(), "img/bgIPhone.png");
	}
	
	
	logo.setup(ofVec2f(), IMAGE_ROOT + "logo.png");
	logo.x = WIDTH/2 - logo.width/2;
	logo.y = 35;
	
	
	
	resetButton.setup("reset", ofVec2f(987, 53), IMAGE_ROOT+"reset.png", IMAGE_ROOT+"resetDown.png");
	resetButton.setListener(this);
	
	
	add(bgImage);	
	add(colorPicker);
	add(slider);
	add(colourPickerTitle);
	add(volumeSlider);
	add(settingsTitle);

	add(logo);

	
	add(resetButton);

}


void SettingsPage::buttonPressed(string name) {
	if(name=="reset") {
		Settings::getInstance()->reset();
		colorPicker.reset();
	}
}

	   
