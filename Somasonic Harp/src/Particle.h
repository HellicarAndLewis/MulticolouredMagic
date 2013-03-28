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
 * Particle.h
 * TukeSprint
 *
 * Created by Marek Bereza on 30/04/2011.
 *
 */


class Particle {
public:
	ofPoint pos, vel;
	float age;
	bool alive;
	static ofImage particle;
	ofImage *actualImage;
	//	static ofxControlPanel *gui;
	static ofColor color;
	float maxSize;
	float maxAge;
	Particle(float x = 0, float y = 0, float speed = 0, float angle = 0) {
		//if(particle.width==0) {
		//	particle.loadImage("particle.png");
		//	particle.setAnchorPercent(0.5, 0.5);
		//}
		//if(AppSettings::image!=NULL) {
		//	actualImage = AppSettings::image;
		//} else {
			actualImage = &particle;
		//}
		
		alive = true;
		age = 0;
		pos.x = x;
		pos.y = y;
		speed *= 60;// this is the speed of the particle
		vel.x = speed*cos(angle);
		vel.y = speed*sin(angle);
		#ifdef TARGET_OF_IPHONE
		maxSize = 30;
		#else
		maxSize = 120;
		#endif
		maxAge = 80;
	}
	void update() {
		age++;
		pos += vel;
	}
	
	void draw() {
		float radius = ofMap(age, 0, maxAge, maxSize, 0);
		float alpha = ofMap(age, 0, maxAge, 255, 0);
		if(radius<0) {
			alive = false;
			alpha = 0;
			radius = 0;
		}
		ofSetColor(color.r, color.g, color.b, alpha);
		ofCircle(pos, radius);
//		actualImage->setAnchorPercent(0.5, 0.5);
//		actualImage->draw(pos.x, pos.y, radius, radius);
//		actualImage->setAnchorPercent(0, 0);
	}
};