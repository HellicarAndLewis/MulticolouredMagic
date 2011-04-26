//
//  MagicShapes.h
//  magic
//
//  Created by Joel Gethin Lewis on 13/04/2011.
//  Copyright 2011 Hellicar&Lewis. All rights reserved.
//
#pragma once
#include "ofMain.h"

enum {
	MAGIC_CIRCLE = 0,
	MAGIC_TRIANGLE,
	MAGIC_CROSS,
	MAGIC_HEART,
	MAGIC_HEXAGON,
	MAGIC_SQUARE,
	NUM_MAGIC_SHAPES
};

void drawTriangle(ofVec2f centre, float size, float rotation = 0);
void drawCircle(ofVec2f centre, float size, float rotation = 0);
void drawCross(ofVec2f centre, float size, float rotation = 0);
void drawHeart(ofVec2f centre, float size, float rotation = 0);
void drawHexagon(ofVec2f centre, float size, float rotation = 0);
void drawSquare(ofVec2f centre, float size, float rotation = 0);

void drawShape(int type, ofVec2f centre, float size, float rotation = 0);