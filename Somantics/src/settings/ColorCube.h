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
		width = 58;
		height = width;
		color = 0;
	}
	// if it's a foreground one, draw it as a filled rect
	// if it's a background one draw it as a stroked rect.
	void setup(int color, bool isBackground = false) {
		this->color = color;
		this->isBackground = isBackground;
	}
	
	void draw() {
		ofSetHexColor(color);
		if(isBackground) {
			int r = 3;
			// top bar
			ofRect(x - r, y - r, width + r*2, r*2);
			
			// bottom bar
			ofRect(x - r, y + height - r, width + r*2, r*2);
			
			// left bar
			ofRect(x - r, y + r, r*2, height - r*2);

			// right bar
			ofRect(x + width - r, y + r, r*2, height - r*2);
			
		} else {
			ofRect(*this);
		}
	}
private:
	int color;
	bool isBackground;
		
};