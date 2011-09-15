#pragma once

#include "ofMain.h"
#include "Reactickle.h"
#include "Silhouette.h"
#include "BrushedLine.h"

class Tunnel : public Reactickle {

	public:
		void setup();
		void update();
		void draw();

	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);

	map<int,ofVec2f> touches;
	vector<Silhouette> silhouettes;
	vector<vector<ofVec2f> > history;
	BrushedLine brushedLine;
};
