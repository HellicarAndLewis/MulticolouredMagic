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
 * CircleSwarm.cpp
 * magic
 *
 * Created by Marek Bereza on 12/04/2011.
 *
 */

#include "Follow.h"
#include "constants.h"
#include "ReactickleApp.h"

void Follow::start() {
	currShapeId = 0;
}

void Follow::clap() {
	if(mode>0) {
        if(mode == 1){
            if (currShapeId == MAGIC_CIRCLE){
                currShapeId = MAGIC_CROSS;
            }else{
                currShapeId = MAGIC_CIRCLE;
            }
        }else{
            currShapeId++;
            currShapeId %= NUM_MAGIC_SHAPES;                
        }
        
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        m.setAddress( "/shapechange" );
        m.addIntArg( currShapeId );
        ReactickleApp::instance->sender.sendMessage( m );
#endif
	}
    
	if(mode==1 && numParticles+1<NUM_SWARM_PARTICLES) {
		
		particles[numParticles++].spawn(ofRandomWidth(), ofRandomHeight(), mode, currShapeId);
	}
}



void Follow::update() {

	float timeNow = ofGetElapsedTimef();
	
	float timeSinceLastInteraction = timeNow - timeOfLastInteraction;        
	
	if((volume > volumeThreshold) && (timeSinceLastInteraction > 0.3f )){
		clap(); //simulate a touch in the centre of the screen
		timeOfLastInteraction = timeNow;
	}
	
	// first update particles
	for(int i = 0; i < numParticles; i++) {
		if(particles[i].isAlive()) {
			particles[i].update();
		} else {
			if(touches.size()>0) {
				int ii = ofRandom(0, 100);
				ii %= touches.size();
				int shape = 0;
				if(mode!=0) {
					shape = touches[ii].shapeId;
				}
				particles[i].spawn(touches[ii].x, touches[ii].y, mode, shape);
			} else {
				int shape = 0;
				//if(mode!=0) shape = currShapeId;
				particles[i].spawn(ofRandomWidth(), ofRandomHeight(), mode, shape);
			}
		}
	}

	// then do attractions
	for(int i = 0; i < touches.size(); i++) {
		for(int j = 0; j < numParticles; j++) {
			ofVec2f pos = ofVec2f(touches[i].x, touches[i].y);
			//printf("%f, %f\n", pos.x, pos.y);
			// when we're dealing with touches not from the camera, we
			// need a faster attraction
#ifdef TARGET_OF_IPHONE
			if(mode!=2) {
				particles[j].attract(pos, 1.5);
			} else {
				particles[j].attract(pos);
			}
#else 
			particles[j].attract(pos); // default strength
#endif
		}
	}
	
	
	
	if(mode>0) {
		for(int i = 0; i < NUM_SWARM_PARTICLES; i++) {
			particles[i].shape = currShapeId;
		}
		
	} else {
		for(int i = 0; i < numParticles; i++) {
			particles[i].shape = MAGIC_CIRCLE;
		}
	}
	
	//printf("Touches: %d\n", touches.size());
	
	// then do collisions
	for(int i = 0; i < numParticles; i++) {
		for(int j = i+1; j < numParticles; j++) {
			if(i!=j) {
				collision(particles[j], particles[i]);
			}
		}
	}
}

void Follow::draw() {
	for(int i = 0; i < numParticles; i++) {
		particles[i].draw();
	}

	ofSetColor(100, 100, 100, 40);
	for(int i = 0; i < touches.size(); i++) {
		ofVec2f left = ofVec2f(touches[i].x, touches[i].y);
		ofCircle(left, 10);
	}
}


void Follow::collision(FollowParticle &p1, FollowParticle &p2) {
	float minDistSqr = p1.radius + p2.radius;
	minDistSqr *= minDistSqr;
	float currDistSqr = p2.pos.squareDistance(p1.pos);
	
	// there's a collision
	if(minDistSqr>currDistSqr) {
		// vector from bubble1 to 2
		ofVec2f dist = p2.pos - p1.pos;
		dist.normalize();
		dist *= sqrt(minDistSqr);
		p2.pos = ((p1.pos + dist)*0.1+p2.pos*0.9);
	}
}

bool Follow::touchDown(float x, float y, int touchId) {
	if(currShapeId<0 || currShapeId>=NUM_MAGIC_SHAPES) currShapeId = 0;
	touches.push_back(FollowTouch(x, y, touchId, currShapeId));

    
	return true;
}

bool Follow::touchMoved(float x, float y, int touchId) {
//	printf("x: %f  y: %f  id: %d\n", x, y, touchId);
	for(int i = 0; i < touches.size(); i++) {
		if(touchId==touches[i].touchId) {
			touches[i].x = x;
			touches[i].y = y;
			
			return true;
		}
	}
	return touchDown(x, y, touchId);
}

bool Follow::touchUp(float x, float y, int touchId) {
	for(int i = 0; i < touches.size(); i++) {
		if(touchId==touches[i].touchId) {
			touches.erase(touches.begin()+i);
			return true;
		}
	}
	return true;
}

void Follow::modeChanged() {
	if(mode==0) {
		numParticles = 1;
		particles[0].spawn(WIDTH*0.5, HEIGHT*0.5, mode);
	} else if(mode==1) {
		numParticles = 5;
		for(int i = 0; i < numParticles; i++) {
			particles[i].spawn(ofRandomWidth(), ofRandomHeight(), mode, currShapeId);
		}
	} else if(mode==2) {
		numParticles = NUM_SWARM_PARTICLES;
		for(int i = 0; i < numParticles; i++) {
			particles[i].spawn(ofRandomWidth(), ofRandomHeight(), mode, currShapeId);
		}
		
	}
}