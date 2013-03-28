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

//
//  HandPendulum.h
//  Somability
//
//  Created by Joel Gethin Lewis on 11/06/2012
//

#ifndef Somability_HandPendulum_h
#define Somability_HandPendulum_h

#include "Reactickle.h"
#include "ofxBox2d.h"

class PendulumAnchor{
public:
    void setup(ofxBox2d* _theBox2D, ofColor _theColor){
        theBox2D = _theBox2D;
        theColour = _theColor;
        
        anchor.setup(theBox2D->getWorld(), 20, ofGetHeight()/2, 4);
        
        // first we add just a few circles
        for (int i=0; i<3; i++) {
            ofxBox2dCircle circle;
            circle.setPhysics(3.0, 0.53, 0.1);
            circle.setup(theBox2D->getWorld(), ofGetWidth()/2, 100+(i*20), 8);
            circles.push_back(circle);
        }
        
        // now connect each circle with a joint
        for (int i=0; i<circles.size(); i++) {
            
            ofxBox2dJoint joint;
            
            // if this is the first point connect to the top anchor.
            if(i == 0) {
                joint.setup(theBox2D->getWorld(), anchor.body, circles[i].body);	
            }
            else {
                joint.setup(theBox2D->getWorld(), circles[i-1].body, circles[i].body);
            }
            
            joint.setLength(25);
            joints.push_back(joint);
        }
    }
    
    void update(ofPoint newPosition){
        anchor.setPosition(newPosition);
    }
    
    void addCircle(){
        // add a new circle
        ofxBox2dCircle circle;
        circle.setPhysics(3.0, 0.53, 0.1);
        circle.setup(theBox2D->getWorld(), circles.back().getPosition().x+ofRandom(-30, 30), circles.back().getPosition().y-30, 8);
        circles.push_back(circle);
        
        // get this cirlce and the prev cirlce
        int a = (int)circles.size()-2;
        int b = (int)circles.size()-1;
        
        // now connect the new circle with a joint
        ofxBox2dJoint joint;
        joint.setup(theBox2D->getWorld(), circles[a].body, circles[b].body);
        joint.setLength(25);
        joints.push_back(joint);   
    }
    
    void draw(){
        ofSetColor(theColour);
        anchor.draw();
        
        for(int i=0; i<circles.size(); i++) {
            ofFill();
            circles[i].draw();
        }
        
        for(int i=0; i<joints.size(); i++) {
            joints[i].draw();
        }
    }
    
    //straight from JointExample of ofxBox2D
    
    ofxBox2d*                   theBox2D; //pointer to the world
    ofColor                     theColour;
    ofxBox2dCircle              anchor;	// fixed anchor
    vector	<ofxBox2dCircle>	circles;	// default box2d circles
    vector	<ofxBox2dJoint>     joints;	// joints    
};

class HandPendulum: public Reactickle {
	
public:
	
	
	void setup();
	void update();
	void draw();
	bool touchDown(float x, float y, int touchId);
	
	bool needsKinect() { return true; }
	
	ofxBox2d	box2d;	// the box2d world
    
    PendulumAnchor rightHandAnchor;
    PendulumAnchor leftHandAnchor;
};


#endif
