/**
 * Orbit.h
 * magic
 *
 * Named by Marek Bereza on 12/04/2011.
 * Hacked by Joel Gethin Lewis on 12/04/2011.
 *
 */
#pragma once
#include "Reactickle.h"
#include "ReactickleApp.h"



class Orbit: public Reactickle {
public:

    
	void setup();
	
	void update();
	
	void draw();    
    bool touchDown(float x, float y, int touchId);
	
    
    void nextShape();
    
    int getNumModes() {
		return 3;
	}
    

	
private:
	float timeOfLastInteraction;
    int numberOfShapes;
    ofColor shapesColour;
    ofColor bigShapeColour;
    float shapesRadius;
    float bigShapeRadius;
    int maxNumberOfShapes;
    ofVec2f startOfShapes;
    ofVec2f centreOfBigShape;
    
    bool shapeOnScreen;
    float radiansPerShape;
    int currentShapeType;
    
    int maxNumberOfMiddleShapes;
    int maxNumberOfInnerShapes;
    
    int numberOfMiddleShapes;
    int numberOfInnerShapes;
    
    float radiansPerMiddleShape;
    float radiansPerInnerShape;    
    
    ofVec2f startOfMiddleShapes;
    ofVec2f startOfInnerShapes;
};