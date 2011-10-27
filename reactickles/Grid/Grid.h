/*
 *  Grid.h
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"

class Grid: public Reactickle {
    

	void setup();
	bool touchDown(float x, float y, int id);
	void update();
	
	void draw();
    
    int getNumModes() {
		return 3;
	}
    
 
private:
	int gridWidth;
	int gridHeight;
	int positionInGrid;
	int gridElementWidth;
	int gridElementHeight;
	float timeOfLastNewCircle;
};