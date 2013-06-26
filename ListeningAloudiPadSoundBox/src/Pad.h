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
 *  Pad.h, created by Marek Bereza on 12/12/2012.
 */


#pragma once
#include "ofMain.h"
#include "MiniSampler.h"
#include <map>
#define TRIGGER_TOGGLE 1
#define TRIGGER_MOMENTARY 0

class Pad {
public:
	
	
	struct Touch {
		ofVec2f pos;
		
		int id;
		Touch(int id = 0, ofVec2f pos = ofVec2f()) {
			this->id = id;
			this->pos = pos;
		}
	};
	
	
	
	float radius;
	ofVec2f centre;
	float timeTriggered;
	int id;
	int color;
	
	map<int,Touch> touches;
	
	MiniSampler sampler;
	int playTouchId;
	float recordStartTime;
	
	
	Pad() {
		timeTriggered = 0;
		centre = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
		radius = 400;
		playTouchId = -1;
		triggerType = TRIGGER_MOMENTARY;

	}
	

	
	void set(int id, ofVec2f centre, float radius) {
		this->id = id;
		this->centre = centre;
		this->radius = radius;

		switch(id%4) {
			case 0: color = 0xe70038; break;
			case 1: color = 0x88c453; break;
			case 2: color = 0xF5CF38; break;
			case 3: color = 0x0098d0; break;
		}
	}
	
	void draw() {
	
		float ring = 0.8;
		
		if(recMode) {
			float c = currRecId==id?1:0;
			ofSetHexColor(color);
		
			
//			ofCircle(centre, radius);
			circle.draw(centre, radius*2,radius*2);
			if(currRecId==id) {
				glColor4f(1,1,1,ofMap(sin((ofGetElapsedTimef()-recordStartTime)*8), -1,1, 0.2,0.8));
				circle.draw(centre, radius*2,radius*2);
			}
			if(!sampler.isEmpty()) {
				ofSetColor(100,0,0);
				
				circle.draw(centre, radius*2*ring,radius*2*ring);
			}
		} else {
			float c = ofMap(ofGetElapsedTimef(), timeTriggered, timeTriggered+0.5, 1, 0, true);
			ofSetHexColor(color);
			//ofCircle(centre, radius);
			circle.draw(centre, radius*2,radius*2);
			glColor4f(1,1,1,0.5);

			glPushMatrix();
			glTranslatef(centre.x, centre.y, 0);
			glScalef(radius*0.98, radius*0.98, 1);
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(ofVec2f), &unitCircle[0].x);
			int num = ofMap(sampler.getPosition(), 0, 1, 0, unitCircle.size(), true);
			glDrawArrays(GL_TRIANGLE_FAN, 0, num);
			glPopMatrix();
			if(!sampler.isEmpty()) {
				ofSetHexColor(0);
				
				circle.draw(centre, radius*2*ring,radius*2*ring);
			}
		}
		
		
	}
	
	void trigger() {
		timeTriggered = ofGetElapsedTimef();
		sampler.trigger();
	}
	
	void startRecording() {
		if(currRecId==-1) {
			sampler.clear();
			currRecId = id;
			recordStartTime = ofGetElapsedTimef();
		}
	}
	
	void stopRecording() {
		if(currRecId==id) {
			printf("Can stop recording\n");
			currRecId = -1;
			//recMode = false;
		}
	}

	void toggle() {
		if(!sampler.isPlaying()) {
			trigger();
		} else {
			sampler.stop();
		}
	}
	
	
	void touchDown(float x, float y, int id) {
		touches[id] = Touch(id, ofVec2f(x,y));
		
		float d = ofDistSquared(x, y, centre.x, centre.y);
		if(d<radius*radius) {
			
			if(recMode) {
				startRecording();
			} else {
				if(triggerType==TRIGGER_MOMENTARY) {
					if(!sampler.isPlaying()) {
						trigger();
					
						playTouchId = id;
					}
				} else {
					toggle();
				}
			}
		}
		
		
	}
	
	void touchMoved(float x, float y, int id) {
		if(touches.find(id)!=touches.end()) {
			// touch re-entered
			if(touches[id].pos.distance(centre)>radius && ofVec2f(x, y).distance(centre)<radius) {
				touches[id].pos.set(x,y);
				touchDown(x, y, id);
				//return;
			}
			touches[id].pos.set(x,y);
		}
		
		

		bool fingerStillIn = false;
		
		// if there's any fingers still in the zone, keep
		map<int,Touch>::iterator it;
		for(it = touches.begin(); it != touches.end(); it++) {
			float d = ofDistSquared((*it).second.pos.x, (*it).second.pos.y, centre.x, centre.y);
			if(d<radius*radius) {
				fingerStillIn = true;
				break;
			}
		}
		
		
		// if you move out of the circle when recording, stop recording
		if(recMode) {
			//if(this->id==currRecId) {

			if(!fingerStillIn) {
				stopRecording();
			}
			//}
		} else {
			
			if(triggerType==TRIGGER_TOGGLE) return;
			if(!fingerStillIn) {
				sampler.stop();
			} else if(!sampler.isPlaying()) {
				if(MiniSampler::looping) {
					touchDown(x, y, id);
				}
			}
			
		}
	}
	void touchUp(float x, float y, int id) {
		
		if(touches.find(id)!=touches.end()) {
			touches.erase(id);
		}
		
		
		bool fingerStillIn = false;
		
		// if there's any fingers still in the zone, keep
		map<int,Touch>::iterator it;
		for(it = touches.begin(); it != touches.end(); it++) {
			float d = ofDistSquared((*it).second.pos.x, (*it).second.pos.y, centre.x, centre.y);
			if(d<radius*radius) {
				fingerStillIn = true;
				break;
			}
		}
		
		if(!fingerStillIn) {
			if(recMode) {
				stopRecording();
			} else {
				if(triggerType==TRIGGER_TOGGLE) return;
				sampler.stop();
			}
		}
	}
	
	 
	void addSamples(float *out, int length, int numChannels) {
		sampler.addSamples(out, length, numChannels);
	}
	void recordSamples(float *in, int length) {
		sampler.recordSamples(in, length);
	}

	static bool recMode;
	static int currRecId;

	static vector<ofVec2f> unitCircle;
	static ofImage circle;
	static int triggerType;
				
};

