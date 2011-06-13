/**
* ColorPicker.cpp
* ReacticklesMagicMac
*
* Created by Marek Bereza on 13/06/2011.
*
*/

#include "ColorPicker.h"



ColorPicker::ColorPicker() {
	
	
}

GlowingBorder glowingBorder;
void ColorPicker::setup() {
	int colors[NUM_PICKER_COLORS] = {
		0x4D1965,
		0xE50043,
		0x0E2356,
		0x74AF27,
		0xFFEC00,
		0xED6B06,
		0x6D1B00,
		
		0xA80F79,
		0xE7378C,
		0x0070BA,
		0xC0D886,
		0xF0E500,
		0xF0856A,
		0xE42313,
		
		0xF1DCED,
		0xF6B6CB,
		0xBDE3F2,
		0xF9F3B2,
		0xFFFADE,
		0xF8E7E2,
		0xFBE0EE
	};
	
	x = 120;
	y = 98+55;
	
	int PADDING = 9;
	int NUM_COLS = 7;
	int BG_Y_OFFSET = 234;
	
	
	fgs = new ColorCube*[NUM_PICKER_COLORS];
	bgs = new ColorCube*[NUM_PICKER_COLORS];
	
	
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
	
	// background
	
	for(int i = 0; i < NUM_PICKER_COLORS; i++) {
		ColorCube *c = new ColorCube();
		
		c->setup(colors[i], true);
		
		c->x = (i%NUM_COLS)*(c->width+PADDING);
		c->y = BG_Y_OFFSET + (i/NUM_COLS)*(c->height+PADDING);
		c->setListener(this);
		bgs[i] = c;
		add(c);
	}
	
	
	glowingBorder.setup(ImageCache::getImage("img/dropShadow.png"), 4);
	cross = ImageCache::getImage(IMAGE_ROOT + "x.png");
	cross->setAnchorPercent(0.5 ,0.5);
	
	for(int i = 0; i < NUM_PICKER_COLORS; i++) {
		fgs[i]->cross = cross;
		bgs[i]->cross = cross;
		fgs[i]->glowingBorder = &glowingBorder;
		bgs[i]->glowingBorder = &glowingBorder;
	}
	
	
	bgTitle.setup(ofVec2f(520, 120), IMAGE_ROOT+"background.png");
	fgTitle.setup(ofVec2f(520, 300), IMAGE_ROOT+"foreground.png");
	bg.x = fg.x = 520;
	fg.y = 133;
	bg.y = 235;

	fg.setup(1, false);
	bg.setup(2, true);
	reset();
	add(fgTitle);
	add(bgTitle);
	add(fg);
	add(bg);
	
}
void ColorPicker::reset() {
	selectFg(Settings::getInstance()->settings["fgColor"]);
	selectBg(Settings::getInstance()->settings["bgColor"]);
}

void ColorPicker::selectFg(int index) {
	// deselect all
	for(int i = 0; i < NUM_PICKER_COLORS; i++) {
		fgs[i]->setSelected(false);
	}
	
	// select the appropriate one
	fgs[index]->setSelected(true);
	fg.setColor(fgs[index]->getColor());
	// save to persistent settings
	Settings::getInstance()->settings["fgColor"] = index;
	Settings::getInstance()->save();
}

void ColorPicker::selectBg(int index) {
	// deselect all
	for(int i = 0; i < NUM_PICKER_COLORS; i++) {
		bgs[i]->setSelected(false);
	}
	
	// select the appropriate one
	bgs[index]->setSelected(true);
	bg.setColor(bgs[index]->getColor());
	
	// save to persistent settings
	Settings::getInstance()->settings["bgColor"] = index;
	Settings::getInstance()->save();
}

void ColorPicker::cubePressed(ColorCube *cube) {
	if(cube->getIsBackground()) {
		
		// find the colour's index
		for(int i = 0; i < NUM_PICKER_COLORS; i++) {
			if(bgs[i]==cube) {
				selectBg(i);
				return;
			}
		}
	} else {
		for(int i = 0; i < NUM_PICKER_COLORS; i++) {
			if(fgs[i]==cube) {
				selectFg(i);
				return;
			}
		}
	}
}
