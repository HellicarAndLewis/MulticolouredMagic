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
		}
	}

	void touchDown(float x, float y, int id) {
		float d = ofDistSquared(x, y, centre.x, centre.y);
		if(d<radius*radius) {
			if(recMode) {
				startRecording();
			} else {
				trigger();
				playTouchId = id;
			}
		}
	}
	void touchMoved(float x, float y, int id) {
		// if you move out of the circle when recording, stop recording
		if(recMode) {
			if(this->id==currRecId) {

				float d = ofDistSquared(x, y, centre.x, centre.y);
				if(d>radius*radius) {
					stopRecording();
				}
			}
		} else {

			float d = ofDistSquared(x, y, centre.x, centre.y);
			// if finger falls off play circle
			if(d>radius*radius) {
				if(id==playTouchId) {
				
					sampler.stop();
				}
				
			} else if(!sampler.isPlaying()) {
				touchDown(x, y, id);
			}
			
		}
	}
	void touchUp(float x, float y, int id) {
		float d = ofDistSquared(x, y, centre.x, centre.y);
		if(d<radius*radius) {
		
			if(recMode) {
				printf("Stopping recording\n");
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
	
	
	MiniSampler sampler;
	static bool recMode;
	static int currRecId;
	int playTouchId;
	static vector<ofVec2f> unitCircle;
};