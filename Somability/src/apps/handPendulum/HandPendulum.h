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
