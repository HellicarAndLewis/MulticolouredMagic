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
 * Flip.h
 * magic
 *
 * Created by Marek Bereza on 13/04/2011.
 *
 */
#include "Reactickle.h"

class FlipTouch: public ofVec2f {
public:
	FlipTouch(float x, float y, int touchId) {
		this->x = x;
		this->y = y;
		this->touchId = touchId;
	}
	int touchId;
};

class Flip: public Reactickle {
public:
	
	bool needsKinect() { return true; }
    
    virtual void start();
	virtual void update();
	virtual void draw();
	virtual bool touchDown(float x, float y, int touchId);
	virtual bool touchMoved(float x, float y, int touchId);
	virtual bool touchUp(float x, float y, int touchId);
    virtual void modeChanged();
    
    int getNumModes() {
		return 3;
	}
    
	vector<FlipTouch> touches;

	// this really should be just an ofVec2f rather than a 
	// deque of them. It was originally needed as a trail.
	// haven't got time to change that right now.
	deque<ofVec2f> pos;
	int currShapeId;
	ofVec2f lastPos;
};