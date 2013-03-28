/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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