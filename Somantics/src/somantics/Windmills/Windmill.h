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

	
	
	void draw() {
		rotationSpeed *= 0.96;
		rotation += rotationSpeed;
		//rotation = modulus(rotation, 180);
		/*
		if(rotationSpeed<3 && rotation>176) {
			rotation = 0;
			rotationSpeed = 0;
		}
		if(rotationSpeed<1) {
			if(rotation>1) {
				rotationSpeed = 1;
			} else {
				rotationSpeed = 0;
			}
		}*/
		
		if(rotationSpeed<1) rotation = ofLerpDegrees(rotation, 0, 0.1);
		
		float alpha = ofMap(ABS(rotationSpeed), 0, 10, 0.2, 1, true);
		glColor4f(0,0,0,alpha);
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