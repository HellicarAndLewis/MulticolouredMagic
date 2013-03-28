/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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