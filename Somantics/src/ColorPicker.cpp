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

	// so we've got rgba
	int size = colors->getWidth()*4;
	colorVals = new unsigned char[size];

	memcpy(colorVals, colors->getPixels(), colors->getWidth()*4);
	
	x = 100;
	y = 100;
	width = 150;
	height = 20;
}

void ColorPicker::draw() {
	ofSetHexColor(0xFFFFFF);
	colors->draw(x, y, width, height);
}

ofColor ColorPicker::getColor(int pos) {
	if(pos<0) pos==0;
	if(pos>=colors->getWidth()) {
		pos = colors->getWidth()-1;
	}

	return ofColor(colorVals[pos*4], colorVals[pos*4 + 1], colorVals[pos*4 + 2], 255);
}

bool ColorPicker::touchDown(float xx, float yy, int tid) {
	return touchUp(xx, yy, tid);
}

bool ColorPicker::touchMoved(float xx, float yy, int tid) {
	return touchUp(xx, yy, tid);
}

bool ColorPicker::touchUp(float xx, float yy, int tid) {
	if(inside(xx,yy)) {
		float xxx = xx - x;
		xxx *= colors->getWidth();
		xxx /= width;
		ofColor c = getColor((int)xxx);
		printf("%f %f %f\n", c.r, c.g, c.b);
		return true;
	}
	return false;
}