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
