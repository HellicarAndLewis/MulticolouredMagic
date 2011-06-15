#pragma once

#include "ofMain.h"
#include "Windmill.h"
#include "Reactickle.h"
class Windmills : public Reactickle {

	public:
		void setup();
		void update();
		void draw();

		
	int toWindmillIndex(int x, int y);
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	

	map<int,ofVec2f> touches;
	vector<Windmill> windmills;
	int windmillsX;
	int windmillsY;
};
