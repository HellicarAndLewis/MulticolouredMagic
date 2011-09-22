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
		pickerCube = NULL;
		pickerBorder = NULL;
	}
	ofImage *cross;
	GlowingBorder *glowingBorder;
	ofImage *pickerBorder;
	ofImage *pickerCube;
	ofImage *multicoloured;
	void setListener(ColorCubeListener *listener) {
		this->listener = listener;
	}
	// if it's a foreground one, draw it as a filled rect
	// if it's a background one draw it as a stroked rect.
	void setup(int color) {
		this->color = color;
		multicoloured = ImageCache::getImage(IMAGE_ROOT + "multimini.png");
	}
	
	void draw() {
		
		/*if(selected) {
			ofVec2f points[4];
			points[0] = ofVec2f(x, y);
			points[1] = ofVec2f(x+width, y);
			points[2] = ofVec2f(x+width, y+height);
			points[3] = ofVec2f(x, y+height);
			glowingBorder->draw(points, ofColor(255, 150));
		}*/
		if(color!=0) {
			ofSetHexColor(color);
			if(pickerCube!=NULL) pickerCube->draw(x, y);
		} else {
			ofSetHexColor(0xFFFFFF);
			if(multicoloured!=NULL) multicoloured->draw(x, y);
		}
		
//		ofRect(*this);

		
		if(selected && cross!=NULL) {
			ofSetHexColor(0xFFFFFF);

			glPushMatrix();
			
			glTranslatef(x + width/2, y + height/2, 0);
			cross->draw(1, 1);
			glPopMatrix();
		}

		
		ofSetHexColor(0xFFFFFF);
		if(pickerBorder!=NULL) pickerBorder->draw(x, y);
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

private:
	bool selected;
	int color;
	ColorCubeListener *listener;
		
};