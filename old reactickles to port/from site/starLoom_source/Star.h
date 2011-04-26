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

	float x;
	float y;

	float dx;
	float dy;
	
	int radius;
	
	int red;
	int green;
	
	int blue;
	
	
	ofTrueTypeFont font;

	static ofImage image;
	
	
};