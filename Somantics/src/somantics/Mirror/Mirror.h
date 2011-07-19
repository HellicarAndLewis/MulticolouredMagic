//
//  Mirror.h
//  SomanticsMac
//
//  Created by Marek Bereza on 11/07/2011.
//  Copyright 2011 MAZBOX LTD. All rights reserved.
//
#include "Reactickle.h"
#define MIRROR_AMBIENT_LAPSE	0
#define MIRROR_SLITSCAN			1
#define MIRROR_KALEIDOSCOPE		2

class Mirror: public Reactickle {
public:
	
	Mirror(int type);
	~Mirror();
	
	void setup();
	void update();
	void draw();

	
	bool touchDown(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	
	bool needsKinect() { return true; }
	
	
private:
	int ratio(int l, int r, float ratio);
	int type;
	
	
	// stuff specifically for MIRROR_KALEIDOSCOPE
	float offset;
	int star;
	
	unsigned char *buffer;
	ofxCvColorImage image;
	
	// stuff specifically for MIRROR_SLITSCAN
	int slitScanPos;
};