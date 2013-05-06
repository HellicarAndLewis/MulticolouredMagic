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
 * Windmill.h
 * WindmillsDemo
 *
 * Created by Marek Bereza on 10/05/2011.
 *
 */

#include "constants.h"
#include "ImageCache.h"

class Windmill {
public:
	ofVec2f pos;
	float rotation;
	float rotationSpeed;
	ofImage *propellor;
	Windmill() {
		rotationSpeed = 0;
		rotation = 0;
		propellor = ImageCache::getImage(IMAGE_ROOT+"propellor.png");
		propellor->setAnchorPercent(0.5, 0.5);
	}
	
	double modulus(double a, double b)
	{
		int result = static_cast<int>( a / b );
		return a - static_cast<double>( result ) * b;
	}

	
	
	void draw(const ofColor &c) {
		rotationSpeed *= 0.96;
		rotation += rotationSpeed;
		
		
		if(rotationSpeed<1) rotation = ofLerpDegrees(rotation, 0, 0.1);
		
		float alpha = ofMap(ABS(rotationSpeed), 0, 10, 0.2, 1, true);
		glColor4f(c.r/255.f, c.g/255.f, c.b/255.f, alpha);
		glPushMatrix();
		glTranslatef(pos.x, pos.y, 0);
		glRotatef(rotation, 0, 0, 1);
		propellor->draw(0, 0, 6, 40);
		glPopMatrix();
	}
	
	
	float pld(ofVec2f a, ofVec2f b, ofVec2f p) {
		
		// from http://www.softsurfer.com/Archive/algorithm_0102/algorithm_0102.htm#Distance to 2-Point Line
		return ((a.y - b.y)*p.x + (b.x - a.x)*p.y + (a.x*b.y - b.x*a.y));
	}
	

	
	float fastInverseSqrt(float x) {
		float xhalf = 0.5f*x;
		int i = *(int*)&x; // get bits for floating value
		i = 0x5f375a86- (i>>1); // gives initial guess y0
		x = *(float*)&i; // convert bits back to float
		x = x*(1.5f-xhalf*x*x); // Newton step, repeating increases accuracy
		return x;
	}
	
	void applyForce(ofVec2f force) {
		rotationSpeed += force.length();
	}
	void applyForce(ofVec2f forcePos, ofVec2f force) {
		float distance = 1.f/fastInverseSqrt(pos.distanceSquared(forcePos));
		
		float maxForce = 3;
		// map the distance
		float magnitude = ofMap(distance, 10, WIDTH/6.f, maxForce, 0, true);
		magnitude = maxForce/fastInverseSqrt(magnitude/maxForce);
		if(pld(forcePos, forcePos+force, pos)>0) {
			rotationSpeed += magnitude;	
		} else {
			rotationSpeed -= magnitude;	
		}
		
	}
};