/**
 * ColorPicker.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "ColorPicker.h"
#include "ImageCache.h"

void ColorPicker::setup() {
	colors = ImageCache::getImage("img/colorPicker.png");
	x = 100;
	y = 100;
	width = 100;
	height = 10;
}

void ColorPicker::draw() {
	ofSetHexColor(0xFFFFFF);
	colors->draw(x, y, width, height);
}