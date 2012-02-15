
#pragma once

#include "ofMain.h"


class Sparticles {
	
public: 
    
    void setup();
	void update();
	void draw(bool multicoloured = false);
	void spawn(float x, float y, float dx, float dy);
    
    
	Sparticles();
    ~Sparticles();
	
    
    int maxAge;
	int pos;
	int numParticles;
    
    float density;
    float particleDisplayMode;
    
private:
	
	ofVec2f *positions;
	ofVec2f *velocities;
	float *sizes;
	int *ages;    
	vector<ofImage> images;
    
	
};



