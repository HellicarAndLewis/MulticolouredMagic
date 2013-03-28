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

/**
 * Expand.cpp
 * magic
 *
 * Created by Joel Gethin Lewis on 13/04/2011.
 *
 */

#include "Expand.h"

#include "constants.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif




void Expand::setup(){
	ofSetCircleResolution(42); //42 is the answer to everything!

	timeOfLastInteraction = ofGetElapsedTimef();

	bigShapeRadius = 400.f;

	centreOfBigShape = ofVec2f(WIDTH/2.f, HEIGHT/2.f);

	currentShapeType = 0;

	drawACircle = false;

	shapeScale = 1.f;

	whiteBg = false;
}

void Expand::update(){
	float timeNow = ofGetElapsedTimef();

	float timeSinceLastInteraction = timeNow - timeOfLastInteraction;
	if((volume > volumeThreshold) && (timeSinceLastInteraction > 0.3f )){
		touchDown(WIDTH/2.f, HEIGHT/2.f, 0); //simulate a touch in the centre of the screen
	}
}

void Expand::draw() {
	int colorIndex = Settings::getInstance()->settings["fgColor"];
	if(colorIndex==20) {
		ofSetColor(ofColor::white);
	} else {
		ofSetHexColor(ColorPicker::colors[colorIndex]);
	}
	ofPushStyle(); //for safety in terms of drawing, and not messing up anyone elses code
	//ofBackground(0); //set to black (0 brightness)
	ofFill();

	switch (mode) {
		case 0:


			if (!drawACircle) {
				drawCross(centreOfBigShape, bigShapeRadius);
				//drawCircle(centreOfBigShape, bigShapeRadius);
			}else{
				drawCircle(centreOfBigShape, bigShapeRadius);
			}
			break;
		case 1:
			drawShape(currentShapeType, centreOfBigShape, bigShapeRadius);
			break;
		case 2:
			if(!whiteBg){// had to flip this because I couldn't get a heart to draw in white(?)

				if(colorIndex==20) {
					ofSetColor(ofColor::white);
				} else {
					ofSetHexColor(ColorPicker::colors[colorIndex]);
				}
				//ofSetColor(ofColor::white);
				ofRect(0, 0, WIDTH, HEIGHT);
				ofSetColor(ofColor::black);
			}else{
				if(colorIndex==20) {
					ofSetColor(ofColor::white);
				} else {
					ofSetHexColor(ColorPicker::colors[colorIndex]);
				}
			}

			//if(currentShapeType==MAGIC_HEART) {
			//	drawShape(MAGIC_CIRCLE, centreOfBigShape, bigShapeRadius*shapeScale);
			//} else {
			drawShape(currentShapeType, centreOfBigShape, bigShapeRadius*shapeScale);
			//}
			break;
		default:
			break;
	}

	ofPopStyle(); //pop back what was there before
}

bool Expand::touchDown(float x, float y, int touchId){


#ifndef TARGET_OF_IPHONE
	ofxOscMessage simpleMessage;
#endif
	switch (mode) {
		case 0:
			drawACircle = !drawACircle;

			timeOfLastInteraction = ofGetElapsedTimef();

			int shapeType;

			if(drawACircle){
				shapeType = 0;
			}else{
				shapeType = 2;
			}
#ifndef TARGET_OF_IPHONE
			simpleMessage.setAddress( "/shapechange" );
			simpleMessage.addIntArg( shapeType );
			ReactickleApp::instance->sender.sendMessage( simpleMessage );
#endif
			break;
		case 1:
			nextShape();

			timeOfLastInteraction = ofGetElapsedTimef();
			break;

		case 2:

		{
			float maxScale = 5;
			// custom sizes for each shape to grow to
			switch(currentShapeType) {
				case MAGIC_CIRCLE: maxScale = 4; break;
				case MAGIC_CROSS: maxScale = 4.5; break;
				case MAGIC_TRIANGLE: maxScale = 7.4; break;
				case MAGIC_HEART: maxScale = 6.0; break;
				case MAGIC_HEXAGON: maxScale = 4.0; break;
				case MAGIC_SQUARE: maxScale = 3.0; break;
			}
			shapeScale += 0.5f;

			// make triangles, hearts and crosses grow faster
			if((currentShapeType==MAGIC_CROSS || currentShapeType==MAGIC_TRIANGLE || currentShapeType==MAGIC_HEART) && shapeScale>2) shapeScale += 0.5;

			if(shapeScale >= maxScale){
				shapeScale = 0.6;
				nextShape();
				whiteBg = !whiteBg;
			}
			timeOfLastInteraction = ofGetElapsedTimef();
			break;
		}
		default:
			break;
	}

	return true;
}

void Expand::nextShape(){
	currentShapeType++;

	if(currentShapeType >= NUM_MAGIC_SHAPES || currentShapeType < 0) { //safety!
		currentShapeType = 0;
	}
#ifndef TARGET_OF_IPHONE
	ofxOscMessage m;
	m.setAddress( "/shapechange" );
	m.addIntArg( currentShapeType );
	ReactickleApp::instance->sender.sendMessage( m );
#endif
}
