/**
 * ColorCube.h
 * SomanticsMac
 *
 * Created by Marek Bereza on 11/05/2011.
 *
 */

#include "InteractiveObject.h"

class ColorCube: public InteractiveObject {
public:
	ColorCube() {
		width = 46;
		height = width;
		color = 0;
	}
	void setup(int color) {
		this->color = color;
	}
	
	void draw() {
		ofSetHexColor(color);
		ofRect(*this);
	}
private:
	int color;
		
};