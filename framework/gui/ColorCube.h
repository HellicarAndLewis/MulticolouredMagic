/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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