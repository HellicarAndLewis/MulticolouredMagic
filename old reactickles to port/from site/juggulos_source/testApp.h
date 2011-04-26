#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Ball.h"
#include "Rectangle.h"
#include "ofxSimpleGuiToo.h"
#include "ofxShader.h" 
#include "ofxFBOTexture.h"
#include "shaderZoom.h"


#define numBalls 4


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
		void resized(int w, int h);
	
	void drawConnectors();
	
	void checkCollision();
	
	void extraRings();

	
	ofxVec3f wind;
	ofxVec3f gravity;
	ofxVec3f tempforce;
	
	float vibration;
	
	Ball b1;
	Ball b2;
	Ball b3;
	Ball b4;
	
	rectangle r1;
	rectangle r2;
	rectangle r3;
	rectangle r4;
	
	
	float x;
	float y;
	
	int colorA;
	int colorB;
	int colorC;
	
	int _colorA;
	int _colorB;
	int _colorC;
	
	int screenW;
	int screenH;
	
	
	shaderZoom zoom;
	

	
	rectangle* rectangles[4];
	
	Ball* balls[4];

	//bool	randomizeButton = true;
	
	ofPoint *points;
	
	ofPoint	v[300];
	
	

};

#endif
