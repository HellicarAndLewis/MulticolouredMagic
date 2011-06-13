/**
 * ColorCube.h
 * SomanticsMac
 *
 * Created by Marek Bereza on 11/05/2011.
 *
 */

#include "InteractiveObject.h"
#include "GlowingBorder.h"

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
		cross = NULL;
		
		listener = NULL;
	}
	ofImage *cross;
	GlowingBorder *glowingBorder;
	
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
		
		if(selected) {
			ofVec2f points[4];
			points[0] = ofVec2f(x, y);
			points[1] = ofVec2f(x+width, y);
			points[2] = ofVec2f(x+width, y+height);
			points[3] = ofVec2f(x, y+height);
			glowingBorder->draw(points, ofColor(255, 150));
		}
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
		
		if(selected && cross!=NULL) {
			ofSetHexColor(0xFFFFFF);

			glPushMatrix();
			
			glTranslatef(x + width/2, y + height/2, 0);
			cross->draw(0, 0);
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
	
	int getColor() {
		return color;
	}
	void setColor(int color) {
		this->color = color;
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