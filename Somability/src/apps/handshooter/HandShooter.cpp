/**
 *  HandShooter.cpp
 *
 *  Created by Marek Bereza on 11/06/2012.
 */

#include "HandShooter.h"
#include "Skeletons.h"
#include "constants.h"

void HandShooter::setup() {
	
}
void HandShooter::update() {
	for(int i = 0; i < Skeletons::getInstance().size(); i++) {
		ofxOpenNIUser &user = Skeletons::getInstance().getUser(i);
		
		// find out if there's a collision
		
		ofxOpenNIJoint &lHand = user.getJoint(JOINT_LEFT_HAND);
		ofxOpenNIJoint &lArm = user.getJoint(JOINT_LEFT_ELBOW);
		
		ofxOpenNIJoint &rHand = user.getJoint(JOINT_RIGHT_HAND);
		ofxOpenNIJoint &rArm = user.getJoint(JOINT_RIGHT_ELBOW);
		
		
		// LEFT ARM 
		ofPoint st = lHand.getProjectivePosition();
		ofVec2f start(st.x, st.y);
	
		ofPoint d = lArm.getProjectivePosition();
		ofVec2f dir(st.x - d.x, st.y - d.y);
		dir.normalize();
		emitParticle(start, dir);
		
		
		// RIGHT ARM
		st = rHand.getProjectivePosition();
		start.set(st.x, st.y);
		d = rArm.getProjectivePosition();
		dir.set(st.x - d.x, st.y - d.y);
		dir.normalize();
		emitParticle(start, dir);

	}
	
	while(particles.size()>500) {
		particles.pop_front();
	}
	
	for(int i = 0; i < particles.size(); i++) {
		particles[i].update();
	}
}
void HandShooter::emitParticle(ofVec2f pos, ofVec2f dir) {
	//if(ofRandom(0,1)>0.5) return; // don't do every single one
	particles.push_back(HandParticle());
	particles.back().setup(pos, dir);
	
	particles.push_back(HandParticle());
	dir += ofVec2f(ofRandom(-0.05,0.05), ofRandom(-0.05,0.05));
	particles.back().setup(pos+dir+dir, dir);
}

void HandShooter::draw() {
	glPushMatrix();
	ofSetHexColor(0xFFFFFF);
	
	glScalef((float)WIDTH/640.f, (float)HEIGHT/480.f, 1);
	colorImg->draw(0,0,640, 480);
	for(int i = 0; i < Skeletons::getInstance().size(); i++) {
		ofxOpenNIUser &user = Skeletons::getInstance().getUser(i);
	//	user.drawSkeleton();
	}
	glLineWidth(5);
	//	printf("%d skelingtons\n", Skeletons::getInstance().size());
	for(int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
	glLineWidth(1);
	
	glPopMatrix();
	
	
}
