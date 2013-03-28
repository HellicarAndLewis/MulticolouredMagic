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
* ColorPicker.cpp
* ReacticklesMagicMac
*
* Created by Marek Bereza on 13/06/2011.
*
*/

#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif


int ColorPicker::colors[NUM_PICKER_COLORS];


ColorPicker::ColorPicker() {
	int i = 0;
	colors[i++] = 0x4D1965;
	colors[i++] = 0xE50043;
	colors[i++] = 0x0E2356;
	colors[i++] = 0x74AF27;
	colors[i++] = 0xFFEC00;
	colors[i++] = 0xED6B06;
	colors[i++] = 0x6D1B00;
	colors[i++] = 0xA80F79;
	colors[i++] = 0xE7378C;
	colors[i++] = 0x0070BA;
	colors[i++] = 0xC0D886;
	colors[i++] = 0xF0E500;
	colors[i++] = 0xF0856A;
	colors[i++] = 0xE42313;
	colors[i++] = 0xF1DCED;
	colors[i++] = 0xF6B6CB;
	colors[i++] = 0xBDE3F2;
	colors[i++] = 0xF9F3B2;
	colors[i++] = 0xFFFADE;
	colors[i++] = 0xF8E7E2;
	colors[i++] = 0;

}

GlowingBorder glowingBorder;
void ColorPicker::setup() {


	x = 120;
	y = 98+55;

	int PADDING = 9;
	int NUM_COLS = 7;


	fgs = new ColorCube*[NUM_PICKER_COLORS];



	// foreground
	for(int i = 0; i < NUM_PICKER_COLORS; i++) {
		ColorCube *c = new ColorCube();

		c->setup(colors[i]);
		c->x = (i%NUM_COLS)*(c->width+PADDING);
		c->y = (i/NUM_COLS)*(c->height+PADDING);
		c->setListener(this);
		fgs[i] = c;
		add(c);

	}

	pickerBorder = ImageCache::getImage(IMAGE_ROOT + "pickerBorder.png");
	pickerCube = ImageCache::getImage(IMAGE_ROOT + "pickerCube.png");

	glowingBorder.setup(ImageCache::getImage("img/dropShadow.png"), 4);
	cross = ImageCache::getImage(IMAGE_ROOT + "x.png");
	cross->setAnchorPercent(0.5 ,0.5);

	for(int i = 0; i < NUM_PICKER_COLORS; i++) {
		fgs[i]->cross = cross;
		fgs[i]->glowingBorder = &glowingBorder;
		fgs[i]->pickerBorder = pickerBorder;
		fgs[i]->pickerCube = pickerCube;
	}



	selection.setup(ofVec2f(463+37, 130), IMAGE_ROOT+"selection.png");


	inkWell.setup();
	inkWell.x = 485;



	reset();
	add(selection);



	add(inkWell);
}
void ColorPicker::reset() {
	selectFg(Settings::getInstance()->settings["fgColor"]);

}

void ColorPicker::selectFg(int index) {
	// deselect all
	for(int i = 0; i < NUM_PICKER_COLORS; i++) {
		fgs[i]->setSelected(false);
	}

	// select the appropriate one
	fgs[index]->setSelected(true);
	inkWell.setColor(fgs[index]->getColor());
	// save to persistent settings
	Settings::getInstance()->settings["fgColor"] = index;
	Settings::getInstance()->save();
}

void ColorPicker::cubePressed(ColorCube *cube) {

	for(int i = 0; i < NUM_PICKER_COLORS; i++) {
		if(fgs[i]==cube) {
			selectFg(i);
			return;
		}
	}

}
