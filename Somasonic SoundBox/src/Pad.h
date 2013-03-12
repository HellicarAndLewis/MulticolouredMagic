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
	Pad() {
		timeTriggered = 0;
		centre = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
		radius = 400;
		playTouchId = -1;
		
	}
	
	Pad(int id, ofVec2f centre, float radius) {
		set(id,centre,radius);
	}
	
	void set(int id, ofVec2f centre, float radius) {
		this->id = id;
		this->centre = centre;
		this->radius = radius;
	}
	
	void draw() {
	

		
		if(recMode) {
			float c = currRecId==id?1:0;
			if(sampler.isEmpty()) {
				glColor4f(0.5, 0.2, 0.2, 1);
			} else {
				glColor4f(0.5+0.5*c, c, c, 1);
			}
			ofCircle(centre, radius);
			
			if(sampler.isEmpty()) {
				ofSetHexColor(0);
				ofDrawBitmapString("HOLD ME DOWN\n  TO RECORD", centre.x-40, centre.y-15);
			}
		} else {
			float c = ofMap(ofGetElapsedTimef(), timeTriggered, timeTriggered+0.5, 1, 0, true);
			if(sampler.isEmpty()) {
				glColor4f(0.3, 0.3, 0.3, 1);
			} else {
				glColor4f(0.5+0.5*c, 0.5+0.5*c, 0.7+0.3*c, 1);
			}
			ofCircle(centre, radius);
			glColor4f(c, c, 0.5+0.5*c, 1);

			glPushMatrix();
			glTranslatef(centre.x, centre.y, 0);
			glScalef(radius, radius, 1);
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(ofVec2f), &unitCircle[0].x);
			int num = ofMap(sampler.getPosition(), 0, 1, 0, unitCircle.size(), true);
			glDrawArrays(GL_TRIANGLE_FAN, 0, num);
			glPopMatrix();
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
};

