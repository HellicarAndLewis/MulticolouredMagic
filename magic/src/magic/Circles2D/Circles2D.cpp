/**
 * Circles2D.cpp
 * magic
 *
 * Created by Marek Bereza on 11/04/2011.
 *
 */

#include "Circles2D.h"

void Circles2D::update() {
	for(int i = 0; i < particles.size(); i++) particles[i].update();
	
	// check for collisions
	
	for(int i = 0; i < particles.size(); i++) {
		for(int j = i+1; j < particles.size(); j++) {
			//if(i!=j) {
				collision(particles[j], particles[i]);
			//}
		}
	}
	// check if bubbles have disappeared off the edge
	// (This doesn't work perfectly.)
	for(int i = 0; i < particles.size(); i++) {
		if(
		   !particles[i].isAlive()
		   ||
		   particles[i].pos.x+particles[i].radius<0
		   ||
		   particles[i].pos.y+particles[i].radius<0
		   ||
		   particles[i].pos.x-particles[i].radius>ofGetWidth()
		   ||
		   particles[i].pos.y-particles[i].radius>ofGetHeight()) {
			
			particles.erase(particles.begin()+i);
			i--;
		}
	}
}


void Circles2D::draw() {
	//ofClear(100, 0, 0, 255);
	//glDisable(GL_DEPTH_TEST);
		ofBackground(0,0,0);
	ofClear(0, 0, 0, 0);
	
	for(int i = 0; i < particles.size(); i++) particles[i].draw();
}


void Circles2D::spawn(ofVec2f pos) {
	if(particles.size()<MAX_NUM_PARTICLES) {
		particles.push_back(CircleParticle());
		particles.back().pos = pos;
	}
}

void Circles2D::collision(CircleParticle &p1, CircleParticle &p2) {
	float minDistSqr = p1.radius + p2.radius;
	minDistSqr *= minDistSqr;
	float currDistSqr = p2.pos.squareDistance(p1.pos);
	
	// there's a collision
	if(minDistSqr>currDistSqr) {
		// vector from bubble1 to 2
		ofVec2f dist = p2.pos - p1.pos;
		dist.normalize();
		dist *= sqrt(minDistSqr);
		p2.pos = p1.pos + dist;
	}
}

void Circles2D::touchDown(float x, float y, int touchId) {
	for(int i = 0; i < SPAWN_RATE; i++) spawn(ofVec2f(x, y));
}

void Circles2D::touchMoved(float x, float y, int touchId) {
	for(int i = 0; i < SPAWN_RATE; i++) spawn(ofVec2f(x, y));
}

void Circles2D::touchUp(float x, float y, int touchId) {
	for(int i = 0; i < SPAWN_RATE; i++) spawn(ofVec2f(x, y));
}
