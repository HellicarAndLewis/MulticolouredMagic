/*
 *  Grid.h
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"

class Grid: public Reactickle {
	
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
		
		if((volume > volumeThreshold) && (timeSinceLastCircle > 0.1f )){			
			positionInGrid++;
			
			if(positionInGrid > numberOfElements){
				positionInGrid = 0;
			}
            
//            if(mode>0) {
//                if(mode == 1){
//                    if (currShapeId == MAGIC_CIRCLE){
//                        currShapeId = MAGIC_CROSS;
//                    }else{
//                        currShapeId = MAGIC_CIRCLE;
//                    }
//                }else{
//                    currShapeId++;
//                    currShapeId %= NUM_MAGIC_SHAPES;                
//                }
//            }else{
//                currShapeId = MAGIC_CIRCLE;
//            }            
            
			
			timeOfLastNewCircle = timeNow;
		}
	}
	
	void draw() {
		
		int shapeId = MAGIC_CIRCLE;
		
		ofSetHexColor(0xFFFFFF);
        
		for(int i=0; i< gridHeight; i++){
			for(int j = 0; j < gridWidth; j++){
                
                if(mode == 0){
                    //not much
                }else if (mode == 1) {
                    if (shapeId == MAGIC_CIRCLE){
                        shapeId = MAGIC_CROSS;
                    }else{
                        shapeId = MAGIC_CIRCLE;
                    }
                }else{
                    shapeId++;
                    shapeId %= NUM_MAGIC_SHAPES;
                }
                
				int positionNow = i*gridWidth + j;
				
				int topLeftX = j*gridElementWidth;
				int topLeftY = i*gridElementHeight;
				
				int centreX = topLeftX + gridElementWidth/2;
				int centreY = topLeftY + gridElementHeight/2;
				
				if(positionNow < positionInGrid){
                    drawShape(shapeId, ofVec2f(centreX, centreY), gridElementWidth*1.5/2.f);
				}else{
					// draw a square
					float border = 10.f;
                    
					ofRect(topLeftX+border/2.f, topLeftY+border/2.f, gridElementWidth-border, gridElementHeight-border);
				}
			}
		}
	}
    
    int getNumModes() {
		return 3;
	}
	
	int gridWidth;
	int gridHeight;
	int positionInGrid;
	int gridElementWidth;
	int gridElementHeight;
	float timeOfLastNewCircle;
};