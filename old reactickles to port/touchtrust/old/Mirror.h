/*
 *  PerlinMirror.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */
#include "TTApp.h"

// delay, slitscan, glitch

#include <deque>
#define MAX_FRAMES 72


#define GRID		0
#define SLITSCAN	1
#define GLITCH		2
#define NUM_MODES	3

#define GRID_ROWS 5
#define GRID_COLS 5

class Mirror: public TTApp {
public:
	
	void setup() {
		mode = GRID;
		gui->saveToXML();
		gui->addPage("Mirror");
		gui->addSlider("MirrorMode", mode, 0, 2);
		gui->loadFromXML();
	}
	
	void init() {
		gui->setPage("Mirror");
	}
	
	void update() {
		if(buffer.size()>MAX_FRAMES) {
			delete buffer.front();
			buffer.pop_front();
		}
		ofTexture *img = new ofTexture();
		img->allocate(VISION_WIDTH, VISION_HEIGHT, GL_RGB);
		img->loadData(cam->getPixels(), VISION_WIDTH, VISION_HEIGHT, GL_RGB);

		
		buffer.push_back(img);
		
	}
	
	void draw() {
		
		if(buffer.size()<0) return;
		ofSetHexColor(0xFFFFFF);
		if(mode==GLITCH) {
			
			int frame = ofNoise((float)ofGetFrameNum()/10.f)*buffer.size();
			buffer[frame]->draw(0, 0, ofGetWidth(), ofGetHeight());
		//} else if(mode==DELAY) {
		//	buffer[0]->draw(0, 0, ofGetWidth(), ofGetHeight());
		} else if(mode==GRID) {
			float width = ofGetWidth()/GRID_COLS;
			float height = ofGetHeight()/GRID_ROWS;
			
			for(int i = 0; i*2 < buffer.size() && i < GRID_ROWS*GRID_COLS; i++) {
				float x = (int)i%GRID_COLS;
				x *= width;
				float y = (int)i/GRID_COLS;
				y *= height;
				
				int frameIndex = buffer.size() - i*2 - 1;
				buffer[frameIndex]->draw(x, y, width, height);
			}
		} else if(mode==SLITSCAN) {
			float bufferSize = buffer.size();
			for(int i = 0; i < bufferSize; i++) {
				int frameIndex = buffer.size() - i - 1;
				buffer[frameIndex]->bind();
				glBegin(GL_QUADS);
				
				float topImage = (float)i*buffer[i]->getHeight()/bufferSize;
				float topScreen = (float)i*ofGetHeight()/bufferSize;
				
				glTexCoord2f(0, topImage);
				glVertex2f(0, topScreen);
				
				
				glTexCoord2f(buffer[frameIndex]->getWidth(), topImage);
				glVertex2f(ofGetWidth(), topScreen);
				
				
				float bottomImage = (float)(i+1)*buffer[frameIndex]->getHeight()/bufferSize;
				float bottomScreen = (float)(i+1)*ofGetHeight()/bufferSize;
				
				glTexCoord2f(buffer[frameIndex]->getWidth(), bottomImage);
				glVertex2f(ofGetWidth(), bottomScreen);
				
				
				
				glTexCoord2f(0, bottomImage);
				glVertex2f(0, bottomScreen);
				
				
				
				glEnd();
				
				buffer[frameIndex]->unbind();
			}
		}
	}
	
	
	
	void mousePressed(int x, int y, int button) {
		mode++;
		if(mode>=NUM_MODES) {
			mode = GRID;
		}
	}
	
	// all the frames to remember
	deque<ofTexture*> buffer;
	

	
	// which mode we're in
	int mode;
	
};