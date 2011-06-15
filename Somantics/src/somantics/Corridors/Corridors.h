#pragma once

#include "ofMain.h"
#include "Corridor.h"
#include "Reactickle.h"

class Corridors : public Reactickle {

public:
	void setup();
	void update();
	void draw();
	const static int NUM_COLORS = 4;
	ofColor colors[NUM_COLORS];	
	bool touchDown(float x, float y, int touchId);
	bool touchUp(int touchId);
	bool touchMoved(float x, float y, int touchId);
	
	map<int,ofVec2f> touches;
	vector<Corridor> corridors;
};
