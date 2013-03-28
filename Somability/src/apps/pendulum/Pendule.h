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

/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  Pendule.h, created by Marek Bereza on 23/05/2012.
 */


#include "Spring.h"
#include "ofxBox2d.h"

class Pendule {
public:
	ofVec2f target;
	Pendule(float x = 0, float y = 0) {		
		target = ofVec2f(x, y);
	}
	void setup(ofxBox2d *box2d) {
		anchor.setup(box2d->getWorld(), target.x,target.y, 4);
		
		// first we add just a few circles
		for (int i=0; i<10; i++) {
			ofxBox2dCircle circle;
			circle.setPhysics(3.0, 0.53, 0.1);
			circle.setup(box2d->getWorld(), ofGetWidth()/2, 100+(i*20), 8);
			circles.push_back(circle);
		}
		
		// now connect each circle with a joint
		for (int i=0; i<circles.size(); i++) {
			
			ofxBox2dJoint joint;
			
			// if this is the first point connect to the top anchor.
			if(i == 0) {
				joint.setup(box2d->getWorld(), anchor.body, circles[i].body);		
			}
			else {
				joint.setup(box2d->getWorld(), circles[i-1].body, circles[i].body);
			}
			
			joint.setLength(20);
			joints.push_back(joint);
		}
		
		
	}
	void destroy() {
		anchor.destroy();
		
		
		for(int i = 0; i < joints.size(); i++) {
		//	joints[i].destroy();
		}
		for(int i = 0; i < circles.size(); i++) {
			circles[i].destroy();
		}
	}
	
	void setTarget(ofVec2f target) {
		anchor.setPosition(target);
		this->target = target;
	}
	
	ofVec2f getTarget() {
		return this->target;
	}
	
	void draw() {
		ofSetHexColor(0xf2ab01);
		anchor.draw();
		
		
		for(int i=0; i<circles.size(); i++) {
			ofFill();
			ofSetHexColor(0x01b1f2);
			circles[i].draw();
		}
		
		for(int i=0; i<joints.size(); i++) {
			ofSetHexColor(0x444342);
			joints[i].draw();
		}
	}
	
	ofxBox2dCircle					anchor;			  //	fixed anchor
	vector		<ofxBox2dCircle>	circles;		  //	default box2d circles
	vector		<ofxBox2dJoint>		joints;			  //	joints

};