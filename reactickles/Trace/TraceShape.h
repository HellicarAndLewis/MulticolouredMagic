//
//  TraceShape.h
//  magic
//
//  Created by Joel Gethin Lewis on 14/06/2011.
//  Copyright 2011 Hellicar&Lewis. All rights reserved.
//

#include "ofMain.h"
#include "msaColor.h"
#include "MagicShapes.h"

class TraceShape {
public:
	TraceShape(){};
    
    void setup(ofVec2f _pos, int _shapeType){
        pos = _pos;
        radius = ofRandom(80.f, 200.f);
        shapeType = _shapeType;
        traceColour.setHSV(ofRandom(0.f,360.f), 1, 1);
        birth = ofGetElapsedTimef();
        age = 0.f;
    }
    
	void update(){
        age = ofMap(ofGetElapsedTimef() - birth, 0, 5, 1, 0, true);
        traceColour.a = age*255;
        
        if(radius > 1.f){
            radius *= age;
        }
    }
    
	void draw(){
        traceColour.setGL();
        drawShape(shapeType, pos, radius);
    }
	
	// position in space
	ofVec2f pos;
    float radius;
    int shapeType;
    float birth;
    float age;
    
    msaColor traceColour;
};