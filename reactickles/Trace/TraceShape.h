//
//  TraceShape.h
//  magic
//
//  Created by Joel Gethin Lewis on 14/06/2011.
//  Copyright 2011 Hellicar&Lewis. All rights reserved.
//

#include "ofMain.h"

#include "MagicShapes.h"

class TraceShape {
public:
	TraceShape(){};
    
    void setup(ofVec2f _pos, int _shapeType){
        pos = _pos;
        radius = ofRandom(80.f, 200.f);
        shapeType = _shapeType;
		
		int colorIndex = Settings::getInstance()->settings["fgColor"];
		if(colorIndex==20) {
			traceColour.setHsb(ofRandom(0.f,255.f), 255, 255);
		} else {
			traceColour.setHex(ColorPicker::colors[colorIndex]);
			traceColour.setBrightness(ofRandom(126, 255));
		}
		
		
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
		ofSetColor(traceColour);
        drawShape(shapeType, pos, radius);
    }
	
	// position in space
	ofVec2f pos;
    float radius;
    int shapeType;
    float birth;
    float age;
    
	ofColor traceColour;
};