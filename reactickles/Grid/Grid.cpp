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
 *  Grid.cpp
 *
 *  Created by Marek Bereza on 27/10/2011.
 */

#include "Grid.h"
#include "constants.h"
#include "Settings.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif


void Grid::setup(){
	gridWidth = 6;
	gridHeight = 4;
	positionInGrid = 0;

	gridElementWidth = WIDTH/gridWidth;
	gridElementHeight = HEIGHT/gridHeight;

	timeOfLastNewCircle = ofGetElapsedTimef();
}

bool Grid::touchDown(float x, float y, int id) {
	positionInGrid++;
	if(positionInGrid > gridWidth*gridHeight){
		positionInGrid = 0;
	}


	return true;
}
void Grid::update(){
	float timeNow = ofGetElapsedTimef();

	float timeSinceLastCircle = timeNow - timeOfLastNewCircle;

	int numberOfElements = gridWidth*gridHeight;

	if((volume > volumeThreshold) && (timeSinceLastCircle > 0.1f )){
		positionInGrid++;

		if(positionInGrid > numberOfElements){
			positionInGrid = 0;
		}
		timeOfLastNewCircle = timeNow;
	}
}

void Grid::draw() {

	int shapeId = MAGIC_CIRCLE;
	int colorIndex = Settings::getInstance()->settings["fgColor"];
	if(colorIndex==20) {
		ofSetHexColor(0xFFFFFF);
	} else {
		ofSetHexColor(ColorPicker::colors[colorIndex]);
	}


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
