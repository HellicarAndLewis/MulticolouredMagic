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
	
	settingsTitle.setup(ofVec2f(39, 35+55+20), IMAGE_ROOT + "settingsTitle.png");	
	colourPickerTitle.setup(ofVec2f(273-18, 115+98), IMAGE_ROOT + "colourPickerTitle.png");
	
	
	colorPicker.setup();
	colorPicker.y += 108;
	colorPicker.x -= 18;
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
	
	
	
	add(bgImage);	
	add(colorPicker);
	add(slider);
	add(colourPickerTitle);
	add(volumeSlider);
	add(settingsTitle);

	add(logo);

	


}


void SettingsPage::buttonPressed(string name) {
	
}

	   
void SettingsPage::draw() {
	Reactickle::draw();
	ofSetHexColor(0xFF0000);
	ofRect(0, 0, ofMap(volume, 0, 1, 0, WIDTH), 20);
}