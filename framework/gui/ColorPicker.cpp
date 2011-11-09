/**
* ColorPicker.cpp
* ReacticklesMagicMac
*
* Created by Marek Bereza on 13/06/2011.
*
*/

#include "ColorPicker.h"

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
