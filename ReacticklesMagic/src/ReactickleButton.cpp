/**
 * ReactickleButton.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

#include "ReactickleButton.h"
#include "ImageCache.h"
ReactickleButton::ReactickleButton(string screenshotUrl) {
	screenshot = ImageCache::getImage(screenshotUrl);
	width = screenshot->getWidth();
	height = screenshot->getHeight();
}

void ReactickleButton::draw() {
	ofSetHexColor(0xFFFFFF);
	screenshot->draw(x, y, width, height);
}