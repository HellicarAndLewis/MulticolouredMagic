/**
 *  Trace.cpp
 *
 *  Created by Marek Bereza on 27/10/2011.
 */

#include "Trace.h"
/*
 *  Trace.h
 *
 *
 */

#include "Reactickle.h"
#include "TraceShape.h"

void Trace::start(){
#ifndef TARGET_OF_IPHONE
	ofxOscMessage m;
	int reactickleNumber = 9;
	m.setAddress( "/reacticklechange" );
	m.addIntArg( reactickleNumber );
	ReactickleApp::instance->sender.sendMessage( m );
#endif
}

void Trace::setup() {
	maximumLengthOfTrace = 200; //start with 200, make this interactive?
	positionInTrace = 0;
	
	currShapeID = MAGIC_CIRCLE;
}

void Trace::update() {
	for(int i=0; i < traces.size(); i++){
		traces[i].update();
	}
}

void Trace::draw() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	
	for(int i=0; i < traces.size(); i++){
		traces[i].draw();
	}
}

bool Trace::touchDown(float x, float y, int touchId){
	
	touchMoved(x, y, touchId);
#ifndef TARGET_OF_IPHONE
	ofxOscMessage m;
	m.setAddress( "/touchdown" );
	m.addIntArg(mode);
	ReactickleApp::instance->sender.sendMessage(m);
#endif
	
	return true;
}

bool Trace::touchMoved(float x, float y, int touchId){
	addNewTraceToTraces(x,y); 
	if(mode==2) {
		float dx = x - WIDTH/2;
		float dy = y - HEIGHT/2;
		float dist = sqrt(dx*dx + dy*dy);
		float angle = atan2(dy, dx);
		angle -= PI;
		x = dist*cos(angle) + WIDTH/2;
		y = dist*sin(angle) + HEIGHT/2;
		addNewTraceToTraces(x, y);
	}
	
	return true;
}

bool Trace::touchUp(float x, float y, int touchId){
	return true;
} 

void Trace::addNewTraceToTraces(float x, float y){
	
	if(mode==2) {
		currShapeID = ofGetElapsedTimef();
		currShapeID %= NUM_MAGIC_SHAPES;
	}
	else if(mode == 1){
		currShapeID++;
		currShapeID %= NUM_MAGIC_SHAPES;
		
		/*if (currShapeID == MAGIC_CIRCLE){
		 currShapeID = MAGIC_CROSS;
		 }else{
		 currShapeID = MAGIC_CIRCLE;
		 }*/
		
	}else{
		currShapeID = MAGIC_CIRCLE;
	}    
	
#ifndef TARGET_OF_IPHONE
	ofxOscMessage m;
	m.setAddress( "/shapechange" );
	m.addIntArg( currShapeID );
	ReactickleApp::instance->sender.sendMessage( m );
#endif
	
	
	if(traces.size() < maximumLengthOfTrace){
		//then we want to keep growing the vector....
		TraceShape newShape;
		newShape.setup(ofVec2f(x,y), currShapeID);
		traces.push_back(newShape);
	}else{
		//otherwise, change an "old" trace shape
		traces[positionInTrace].setup(ofVec2f(x,y), currShapeID);
	}
	
	positionInTrace++;
	
	positionInTrace %= maximumLengthOfTrace;
}
