/**
 * ColorPicker.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */
#include "InteractiveObject.h"

class ColorPicker: public InteractiveObject {
public:
	void setup();
	void draw();
	ofImage *colors;
};