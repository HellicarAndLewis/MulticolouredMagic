/*
 *  ClapBang.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */
#include "Reactickle.h"
#include "msaColor.h"

class ClapParticle {
public:
	ofPoint pos;
	ofPoint vel;
	float birth;
	float age;
	ofColor color;
	ofImage *circleImage;
	
	ClapParticle(float x, float y, float magnitude, ofColor _color, ofImage *_circleImage) {
		pos.x = x;
		pos.y = y;
		circleImage = _circleImage;
		color = _color;
		float angle = ofRandom(0, PI*2);
		float speed = magnitude*5.f + ofRandom(-2, 3);
		vel.x = speed*cos(angle);
		vel.y = speed*sin(angle);
		birth = ofGetElapsedTimef();
	}
	
	void update() {
		age = ofMap(ofGetElapsedTimef() - birth, 0, 5, 1, 0, true);
		pos += vel;
		vel.y += 0.2;
		if(pos.y>ofGetHeight() && vel.y>0) vel.y *= -0.75;
	}
	
	void draw() {
		
		ofSetColor(color.r*255, color.g*255, color.b*255, age*255);
		float radius = ofMap(age, 1, 0.6, 50, 0, true);
		circleImage->draw(pos.x, pos.y, radius*4, radius*4);
		//ofCircle(pos.x, pos.y, radius);
		ofSetColor(color.r*255, color.g*255, color.b*255, ofMap(age, 1, 0.6, 100, 0, true));
		//ofCircle(pos.x, pos.y, ofMap(age, 1, 0.9, 0, 100, false));
		radius = ofMap(age, 1, 0.8, 0, 100, false);
		circleImage->draw(pos.x, pos.y, radius*4, radius*4);
	}
	bool isDead() {
		return age<0.6;
	}
	
};


class ClapBang: public Reactickle {
public:

	ofImage img;
	void init() {
		ofSetCircleResolution(16);
	}
	
	
	void setup() {
		img.loadImage("bang.png");
		img.setAnchorPercent(0.5, 0.5);
		lastClap = 0;
		clapping = false;
		
		
		/*gui->saveToXML();
		gui->addPage("ClapBang");
		gui->addSlider("ClapThreshold",clapThreshold, 0, 1);
		gui->loadFromXML();*/
	}
	
	/*
	ofPoint findBiggestBlob() {
		contourFinder.findContours(*greyDiff, 20, (340*240)/3, 10, false);
		
		// default if there's no blobs
		if(contourFinder.nBlobs==0) {
			float x = ofRandom(ofGetWidth()/3, 2.f*ofGetWidth()/3);
			float y = ofRandom(ofGetHeight()/6, 2.f*ofGetHeight()/3);
			return ofPoint(x, y);
		}
		
		float maxArea = 0;
		int maxI = 0;
		for (int i = 0; i < contourFinder.nBlobs; i++) {
			if(contourFinder.blobs[i].area>maxArea) {
				maxArea = contourFinder.blobs[i].area;
				maxI = i;
			}
		}
		//printf("%f %f\n", contourFinder.blobs[maxI].centroid.x, contourFinder.blobs[maxI].centroid.y);
		ofPoint src = contourFinder.blobs[maxI].centroid;
		src.x *= (float)ofGetWidth()/(float)VISION_WIDTH;
		src.y *= (float)ofGetHeight()/(float)VISION_HEIGHT;
		return src;
	}*/
	void update() {
		clapThreshold = volumeThreshold;
		if(clapping) {
			
			
			ofPoint clapPoint = ofPoint(ofRandomWidth(), ofRandomHeight());//findBiggestBlob();
			
			
			msaColor color;
			color.setHSV(ofRandom(0, 360), 1, 1);


			int numParticles = ofRandom(12, 20);
			
			for(int i = 0; i < numParticles; i++) {
				if(particles.size()<100) {
					particles.push_back(ClapParticle(clapPoint.x, clapPoint.y, volume, color, &img));
				}
			}
			clapping = false;
		}
		for(int i = 0; i < particles.size(); i++) {
			particles[i].update();
			if(particles[i].isDead()) {
				particles.erase(particles.begin()+i);
				i--;
			}
		}

		
		
	}
	void draw() {
		ofBackground(0,0,0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		float timeSinceLastClap = ofGetElapsedTimef() - lastClap;
		float value = ofMap(timeSinceLastClap, 0, 0.5, 0.4, 0, true);
		glColor3f(value, 0, 0);
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
		
		for(int i = 0; i < particles.size(); i++) {
			particles[i].draw();
		}
	}
	
	
	void audioReceived(float *input, int length, int nChannels) {
		
		float lastSample = input[0];
		for(int i = 1; i < length; i++) {
			float diff = input[i] - lastSample;
			
			if(ABS(diff)>clapThreshold) {
				magnitude = ABS(diff);
				lastClap = ofGetElapsedTimef();
				clapping = true;
				return;
			}
			lastSample = input[i];
		}
	}
	float clapThreshold;
	float magnitude;
	float lastClap;
	bool clapping;
	ofxCvContourFinder contourFinder;
	vector<ClapParticle> particles;
};