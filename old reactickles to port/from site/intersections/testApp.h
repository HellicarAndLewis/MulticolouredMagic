#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Ball.h"
#include "Timer.h"
#include "Catcher.h"
#include "Score.h"

// Define a constant, no assignment 
// operator or semi-colon required..
#define ARRAYLENGTH 50

class testApp : public ofBaseApp {

	public:
	
	Timer timer;
	Catcher catcher;
	Score score;
	
	Ball ballArray[ARRAYLENGTH];
	
	ofSoundPlayer sound;
	
	ofTrueTypeFont myFont; // Not ofFont (in docs)
	ofTrueTypeFont mySmallFont;
	
	string scoreString;
	
	int count;
	int stringLength;
	
	//int startTime; 
	//int currentTime;
	//int passedTime;
	
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
