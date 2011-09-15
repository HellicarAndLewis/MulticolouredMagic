#pragma once

#include "ofMain.h"
#include "Reactickle.h"
#include "constants.h"
#include "BrushedLine.h"

class Path {
public:
	bool everHadPoints;
	Path() {
		everHadPoints = false;

	}
	void setDrawingStuff(BrushedLine *brushedLine, ofColor color) {
		this->color = color;
		this->brushedLine = brushedLine;
		
	}
	BrushedLine *brushedLine;
	ofColor color;
	
	vector<ofVec2f> points;
	
	void addPoint(ofVec2f p) {
		if(points.size()>0) {
			points.push_back((p+points.back())/2);
		} else {
			points.push_back(p);
		}
		everHadPoints = true;
	}
	
	bool isAlive() {
		return !(everHadPoints && points.size()==0);
	}
	
	void update(const ofVec2f &offset) {
		for(int i = 0; i < points.size(); i++) {
			points[i] += offset;
			// clear any points that aren't alive anymore
			int BORDER = 20; // we don't want to lose all vertices that are offscreen, or we'll get weird things happening
							 // at the edges, so we'll 
			if(points[i].x<0-BORDER || points[i].y<0-BORDER || points[i].x>WIDTH+BORDER || points[i].y>HEIGHT+BORDER) {
				points.erase(points.begin()+i);
				i--;
			}
			
		}
	
	}
	void draw() {
		ofSetColor(color);
		brushedLine->drawLines(points);
	}
		
};
class Paths : public Reactickle {

	public:
		void setup();
		void update();
		void draw();

	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);

	map<int,ofVec2f> touches;
	vector<Path*> paths;
	map<int, Path*> touchToPath;
	BrushedLine brushedLine;
	ofImage *blob;
};
