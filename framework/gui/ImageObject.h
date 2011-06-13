/**
 * ImageObject.h
 * ReacticklesMagic
 *
 * Lets you draw a simple image to the screen in the display hierarchy.
 *
 * Created by Marek Bereza on 13/06/2011.
 *
 */
#include "InteractiveObject.h"
#include "ImageCache.h"
#pragma once
class ImageObject: public InteractiveObject {
public:
	ofImage *img;
	void setup(ofVec2f pos, string path) {
		x = pos.x;
		y = pos.y;
		img = ImageCache::getImage(path);
		width = img->getWidth();
		height = img->getHeight();
	}
	
	void draw() {
		ofSetHexColor(0xFFFFFF);
		img->draw(x, y, width, height);
	}
};