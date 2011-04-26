/*
 *  ExampleApp.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"

class GridOfSquaresApp: public Reactickle {
	
	void setup(){
		gridWidth = 6;
		gridHeight = 4;
		positionInGrid = 0;
		
		gridElementWidth = ofGetWidth()/gridWidth;
		gridElementHeight = ofGetHeight()/gridHeight;	
		
		timeOfLastNewCircle = ofGetElapsedTimef();
	}
	
	void update(){
		float timeNow = ofGetElapsedTimef();
		
		float timeSinceLastCircle = timeNow - timeOfLastNewCircle;
		
		int numberOfElements = gridWidth*gridHeight;
		
		if((volume > 0.9f) && (timeSinceLastCircle > 0.1f )){
			
//			if(++positionInGrid == gridWidth*gridHeight){
//				positionInGrid = 0;
//			}
			
			positionInGrid++;
			
			if(positionInGrid > numberOfElements){
				positionInGrid = 0;
			}
			
			timeOfLastNewCircle = timeNow;
		}
	}
	
	void draw() {
		
		int shapeId = MAGIC_CIRCLE;
		
		ofSetHexColor(0xFFFFFF);
		for(int i=0; i< gridHeight; i++){
			for(int j = 0; j < gridWidth; j++){
				shapeId++;
				shapeId %= NUM_MAGIC_SHAPES;
				int positionNow = i*gridWidth + j;
				
				int topLeftX = j*gridElementWidth;
				int topLeftY = i*gridElementHeight;
				
				int centreX = topLeftX + gridElementWidth/2;
				int centreY = topLeftY + gridElementHeight/2;
				
				if(positionNow < positionInGrid){
					// draw a circle
					if(mode!=0) ofSetHexColor(0xFF0000);
					if(mode!=2) ofCircle(centreX, centreY, gridElementWidth/2);
					else drawShape(shapeId, ofVec2f(centreX, centreY), gridElementWidth*1.5/2.f);
				}else{
					// draw a square
					float border = 10.f;
					
					if(mode!=0) ofSetHexColor(0x1100dd);
					ofRect(topLeftX+border/2.f, topLeftY+border/2.f, gridElementWidth-border, gridElementHeight-border);
				}
			}
		}
	}
	
	int gridWidth;
	int gridHeight;
	int positionInGrid;
	int gridElementWidth;
	int gridElementHeight;
	float timeOfLastNewCircle;
};