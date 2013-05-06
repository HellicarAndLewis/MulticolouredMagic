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


#include "Painter.h"
#include "constants.h"
#include "Settings.h"

#define VISION_WIDTH  320
#define VISION_HEIGHT 240

// increment and wrap the current colour
void Painter::nextColour() {
	colourIndex++;
	if(colourIndex>=NUM_PAINTER_COLOURS) colourIndex = 0;
}
//--------------------------------------------------------------
void Painter::setup(){
	
	// add all the colours to the list
	colourIndex = 0;
	colours[0] = ofColor::fromHex(0x4D1965);
	colours[1] = ofColor::fromHex(0x0E2356);
	colours[2] = ofColor::fromHex(0xFFEC00);
	colours[3] = ofColor::fromHex(0x6D1B00);
	colours[4] = ofColor::fromHex(0xE50043);
	colours[5] = ofColor::fromHex(0x74AF27);	
	colours[6] = ofColor::fromHex(0xED6B06);
	
	scaledImage.allocate(VISION_WIDTH, VISION_HEIGHT);
	grayImage.allocate(VISION_WIDTH, VISION_HEIGHT);
	grayBg.allocate(VISION_WIDTH, VISION_HEIGHT);
	grayDiff.allocate(VISION_WIDTH, VISION_HEIGHT);
	canvas.allocate(VISION_WIDTH, VISION_HEIGHT);
	canvas.set(0);

	// set the vision parameters - we'll need to tweak these
	threshold = 60;
	amount = 0.5;
}

//--------------------------------------------------------------
void Painter::update(){
	
	if(colorImg!=NULL) {
		scaledImage.scaleIntoMe(*colorImg);
#ifdef TARGET_OF_IPHONE	
		grayImage = scaledImage;
#else 
		grayImage.scaleIntoMe(*depthImg);
#endif

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (scaledImage.getWidth()*scaledImage.getHeight())/2, 10, true);	// find holes
		
		
		
		
		// if there are no massive blobs, add the grayDiff to the canvas
		bool updateCanvas = true;
		/*for(int i = 0; i < contourFinder.nBlobs; i++) {
			if(contourFinder.blobs[i].boundingRect.width>colorImg.width/4) updateCanvas = false;
		}*/
		
		
		if(updateCanvas) {
			
			
			// loop through pixels 
			//  - add new colour pixels into canvas
			unsigned char *canvasPixels = canvas.getPixels();
			unsigned char *diffPixels = grayDiff.getPixels();
			int r = colours[colourIndex].r;
			int g = colours[colourIndex].g;
			int b = colours[colourIndex].b;
			int matchCount = 0;
			for(int i = 0; i < canvas.width*canvas.height; i++) {
				if(diffPixels[i]) {
					canvasPixels[i*3] = r;
					canvasPixels[i*3+1] = g;
					canvasPixels[i*3+2] = b;
				}
				if(canvasPixels[i*3]==r && canvasPixels[i*3+1]==g && canvasPixels[i*3+2]==b) {
					matchCount++;
				}
			}
			
			float totalCount = canvas.width*canvas.height;
			float proportionOfMatchedPixels = (float)matchCount/totalCount;
		//	printf("Match count: %f%%\n", proportionOfMatchedPixels*100.f);
			if(proportionOfMatchedPixels>.36) {
				// change colour
				nextColour();
			}
			//canvas += grayDiff;
			canvas.blur();
		}
		
		
		grayBg.convertToRange(0, 255.f*(1.f - amount));
		grayImage.convertToRange(0, 255.f*(amount));
		
		// grayBg = grayBg * 0.9 + grayImage * 0.1
		grayBg += grayImage;
	}

}

//--------------------------------------------------------------
void Painter::draw() {
	ofSetHexColor(0xFFFFFF);
	canvas.draw(0,0,WIDTH, HEIGHT);
	ofEnableAlphaBlending();
	glColor4f(1, 1, 1, 0.2);
	//glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
	scaledImage.draw(0, 0, WIDTH, HEIGHT);
	//ofEnableAlphaBlending();
	//glColor4f(1, 1, 1, 0.75);
	//canvas.draw(0,0,WIDTH, HEIGHT);

}





bool Painter::touchDown(float x, float y, int touchId) {
	return false;
}


bool Painter::touchUp(float x, float y, int touchId) {
	return false;
}

bool Painter::touchMoved(float x, float y, int touchId) {
	return false;
}

