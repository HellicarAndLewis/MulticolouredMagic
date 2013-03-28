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
 * VolumeSlider.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 13/06/2011.
 *
 */

#include "InteractiveObject.h"
#include "ImageCache.h"
#include "constants.h"
#include "Settings.h"

class VolumeSlider: public InteractiveObject {
public:
	
	void setVolume(float volume) {
		this->volume = volume;
	}
	void setup() {
		x = 870;
		y = 77+55;
		sliderBG = ImageCache::getImage(IMAGE_ROOT+"volSliderBG.png");
		sliderFull = ImageCache::getImage(IMAGE_ROOT+"volSliderBGFull.png");
		peakOn = ImageCache::getImage(IMAGE_ROOT+"peakOn.png");
		peakOff = ImageCache::getImage(IMAGE_ROOT+"peakOff.png");
		
		width = sliderBG->getWidth();
		height = sliderBG->getHeight();
		sliderHandle = ImageCache::getImage(IMAGE_ROOT+"sliderHandle.png");
		sliderHandle->setAnchorPercent(0.5, 0.5);
		value = &Settings::getInstance()->settings["volume"];
		lastTimePeaked = -100;
	}
	
	float lastTimePeaked;
	
	void triggerPeak() {
		lastTimePeaked = ofGetElapsedTimef();
	}
	void draw() {
		ofSetHexColor(0xFFFFFF);
		
		sliderBG->draw(x, y);
		float yy = ofMap(*value, 0, 1, 389+this->y, 69+this->y, true);
		
		//maskOn(0, 500, ofGetWidth()/2, ofGetHeight()/4);//x, y, width, height/2);
		//sliderFull->draw(x, y);
		sliderFull->bind();
		ofMesh shape;
		float vol = volume;
		if(vol>=0.3) triggerPeak();
		// 0.3 is the volume threshold for reactickles
		float top = ofMap(vol, 0, 0.3, 0.84, 0.06, true);

//		printf("%f\n", top);
//		0.06 is the top
//		0.84 is the bottom
		
		shape.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		shape.addTexCoord(ofVec2f(0, top));
		shape.addVertex(ofVec2f(x, y+height*top));
		
		shape.addTexCoord(ofVec2f(1, top));
		shape.addVertex(ofVec2f(x+width, y+height*top));
		
		shape.addTexCoord(ofVec2f(0, 1));
		shape.addVertex(ofVec2f(x, y+height));
		
		shape.addTexCoord(ofVec2f(1, 1));
		shape.addVertex(ofVec2f(x+width, y+height));

		
		shape.draw();
		sliderFull->unbind();
		sliderHandle->draw(x + sliderBG->getWidth()/2, yy);
		//ofRect(0, 0, ofGetWidth(), ofGetHeight());
		//maskOff();
		
		peakOff->draw(x, y-40);
		
		float t = ofGetElapsedTimef() - lastTimePeaked;
		if(t<1) {
			glColor4f(1, 1, 1, ofMap(t, 0, 1, 1, 0));
			peakOn->draw(x, y-40);
		}
	}
	
	bool touchDown(float x, float y, int touchId) {
		if(inside(x, y)) {
			*value = ofMap(y, 69+this->y, 389+this->y, 1, 0, true);
			return true;
			
		}
		return false;
	}
	
	bool touchUp(float x, float y, int touchId) {
		
		touchDown(x, y, touchId);
		if(inside(x, y)) {
			Settings::getInstance()->save();
			return true;
		}
		return false;
	}
	
	
	void maskOn(int _x, int _y, int _w, int _h) {
		glEnable(GL_SCISSOR_TEST);
		glScissor(_x, ofGetHeight()-(_y+_h), _w, _h);
	}
	void maskOff() {
		glDisable(GL_SCISSOR_TEST);
	}
	
	bool touchMoved(float x, float y, int touchId) {
		return touchDown(x, y, touchId);
		
	}
private:
	float *value;
	ofImage *sliderBG;
	ofImage *sliderHandle;
	ofImage *sliderFull;
	ofImage *peakOff;
	ofImage *peakOn;
	float volume;
};