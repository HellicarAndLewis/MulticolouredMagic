/*
 *  ExampleApp.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "TTApp.h"

class HighestBlobDetection: public TTApp {
	
	void init(){

		
		learnBackground = true;
		threshold = 80;
		mousePositionX = 0;
		normDistance = 0.0f;
		normDistance2 = 0.0f;
		normDistance3 = 0.0f;
		normTarget = 0.0f;
		
		ofSetCircleResolution(64);
	}
	
	void setup() {

		greyBg.allocate(320, 240);
		greyDifference.allocate(320, 240);
		
		init();
	}
	
	void update() {
		if (learnBackground == true) {
			learnBackground = false;
			
			greyBg = *currentGrey; // breaks the app
			
			cout << "learn the background\n";
		}
		
		//greyDifference.absDiff(greyBg, *grey);
		greyDifference = *currentGrey;
		greyDifference.threshold(threshold, true);
		
		// find any blobs between 20 and 300 pixels
		int minArea = greyDifference.getWidth() * greyDifference.getHeight() * 0.1;
		int maxArea = greyDifference.getWidth() * greyDifference.getHeight() * 0.4;
			//contourFinder.findContours(greyDifference, minArea, maxArea, 10, false);
		contourFinder.findContours(*greyDiff, minArea, maxArea, 10, false);
		
		int highestBlob = 0;
		
		for (int i = 0; i < contourFinder.nBlobs; i++) {
			int h = contourFinder.blobs[i].boundingRect.height;
			
			if (h > highestBlob) {
				highestBlob = h;
			}
		}
		
		if(highestBlob > 0) {
			normTarget = (float)highestBlob / 240;
		}
		
		normDistance += (normTarget - normDistance) / 8;
		normDistance2 += (normTarget - normDistance2) / 16;
		normDistance3 += (normTarget - normDistance3) / 24;
		
		normDistance -= 0.005f;
		if(normDistance < 0) {
			normDistance = 0;
		}
		
		normDistance2 -= 0.005f;
		if(normDistance2 < 0) {
			normDistance2 = 0;
		}
		
		normDistance3 -= 0.005f;
		if(normDistance3 < 0) {
			normDistance3 = 0;
		}
		
		cout << normDistance << "\n";
	}
	
	void draw() {
//		ofSetColor(0xFFFFFF);
//		
//		grey->draw(0,0);
//		greyBg.draw(330, 0);
//		greyDifference.draw(0, 250);
//		
//		contourFinder.draw(0,250);
		
		// set the alpha 0 = 0% (far away) 1 = 100% (large blob);
		ofEnableAlphaBlending();
		ofSetColor(255, 0, 0, 255 * normDistance);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
		ofDisableAlphaBlending();
		
		ofSetColor(255,255,255,255);
		ofEllipse(ofGetWidth() / 2, ofGetHeight() / 2, 400 * normDistance3, 400 * normDistance3);
		
		ofSetColor(255, 0, 0);
		ofEllipse(ofGetWidth() / 2, ofGetHeight() / 2, 300 * normDistance2, 300 * normDistance2);
		
		ofSetColor(255, 255, 255);
		ofEllipse(ofGetWidth() / 2, ofGetHeight() / 2, 200 * normDistance, 200 * normDistance);
	}
	
	void keyPressed(int key) {
		switch (key) {
			case ' ':
				learnBackground = true;
				break;
				
			case '=':
				threshold++;
				if (threshold > 255) threshold = 255;
				break;
				
			case '-':
				threshold--;
				if (threshold < 0) threshold = 0;
				break;

			default:
				break;
		}
	}
	
	void mouseMoved(int x, int y) {
		mousePositionX = x;
	}
	
	
	bool learnBackground;
	int threshold;
	int mousePositionX;
	float normDistance;
	float normDistance2;
	float normDistance3;
	float normTarget;
	
	ofxCvGrayscaleImage greyBg;
	ofxCvGrayscaleImage greyDifference;
	ofxCvContourFinder contourFinder;
};