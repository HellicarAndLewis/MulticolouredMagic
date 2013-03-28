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
 * Follow.h
 * magic
 *
 * Created by Marek Bereza on 12/04/2011.
 *
 */
#include "Reactickle.h"
#include "FollowParticle.h"
#define NUM_SWARM_PARTICLES 150
class FollowTouch: public ofVec2f {
public:
	int touchId;
	int shapeId;
	FollowTouch(float x, float y, int touchId, int shapeId) {
		this->shapeId = shapeId;
		this->touchId = touchId;
		this->x = x;
		this->y = y;
	}
};
class Follow: public Reactickle {
public:
	
	bool needsKinect() { return true; }
	void update();
	void draw();
	void start();
	
	void clap();
	void modeChanged();
	virtual bool touchDown(float x, float y, int touchId);
	virtual bool touchMoved(float x, float y, int touchId);
	virtual bool touchUp(float x, float y, int touchId);
	void collision(FollowParticle &p1, FollowParticle &p2);
    
    int getNumModes() {
		return 3;
	}
private:
	
	float timeOfLastInteraction;
	vector<FollowTouch> touches;
	FollowParticle particles[NUM_SWARM_PARTICLES];
	int numParticles;
	int currShapeId;
};