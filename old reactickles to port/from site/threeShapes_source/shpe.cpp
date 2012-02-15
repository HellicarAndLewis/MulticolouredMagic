/*
 *  shpe.cpp
 *  emptyExample
 *
 *  Created by Joseph Scully on 27/02/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "shpe.h"


void shpe::setup(int sizE){
	drawState = 0;

	sizeE = sizE;
	ofSetCircleResolution(60);
}

void shpe::reset(){
	
	
}

void shpe::update(int x, int y){
	if(x<ofGetWidth()/3){
			drawState = 0;
	}
	
	if(x>ofGetWidth()/3){
			drawState = 1;	
	}
	
	if(x>(ofGetWidth()/3)*2){
			drawState = 2;	
	}
	
}

void shpe::draw(int x, int y){
	ofPushStyle();
	ofSetLineWidth(5);
	ofSetColor(255, 255, 255);
	
	ofTranslate(x, y, 0);
	if(drawState==0){
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRect(0, 0, sizeE, sizeE);
	}
	
	if(drawState==1){
		ofEllipse(0, 0, sizeE, sizeE);
	}
	
	
	if(drawState==2){
		
		ofTriangle(-sizeE/2, sizeE/2, 0, -sizeE/2, sizeE/2, sizeE/2);
	}
	ofPopStyle();
	
	
	
	ofPushStyle();
	ofNoFill();
	ofSetLineWidth(5);
	ofSetColor(0, 0, 0);
	
	
	if(drawState==0){
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofRect(0, 0, sizeE, sizeE);
	}
	
	if(drawState==1){
		ofEllipse(0, 0, sizeE, sizeE);
	}
	
	
	if(drawState==2){
		
		ofTriangle(-sizeE/2, sizeE/2, 0, -sizeE/2, sizeE/2, sizeE/2);
	}
	ofPopStyle();

}


int shpe::getState(){
	return drawState;
}
	
	

