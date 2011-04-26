/*
 *  Star.h
 *  openFrameworks
 */

#include "ofMain.h"

class Star {
public:
	Star();
	void setup();
	void reset();
	void update();
	void draw(int red, int green, int blue, int alpha);
	void attract(int fx, int fy);
	
	// position in space
	float x;
	float y;
	
	
	// current velocity
	float dx;
	float dy;
	
	// how big it is
	int radius;
	
	// RGB colour value
	int red;
	int green;
	
	int blue;
	
	
	ofTrueTypeFont font;
	
	
	// this is shared amongst
	// all the Star objects (so
	// we don't have to load
	// the same image for each
	// star object)
	static ofImage image;
	
	
};