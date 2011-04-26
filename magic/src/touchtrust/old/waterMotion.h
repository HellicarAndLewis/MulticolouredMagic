/*
 *  water.h
 *  waterMotion
 *
 *  Created by Will Pearson on 05/07/2010.
 *  Copyright 2010 Sacculi >>. All rights reserved.
 *
 */

#pragma once

#define DWIDTH 64
#define DHEIGHT 32

#include "ofMain.h"
#include "TTApp.h"

class Water{
public:

		float x;
		float y;
		float angle;
		float speed;

		bool turnLeft;
		bool turnRight;
		bool accel;
		
		float turnSpeed;
	
	Water(){
		turnLeft = false;
		turnRight = false;
		accel = false;
		
		turnSpeed = 0.1;
		
	}
		


	//----------------------------------------------
	void update() {
		angle += 
		(turnLeft ? -turnSpeed : 0.0) +
		(turnRight ? turnSpeed : 0.0);
		
		x += cos(angle) * speed;
		y += sin(angle) * speed;
		
		speed = ofClamp(speed+0.1, 0.0, 3.0);
	}

	//----------------------------------------------
	void draw() {
		float sine = sin(angle);
		float cosine = cos(angle); 
		ofSetColor(255, 20, 20);
		
		ofFill();
		ofSetColor(180,10,10);
		ofBeginShape();
		ofVertex(x,    y+30*sine);
		ofVertex(x-30*cosine,  y);
		ofVertex(x,    y-100*sine);
		ofVertex(x+30*cosine,  y);
		ofEndShape(true);
	}
};

class WaterMotionApp : public TTApp {
	public:
	
	int vidWidth;
	int vidHeight;
	
	//all the openCV stuff for loading in video
	
	
	ofVideoGrabber 		vidGrabber;
	
	ofxCvColorImage			colorImage;
	ofImage					colorImage_ofImage;
	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBackgroundImage;
	ofxCvGrayscaleImage 	grayDiffImage;
	
	ofxCvContourFinder 	contourFinder;
	
	
	
	int 				threshold;
	bool				bLearnBackground;
	int					camVidWidth;
	int					camVidHeight;
	
	float				heightSUMer;
	
	
	
	
	int					lastMx, lastMy;
	
	ofTrueTypeFont		verdana;
	
	ofPoint				influence;
	
	
	int					pixelFactor;
	int					margin;
	
	float				level [DWIDTH][DHEIGHT];
	float				dLevel [DWIDTH][DHEIGHT];
	
	bool drawStroke;
	bool drawFill;
	bool pushUp;
	bool sizeMod;
	bool highDrag;
	
	bool mouseIsDown;
	
	bool showFps;
	
	
	float	redValue;
	float	greenValue;
	float	blueValue;
	float	alphaValue;	
										
	Water water1;
	
		//----------------------------------------------
	void init(){
		
		ofFill();
	}
		
		//----------------------------------------------
		void setup(){
			
			influence.x = mouseX;
			influence.y = mouseY;
			
			ofSetVerticalSync(true);
			
			heightSUMer = 0;
			
			lastMx = -1;
			lastMy = -1;
			pixelFactor = DWIDTH;
			margin = 4;
			
			redValue = 255;
			greenValue = 255;
			blueValue = 255;
			
			drawStroke = true;
			drawFill = true;
			pushUp = true;
			sizeMod = false;
			highDrag = false;
			//size(int(screen.width*0.75), int(screen.height*0.75));
			
			//All the openCV stuff here...
			
			camVidWidth = 320;
			camVidHeight = 240;
			
			vidGrabber.setVerbose(true);
			vidGrabber.setDeviceID(2);
			vidGrabber.initGrabber(camVidWidth,camVidHeight);
			
			colorImage.allocate(camVidWidth,camVidHeight);
			grayImage.allocate(camVidWidth,camVidHeight);
			grayBackgroundImage.allocate(camVidWidth,camVidHeight);
			grayDiffImage.allocate(camVidWidth,camVidHeight);
			
			bLearnBackground = true;
			threshold = 10;

			gui->addTitle("Water Settings");
			gui->addSlider("Red Tile Value", redValue, 0.0, 255.0);
			gui->addSlider("Green Tile Value", greenValue, 0.0, 255.0);
			gui->addSlider("Blue Tile Value", blueValue, 0.0, 255.0);
			gui->addSlider("Alpha for Tiles", alphaValue, 0.0, 255.0);
			
			
			gui->loadFromXML();
			
			
			//ofBackground(0,0,0);
			ofSetFrameRate(30);
			
			for(int x=0; x<DWIDTH; x++) {
				for(int y=0; y<DHEIGHT; y++) {
					level[x][y] = 0.0;
				}
			}
			
			for(int x=0; x<DWIDTH; x++) {
				for(int y=0; y<DHEIGHT; y++) {
					dLevel[x][y] = 0.0;
				}
			}
			
			//setHelp();
		}
		
		//----------------------------------------------
		void update(){
			
				
				grayImage = *cam;
				if (bLearnBackground == true){
					grayBackgroundImage = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
					bLearnBackground = false;
				}
				
				// take the abs value of the difference between background and incoming and then threshold:
				grayDiffImage.absDiff(grayBackgroundImage, grayImage);
				grayDiffImage.threshold(threshold);
				
				// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
				// also, find holes is set to true so we will get interior contours as well....
				contourFinder.findContours(grayDiffImage, 20, (340*240)/3, 10, true);	// find holes
			}

		//----------------------------------------------
		
		void draw(){
			
			vidWidth = ofGetWidth();
			vidHeight = ofGetHeight();
			
			ofEnableAlphaBlending();
			
			mouseImpulse();
			
			
			updateLake();
			
			
			lastMx = -1;
			lastMy = -1;
			
			
			water1.update();
			
			ofSetColor(0, 0, 0);
			ofFill();
			ofRect(0,0,ofGetWidth(), ofGetHeight());
			
			float contrast = 6.0;
			
			//noStroke();
			ofNoFill();
			
			int rectSize = pixelFactor - margin - margin;
			float currentLevel;
			float currentLevelX;
			float ratio;
			
			int x;
			for(int x2=0; x2<DWIDTH; x2++) {
				if (x2 < DWIDTH/2) {
					x = x2;
				} 
				else {
					x = DWIDTH - ( x2 - (DWIDTH/2) ) -1;
				}
				for(int y=0; y<DHEIGHT; y++) {
					currentLevel = level[x][y];
					currentLevelX = currentLevel*contrast;
					
					bool pinkYellow = false;
					if (drawStroke){
						if (pinkYellow) {
							ofSetColor(redValue + 198.0 + 232.0, greenValue + 98.0 + 204.0, blueValue + 197.0 + 126.0, alphaValue);
						} 
						else {
							ofSetColor(currentLevelX*10.0 + 10.0, currentLevelX*20.0 + 20.0, max(64.0, currentLevelX*20.0 + 64.0), alphaValue);
						}
					}
					if (drawFill) {
						ofFill();
						ofSetColor(redValue + currentLevelX*5.0 + 10.0, greenValue + currentLevelX*10.0 + 20.0, blueValue + currentLevelX*10.0 + 64.0, alphaValue);
					}
					
					ratio = float(x) / float(DWIDTH-1);
					ratio = ratio * 2.0 - 1.0;
					
					
					
					ofRect(
						   x*pixelFactor + int(currentLevel*50.0)*ratio, 
						   y*pixelFactor - int(currentLevel*22.0),
						   rectSize*(sizeMod?currentLevel:1), rectSize*(sizeMod?currentLevel:1));
					
					
					
					//ofSetColor(255, 0, 0);
					
				}

				ofPushStyle();
				ofSetColor(255, 255, 255);
				
				ofPopStyle();
				
				
				ofNoFill();
				
				//attempt to make the contours affect the tiles
				
				for(int i = 0; i < contourFinder.blobs.size(); i++) {
					
					ofRectangle cur = contourFinder.blobs[i].boundingRect;
					ofSetColor(255, 255, 255);
					
					ofRect(cur.x, cur.y, cur.width, cur.height);
					
					
				}
				
			}
			
			bool showHelp = true;
			bool showFps = false;
			
		}
		
		//--------------------------------------------------------------
		void keyPressed  (int key){
			
			switch(key) {
					
				case 'h': 
					
					gui->hide();
					
					break;
					
				case 's': 				
					
					gui->show();
					
					break;
					
					
				case '1':
					highDrag = !highDrag;
					
					break;
				case '2':
					sizeMod = !sizeMod;
					break;
				case '3':
					drawStroke = !drawStroke;
					break;
				case '4':
					drawFill = !drawFill;
					break;
					
					
				case 'f':
					showFps = !showFps;
					break;
					
				case 'a':
					water1.turnLeft = true;
					break;
				case 'd':
					water1.turnRight = true;
					break;
				case 'w':
					water1.accel = true;
					break;
					
				case ' ':
					bLearnBackground = true;
					break;
				case '+':
					threshold ++;
					if (threshold > 255) threshold = 255;
					break;
				case '-':
					threshold --;
					if (threshold < 0) threshold = 0;
					break;
			}
			
			
			if (key == 16) {
				// left shift
				pushUp = false;
			}
			
			
		}
		
		//--------------------------------------------------------------
		void keyReleased(int key){
			if (key == 16) {
				// left shift
				pushUp = true;
			}
			switch (key) {
				case 'a':
					water1.turnLeft = false;
					break;
				case 'd':
					water1.turnRight = false;
					break;
				case 'w':
					water1.accel = false;
					break;
			}
		}
		
		//--------------------------------------------------------------
		void mousePressed(int x, int y, int button){
			
						
			
		}
		
		//--------------------------------------------------------------
		void mouseReleased(int x, int y, int button){
			
			
			
		}
		
		//--------------------------------------------------------------
		void resized(int w, int h){
			
		}
		
		//--------------------------------------------------------------
		
		
		
		
		
		//--------------------------------------------------------------
		
		void updateLake() {
			
			float avgLevel = 0.0;
			float diff = 0.0;
			
			for(int x=1; x<DWIDTH-1; x++) {
				for(int y=1; y<DHEIGHT-1; y++) {
					
					// calc average surrounding level 
					avgLevel = 
					0.7*level[x-1][y-1] +
					level[x][y-1] + 
					0.7*level[x+1][y-1] +
					
					level[x+1][y] + 
					
					0.7*level[x+1][y+1] +
					level[x][y+1] +
					0.7*level[x-1][y+1] +
					
					level[x-1][y];
					
					avgLevel /= 6.8;
					
					// calc difference for this pixel to avg surrounding level
					diff = avgLevel - level[x][y];
					
					// accelerate level speed by difference (pull toward average)
					dLevel[x][y] += diff*0.07;
					
					// drag, so it evens out
					dLevel[x][y] *= highDrag ? 0.99 : 0.997;
					
				}
			}
			
			for(int x=1; x<DWIDTH-1; x++) {
				for(int y=1; y<DHEIGHT-1; y++) {
					// apply level speed to levels
					level[x][y] += dLevel[x][y];
				}
			}
			
			
			
						
		}
		
		//--------------------------------------------------------------
		
		
		
		void mouseImpulse() {
			
			for(int i = 0; i < contourFinder.blobs.size(); i++) {
				
				ofRectangle cur = contourFinder.blobs[i].boundingRect;
				ofSetColor(255, 255, 255);
				
				//test draw the rectangles made with contour finder
				ofRect(cur.x, cur.y, cur.width, cur.height);
				
				influence.x = cur.x;
				influence.y = cur.y;
				
			}
			
			int mx = (influence.x*0.5)/pixelFactor;
			int my = (influence.y*0.5)/pixelFactor;
			
			
			
			mx = ofClamp(mx, 1, DWIDTH-3);
			my = ofClamp(my, 1, DHEIGHT-3);
			
			
			
			float amt = 0.05;
			if (!pushUp) {
				amt *= -1.0;
			}
			
			if (lastMx == -1) {
				//println("dot at " + mx + "," + my);
				dLevel[mx][my] += amt;
				dLevel[mx+1][my] += amt;
				dLevel[mx][my+1] += amt;
				dLevel[mx+1][my+1] += amt;
			} 
			else {
				
				lastMx = ofClamp(lastMx, 1, DWIDTH-3);
				lastMy = ofClamp(lastMy, 1, DHEIGHT-3);
				
				int distToLast = int(ofDist(mx, my, lastMx, lastMy) );
				//println("Line from " + lastMx + "," + lastMy  + " to " + mx + ", " + my + ": " + distToLast);
				for (int i=0; i<=distToLast; i++) {
					float ratio = float(i)/float(distToLast);
					if (distToLast == 0) {
						ratio = 0.0;
					}
					
					int x = int(ratio*lastMx + (1-ratio)*mx);
					int y = int(ratio*lastMy + (1-ratio)*my);
					//println(x + " ," + y + " ratio " + ratio);
					
					distToLast = max(1, distToLast);
					/*amt /= float(distToLast);*/
					
					//            level[x][y] = amt;
					//            level[x+1][y] = amt;
					//            level[x][y+1] = amt;
					//            level[x+1][y+1] = amt;
					
					dLevel[x][y] += amt;
					dLevel[x+1][y] += amt;
					dLevel[x][y+1] += amt;
					dLevel[x+1][y+1] += amt;
				}
				
			}
			
			
			lastMx = mx;
			lastMy = my;
			
		}
	};
		
