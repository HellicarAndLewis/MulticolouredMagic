#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

class testApp : public ofBaseApp {

	public:

	int x[255];
	int y[255];
	int aLength;
	
	int x2[255];
	int y2[255];
	int bLength;
	
	int bg();
	int g;
	
	string file;
	
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

};

#endif
