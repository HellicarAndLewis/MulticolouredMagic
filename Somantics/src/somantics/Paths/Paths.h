#pragma once

#include "ofMain.h"
#include "Reactickle.h"
class Paths : public Reactickle {

	public:
		void setup();
		void update();
		void draw();

	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);

	map<int,ofVec2f> touches;

};
