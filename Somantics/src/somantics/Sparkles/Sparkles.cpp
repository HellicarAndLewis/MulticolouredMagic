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

//
//  Sparkles.cpp
//  SomanticsMac
//
//  Created by Marek Bereza on 11/07/2011.
//  Copyright 2011 MAZBOX LTD. All rights reserved.
//

#include "Sparkles.h"
#include "constants.h"
#include "Settings.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif


//#define VISION_WIDTH 320
//#define VISION_HEIGHT 480
//--------------------------------------------------------------
void Sparkles::setup(){

	p.setup();



	// initialize all the cv images
	scaledImage.allocate(VISION_WIDTH, VISION_HEIGHT);
	grayImage.allocate(VISION_WIDTH, VISION_HEIGHT);
	grayBg.allocate(VISION_WIDTH, VISION_HEIGHT);
	grayDiff.allocate(VISION_WIDTH, VISION_HEIGHT);
	threshold = 40;
	amount = 0.3;

}

//--------------------------------------------------------------
void Sparkles::update(){

	//  printf("New frjjame!!\n");
	if (colorImg!=NULL) {

		scaledImage.scaleIntoMe(*colorImg);

        grayImage = scaledImage;


		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (VISION_WIDTH*VISION_HEIGHT)/3, 10, true);	// find holes


		// now just stick some particles on the contour and emit them randomly
		for(int i = 0; i < contourFinder.nBlobs; i++) {
			int step = 10;//contourFinder.blobs[i].pts.size()/10;
			for(int j = 0; j < contourFinder.blobs[i].pts.size(); j+=step) {
				p.spawn(
						contourFinder.blobs[i].pts[j].x*WIDTH/VISION_WIDTH,
						contourFinder.blobs[i].pts[j].y*HEIGHT/VISION_HEIGHT,
						ofRandom(-5, 5), ofRandom(-5, 5));
			}
		}




		grayBg.convertToRange(0, 255.f*(1.f - amount));
		grayImage.convertToRange(0, 255.f*(amount));

		// grayBg = grayBg * 0.9 + grayImage * 0.1
		grayBg += grayImage;
	}
	 p.update();

}

//--------------------------------------------------------------
void Sparkles::draw() {
	ofBackground(0,0,0);
	ofEnableAlphaBlending();
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetColor(255, 255, 255, 200);

	//draw video feed here
	//colorImg.draw(0, 0, ofGetWidth(), ofGetHeight());
	grayBg.draw(0, 0, WIDTH, HEIGHT);

	//glPushMatrix();
	//glScalef((float)WIDTH/(float)colorImg.width, (float)HEIGHT/(float)colorImg.height, 0);

	int colorIndex = Settings::getInstance()->settings["fgColor"];

	if(colorIndex==20) {
		p.draw(true);
	} else {
		ofSetHexColor(ColorPicker::colors[colorIndex]);
		p.draw();
	}
	//glPopMatrix();
//	ofSetColor(0, 150,255);
	//ofDrawBitmapString(ofToString(ofGetFrameRate(), 2), 50, 20);

	ofEnableAlphaBlending();
}





bool Sparkles::touchDown(float x, float y, int touchId) {
	return false;
}


bool Sparkles::touchUp(float x, float y, int touchId) {
	return false;
}

bool Sparkles::touchMoved(float x, float y, int touchId) {
	return false;
}

