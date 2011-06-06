/**
 * ColorCube.h
 * SomanticsMac
 *
 * Created by Marek Bereza on 11/05/2011.
 *
 */

#include "InteractiveObject.h"
class ColorCube;

class ColorCubeListener {
public:
	virtual void cubePressed(ColorCube *cube) = 0;
};
class ColorCube: public InteractiveObject {
public:
	ColorCube() {
		width = 58;
		height = width;
		color = 0;
		selected = false;
		
		listener = NULL;
	}
	
	void setListener(ColorCubeListener *listener) {
		this->listener = listener;
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
		
		if(selected) {
			ofSetHexColor(0xFFFFFF);
			int c = 3;
			glPushMatrix();
			glTranslatef(x + width/2, y + height/2, 0);
			glRotatef(40, 0, 0, 1);
			ofRect(-c, -height/2, c*2, height);
			ofRect(-width/2, -c, width, c*2);
			glPopMatrix();
		}
	}
	
	void setSelected(bool selected) {
		this->selected = selected;
	}
	bool touchDown(float x, float y, int touchId) {
		if(inside(x, y)) {
			if(listener!=NULL) {
				listener->cubePressed(this);
			}
			return true;
			
		}
		return false;
	}
	
	bool touchUp(float x, float y, int touchId) {
		return touchDown(x, y, touchId);
	}
	
	bool touchMoved(float x, float y, int touchId) {
		return touchDown(x, y, touchId);
	}
	bool getIsBackground() { return isBackground; }

private:
	bool selected;
	int color;
	bool isBackground;
	ColorCubeListener *listener;
		
};