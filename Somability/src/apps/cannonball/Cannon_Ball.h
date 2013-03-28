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
 *  Cannon_Ball.h, created by Marek Bereza on 11/06/2012.
 */




namespace cannon {
	
	class Ball: public ofVec2f {
	public:
		
		ofVec2f vel;
		float radius;
		bool colliding;
		
		void setup() {
			colliding = false;
			radius = ofRandom(10, 25);
			x = ofGetWidth()/2 + ofRandom(-ofGetWidth()/4, ofGetWidth()/4);
			y = ofGetHeight()/2 + ofRandom(-ofGetHeight()/4, ofGetHeight()/4);
			vel = ofVec2f(15, 0);
		}
		
		void update() {
			*this += vel;
			if(x>ofGetWidth()-radius && vel.x>0) {
				vel.x *= -1;
			} else if(x<radius && vel.x<0) {
				vel.x *= -1;
			}
			
			if(y>ofGetHeight()-radius && vel.y>0) {
				vel.y *= -1;
			} else if(y<radius && vel.y<0) {
				vel.y *= -1;
			}		
		}
		
		bool doCollision(ofPoint &a, ofPoint &b) {
			//	if(y<a.y) return;
			float d = pointLineDistance(a,b, *this);
			if(d<radius) {
				
				
				
				// wall normal
				ofVec2f wallNormal = a - b;
				wallNormal.set(-wallNormal.y, wallNormal.x);
				
				resolveFixedCollision(wallNormal);
				colliding = true;
			} else {
				colliding = false;
			}
			return colliding;
		}
		
		void resolveFixedCollision(ofVec2f &wallNormal) {
			ofVec2f c = componentVector(vel, wallNormal) * 2;
			ofVec2f v = vel - c;
			vel.x = v.x;
			vel.y = v.y;
		}
		
		
		ofVec2f componentVector(ofVec2f &vec, ofVec2f &dir) {
			ofVec2f v(dir.x, dir.y);
			v.normalize();
			v *= vec.dot(v);
			return v;
		}
		
		float pointLineDistance(ofVec2f a, ofVec2f b, ofVec2f p) {
			
			// from http://www.softsurfer.com/Archive/algorithm_0102/algorithm_0102.htm#Distance to 2-Point Line
			return abs(((a.y - b.y)*p.x + (b.x - a.x)*p.y + (a.x*b.y - b.x*a.y))/
					   sqrt((b.x-a.x)*(b.x-a.x) + (b.y - a.y)*(b.y - a.y))
					   );
		}
		
		
		void draw() {
			ofFill();
			if(colliding) {
				glColor4f(1, 0, 0, 1);
			} else {
				ofSetColor(200, 200, 255);
			}
			
			ofEllipse(x, y, radius*2, radius*2);
		}
	};
	
};