//
//  HandPendulum.cpp
//  Somability
//
//  Created by Marek Bereza on 24/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "HandPendulum.h"
#include "Skeletons.h"
#include "constants.h"

void HandPendulum::setup() {
	box2d.init();
	box2d.setGravity(0, 20);
	box2d.createGround();
	box2d.setFPS(30.0);
    
    rightHandAnchor.setup(&box2d, ofColor::red);
    leftHandAnchor.setup(&box2d, ofColor::blue);
}
void HandPendulum::update() {

    //ofPoint mousePosition = ofPoint(ofGetMouseX(),ofGetMouseY());
    //anchor.setPosition(mousePosition);
    
    for(int i = 0; i < Skeletons::getInstance().size(); i++) {
		ofxOpenNIUser &user = Skeletons::getInstance().getUser(i);
		ofxOpenNIJoint rightHand = user.getJoint(JOINT_RIGHT_HAND);
		ofxOpenNIJoint leftHand = user.getJoint(JOINT_LEFT_HAND);        
        
        ofPoint rightHandPosition = rightHand.getProjectivePosition();
        rightHandPosition.x *= (float)WIDTH/colorImg->getWidth();
        rightHandPosition.y *= (float)HEIGHT/colorImg->getHeight();
        rightHandAnchor.update(rightHandPosition);
        
        ofPoint leftHandPosition = leftHand.getProjectivePosition();
        leftHandPosition.x *= (float)WIDTH/colorImg->getWidth();
        leftHandPosition.y *= (float)HEIGHT/colorImg->getHeight();
        leftHandAnchor.update(leftHandPosition);
	}
	
	box2d.update();
}

bool HandPendulum::touchDown(float x, float y, int touchId) {
 
}

void HandPendulum::draw() {
	
	ofSetHexColor(0xFFFFFF);
	glPushMatrix();
	glScalef((float)WIDTH/colorImg->getWidth(), (float)HEIGHT/colorImg->getHeight(), 1);
	colorImg->draw(0, 0);
    
    for(int i = 0; i < Skeletons::getInstance().size(); i++) {
		ofxOpenNIUser &user = Skeletons::getInstance().getUser(i);
		user.drawSkeleton();
	}
	
	glPopMatrix();
    
    rightHandAnchor.draw();
    leftHandAnchor.draw();
    
    string info = "";
    info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    ofSetHexColor(0x444342);
    ofDrawBitmapString(info, 30, 30);
}
