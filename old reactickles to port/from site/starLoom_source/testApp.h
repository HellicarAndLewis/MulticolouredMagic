#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Star.h"

#include "ofxTuio.h"

//--------------------------------------------------------
class testApp : public ofSimpleApp{
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
	
	void objectAdded(ofxTuioObject & tuioObject);
	void objectRemoved(ofxTuioObject & tuioObject);
	void objectUpdated(ofxTuioObject & tuioObject);
	
	vector<Star> pa;

	
	ofPoint p;

	
	bool attracting;

	

};

#endif
