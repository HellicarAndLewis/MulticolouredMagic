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


class Pad {
public:
	float radius;
	ofVec2f centre;
	float timeTriggered;
	int id;
	int color;
	Pad() {
		timeTriggered = 0;
		centre = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
		radius = 400;
		playTouchId = -1;
		
	}
	

	
	void set(int id, ofVec2f centre, float radius) {
		this->id = id;
		this->centre = centre;
		this->radius = radius;

		switch(id%4) {
			case 0: color = 0xe70038; break;
			case 1: color = 0x88c453; break;
			case 2: color = 0xf39a3c; break;
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
		}
	}
	
	void stopRecording() {
		if(currRecId==id) {
			printf("Can stop recording\n");
			currRecId = -1;
			recMode = false;
		}
	}

	struct Touch {
		ofVec2f pos;
		int id;
		Touch(int id = 0, ofVec2f pos = ofVec2f()) {
			this->id = id;
			this->pos = pos;
		}
	};
	
	void touchDown(float x, float y, int id) {
		touches[id] = Touch(id, ofVec2f(x,y));
					
		float d = ofDistSquared(x, y, centre.x, centre.y);
		if(d<radius*radius) {
			if(recMode) {
				startRecording();
			} else {
				if(!sampler.isPlaying()) {
					trigger();
				
					playTouchId = id;
				}
			}
		}
	}
	
	void touchMoved(float x, float y, int id) {
		if(touches.find(id)!=touches.end()) {
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

			if(!fingerStillIn) {
				sampler.stop();
			} else if(!sampler.isPlaying()) {
				touchDown(x, y, id);
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
	map<int,Touch> touches;
	
	MiniSampler sampler;
	static bool recMode;
	static int currRecId;
	int playTouchId;
	static vector<ofVec2f> unitCircle;
	static ofImage circle;
};

