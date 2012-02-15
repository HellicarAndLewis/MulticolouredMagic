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
	
	settingsTitle.setup(ofVec2f(39, 110), IMAGE_ROOT + "settingsTitle.png");	
	colourPickerTitle.setup(ofVec2f(273-74, 115+98-44), IMAGE_ROOT + "colourPickerTitle.png");
	colourText.setup(ofVec2f(116, 424), IMAGE_ROOT + "colourText.png");
	micLevelText.setup(ofVec2f(725, 675), IMAGE_ROOT + "micLevelText.png");
	micLevelTitle.setup(ofVec2f(870+20-4, 657-305), IMAGE_ROOT + "micLevelTitle.png");
	brightnessTitle.setup(ofVec2f(870-126-15, 657-280), IMAGE_ROOT + "brightnessTitle.png");
	
	
	colorPicker.setup();
	colorPicker.y += 60;
	colorPicker.x = 41;
	
	slider.setup();
	
	slider.x = 739;
	slider.y = 188;
	
	volumeSlider.setup();
	volumeSlider.x = 897;
	volumeSlider.y = slider.y;

	
	if(IPAD) {
		bgImage.setup(ofVec2f(), "img/bg.png");
	} else if(HI_RES) {
		bgImage.setup(ofVec2f(), "img/bgIPhone4.png");
	} else {
		bgImage.setup(ofVec2f(), "img/bgIPhone.png");
	}
	
	
	logo.setup(ofVec2f(), IMAGE_ROOT + "logo.png");
	logo.x = WIDTH/2 - logo.width/2;
	logo.y = 35;
	
	
	
	add(bgImage);	
	add(colourText);
	add(micLevelText);
	add(colorPicker);
	add(slider);
	add(brightnessTitle);
	add(micLevelTitle);
	add(colourPickerTitle);
	add(volumeSlider);
	add(settingsTitle);

	add(logo);

	


}


void SettingsPage::buttonPressed(string name) {
	
}


	   
void SettingsPage::draw() {
	volumeSlider.setVolume(volume);
	Reactickle::draw();
//	ofSetHexColor(0xFF0000);
//	ofRect(0, 0, ofMap(volume, 0, 1, 0, WIDTH), 20);
}