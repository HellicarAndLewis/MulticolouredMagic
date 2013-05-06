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

/*
 *  Vision.h
 *  sampler
 *
 *  Created by Marek Bereza on 27/04/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

//#include "ofxControlPanel.h"
//#include "AppSettings.h"

#include "ofMain.h"
#include "ofxOpenCv.h"
//#include "customDrawer.h"
//#include "ofxCvOpticalFlowLK.h"

#ifdef TARGET_OF_IPHONE
#define VISION_WIDTH 480
#define VISION_HEIGHT 360
#else
#define VISION_WIDTH 320
#define VISION_HEIGHT 240
#endif
class Vision {
public:
	ofVideoGrabber *video;
	ofxCvColorImage camImg;
	ofxCvGrayscaleImage greyImg;
//	ofxCvGrayscaleImage greyLast;
	ofxCvGrayscaleImage bgImg;
	ofxCvGrayscaleImage diffImg;
	ofxCvGrayscaleImage blendImage;
	
//	ofxCvOpticalFlowLK flow;
	
	//ofxControlPanel *gui;
	
	//customDrawer bgColorPicker;
	//customDrawer noteColorPicker;
	
	vector<pair<ofRectangle, float> > levels;
	bool vertical;
	void setup() {//ofxControlPanel *_gui) {
		vertical = true;
		numLevels = 18;
		//gui = _gui;
		camImg.allocate(VISION_WIDTH, VISION_HEIGHT);
		greyImg.allocate(VISION_WIDTH, VISION_HEIGHT);
//		greyLast.allocate(VISION_WIDTH, VISION_HEIGHT);
		bgImg.allocate(VISION_WIDTH, VISION_HEIGHT);
		diffImg.allocate(VISION_WIDTH, VISION_HEIGHT);
		blendImage.allocate(VISION_WIDTH, VISION_HEIGHT);
//		flow.allocate(VISION_WIDTH, VISION_HEIGHT);
		
		bgImg.set(0);
		
		//gui->setWhichPanel("vision");
		//gui->setWhichColumn(0);
		//gui->addDrawableRect("video", &camera, 320, 240);
		//gui->addDrawableRect("diffImage", &diffImg, 200, 150);
		
		//gui->addSlider("Learn Speed", "learnSpeed", 0.5, 0, 1, false);
		//gui->addSlider("Number of Notes", "levels", 5, 5, 30, true);
		//gui->setWhichColumn(1);
		//gui->addCustomRect("Background tint", &bgColorPicker, 200, 150);
		//gui->addCustomRect("note tint", &noteColorPicker, 200, 150);
		//gui->addToggle("Vertical or Horizontal", "vertical", vertical);
	}
	
	void update() {

		//printf("%d %d\n", video->getWidth(), video->getHeight());

		float learnSpeed = 0.5;//gui->getValueF("learnSpeed");
		
		camImg.setFromPixels(video->getPixels(), VISION_WIDTH, VISION_HEIGHT);
		camImg.mirror(true, false);//AppSettings::mirrorCamera);
		greyImg = camImg;
		blendImage = greyImg;
		
		// weighted scale
		cvConvertScale(bgImg.getCvImage(), bgImg.getCvImage(), 1-learnSpeed);
		cvConvertScale(blendImage.getCvImage(), blendImage.getCvImage(), learnSpeed);
		
		// mix two images
		cvAdd(bgImg.getCvImage(), blendImage.getCvImage(), bgImg.getCvImage());
		
		diffImg.absDiff(greyImg, bgImg);

		levels.clear();

		//vertical = gui->getValueB("vertical");
		unsigned char *pixels = diffImg.getPixels();
		for(int i = 0; i < numLevels; i++) {

			ofRectangle rect;
			//if(vertical) {
			//	rect.x = 0;
			//	rect.width = VISION_WIDTH;
			//	rect.height = (float)VISION_HEIGHT/numLevels;
			//	rect.y = rect.height*i;
			//} else {
				rect.y = 0;
				rect.height = VISION_HEIGHT;
				rect.width = (float)VISION_WIDTH/numLevels;
				rect.x = rect.width*i;
			//}
			float value = getAveragePixelValueInRect(pixels, &rect);

			levels.push_back(make_pair(rect, value));
		}
		
		//flow.calc(greyLast, greyImg, 7);
		//flow.blur(5);
	//	greyLast = greyImg;
	
	}
	
		
	//bool getBiggestFlowPoint(ofPoint *pos, ofPoint *vel) {
	//	return flow.getBiggestFlowPoint(pos, vel);
	//}
	
	
	float getAveragePixelValueInRect(unsigned char *pixels, ofRectangle *rect) {
		float total = 0;
		ofRectangle r = *rect;
		 
		for(int x = rect->x; x < rect->x + rect->width; x++) {
			 for(int y = rect->y; y < rect->y + rect->height; y++) {
				 float val = pixels[(int)(x + y*VISION_WIDTH)];
				 val /= 255.f;
				 total += val;
			 }
		 }
		 return total/(rect->width*rect->height);
	}
	
	void draw() {
		//flow.draw(0, 0, ofGetWidth(), ofGetHeight());
		// additive blending
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255, 220);
		camImg.draw(0, 0, ofGetWidth(), ofGetHeight());
		glBlendFunc(GL_ONE, GL_ONE);
		
		ofSetColor(50, 100, 200);//AppSettings::color2.r, AppSettings::color2.g, AppSettings::color2.b);

		diffImg.draw(0, 0, ofGetWidth(), ofGetHeight());
		diffImg.draw(0, 0, ofGetWidth(), ofGetHeight());
		diffImg.draw(0, 0, ofGetWidth(), ofGetHeight());
		
		// reset to normal alpha blending
		ofEnableAlphaBlending();
		
		/*glPushMatrix();
		ofNoFill();
		glScalef((float)ofGetWidth()/VISION_WIDTH, (float)ofGetHeight()/VISION_HEIGHT, 1);
		for(int i = 0; i < levels.size(); i++) {
			
			ofSetColor(255, 255, 255, 150);
			ofRectangle r = levels[i].first;
			r.height *= levels[i].second;
			ofRect(r);
			
	//		ofRect( (float)i*ofGetWidth()/levels.size(), 0, (float)ofGetWidth()/levels.size(), (float)ofGetHeight()*levels[i].second*5.f);
		}
		glPopMatrix();*/
		ofFill();
	}
	int numLevels;
};