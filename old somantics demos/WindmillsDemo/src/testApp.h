#pragma once

#include "ofMain.h"
#include "ofxMultiTouchPad.h"
#include "Windmill.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	int toWindmillIndex(int x, int y);
	void touchDown(float x, float y, int touchId);
	void touchUp(int touchId);
	void touchMoved(float x, float y, int touchId);
	
	ofxMultiTouchPad touchPad;
	void touchAdded(MTouch &touchId);
	void touchRemoved(int &touchId);
	void touchesUpdated(int &touchCount);
	map<int,ofVec2f> touches;
	vector<Windmill> windmills;
	int windmillsX;
	int windmillsY;
};
