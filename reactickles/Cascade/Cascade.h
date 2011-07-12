/*
 *  Cascade.h
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */
#include "Reactickle.h"
#include "msaColor.h"
#include "MagicShapes.h"

class CascadeParticle {
public:
	ofPoint pos;
	ofPoint vel;
	float birth;
	float age;
	ofColor color;
    int shape;
    
	CascadeParticle(float x, float y, float magnitude, ofColor _color, int _shape){
		pos.x = x;
		pos.y = y;
		color = _color;
		float angle = ofRandom(0, PI*2);
		float speed = magnitude*5.f + ofRandom(-2, 3);
		vel.x = speed*cos(angle);
		vel.y = speed*sin(angle);
		birth = ofGetElapsedTimef();
        shape = _shape;
	}
	
	void update() {
		age = ofMap(ofGetElapsedTimef() - birth, 0, 5, 1, 0, true);
		pos += vel;
		vel.y += 0.2;
		if(pos.y>ofGetHeight() && vel.y>0) vel.y *= -0.75;
	}
	
	void draw() {
		
//		ofSetColor(color.r*255, color.g*255, color.b*255, age*255);
//		float radius = ofMap(age, 1, 0.6, 50, 0, true);
//		circleImage->draw(pos.x, pos.y, radius*4, radius*4);
//		//ofCircle(pos.x, pos.y, radius);
//		ofSetColor(color.r*255, color.g*255, color.b*255, ofMap(age, 1, 0.6, 100, 0, true));
//		//ofCircle(pos.x, pos.y, ofMap(age, 1, 0.9, 0, 100, false));
//		radius = ofMap(age, 1, 0.8, 0, 100, false);
//		circleImage->draw(pos.x, pos.y, radius*4, radius*4);
        
		ofSetColor(color.r*255, color.g*255, color.b*255, age*255);
		float radius = ofMap(age, 1, 0.6, 50, 0, true);
        drawShape(shape, pos, radius*4);
		ofSetColor(color.r*255, color.g*255, color.b*255, ofMap(age, 1, 0.6, 100, 0, true));
		radius = ofMap(age, 1, 0.8, 0, 100, false);
		drawShape(shape, pos, radius*4);        
	}
	bool isDead() {
		return age<0.6;
	}
	
};


class Cascade: public Reactickle {
public:

	void start() {
        currShapeId = 0;
        
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        int reactickleNumber = 6;
        m.setAddress( "/reacticklechange" );
        m.addIntArg( reactickleNumber );
        ReactickleApp::instance->sender.sendMessage( m );
#endif
    }
	
	void setup() {
		lastClap = 0;
		clapping = false;
        currShapeId = 0;
	}
	
	void update() {
		clapThreshold = volumeThreshold;
		if(clapping) {
            
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
            
			ofPoint clapPoint = ofPoint(ofRandomWidth(), ofRandomHeight());
			
			msaColor color;
			color.setHSV(ofRandom(0, 360), 1, 1);
            
			int numParticles = ofRandom(12, 20);
			
			for(int i = 0; i < numParticles; i++) {
				if(particles.size()<100) {
					particles.push_back(CascadeParticle(clapPoint.x, clapPoint.y, volume, color, currShapeId));
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
		ofSetColor(value*255.f, 0, 0);
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
                
#ifndef TARGET_OF_IPHONE
                //claps are touch downs for this one...
                ofxOscMessage m;
                m.setAddress( "/touchdown" );
                m.addIntArg(mode);
                ReactickleApp::instance->sender.sendMessage(m);
#endif
				return;
			}
			lastSample = input[i];
		}
	}
    
    int getNumModes() {
		return 3;
	}
    
    void modeChanged() {        
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        m.setAddress("/modechange");
        m.addIntArg( mode );
        ReactickleApp::instance->sender.sendMessage( m );
#endif
    }
    
	float clapThreshold;
	float magnitude;
	float lastClap;
	bool clapping;
	vector<CascadeParticle> particles;
    int currShapeId;
};