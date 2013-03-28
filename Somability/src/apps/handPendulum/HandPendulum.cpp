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
