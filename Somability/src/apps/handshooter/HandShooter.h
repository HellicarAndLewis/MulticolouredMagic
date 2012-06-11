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
 *  HandShooter.h, created by Marek Bereza on 11/06/2012.
 */

#pragma once



#include "Reactickle.h"
class HandParticle: public ofVec2f {
public:	
	ofVec2f vel;
	float grav;
	int life;
	void setup(ofVec2f pos, ofVec2f dir) {
		life = 0;
		x = pos.x;
		y = pos.y;
		vel = dir*ofRandom(10, 20);
		grav = ofRandom(-0.1, 0.8);
	}
	
	void update() {
		// gravity
		vel.y += 1+grav;
		*this += vel;
		life+=5;
	}
	void draw() {
		ofSetHexColor(0xFF9999);
		float rad = 0;
		if(life<50) {
			rad = ofMap(life, 0, 50, 2, 15);
		} else {
			rad = ofMap(life, 50, 100, 15, 0, true);
		}
		ofColor c = ofColor::fromHsb((life+127) % 255, 255,255);
		ofSetColor(c);
		ofLine(*this, *this+(vel*2));
//		ofCircle(*this, 5);
	}
};

class HandShooter: public Reactickle {
	
public:
	
	
	void setup();
	void update();
	void draw();
	void emitParticle(ofVec2f pos, ofVec2f dir);	
	bool needsKinect() { return true; }
	deque<HandParticle> particles;
};

