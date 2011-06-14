/**
 * CircleSwarm.cpp
 * magic
 *
 * Created by Marek Bereza on 12/04/2011.
 *
 */

#include "Follow.h"

void Follow::start() {
	currShapeId = 0;
}

void Follow::clap() {
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
	}
    
	if(mode==1 && numParticles+1<NUM_SWARM_PARTICLES) {
		
		particles[numParticles++].spawn(ofRandomWidth(), ofRandomHeight(), mode, currShapeId);
	}
}



void Follow::update() {

	float timeNow = ofGetElapsedTimef();
	
	float timeSinceLastInteraction = timeNow - timeOfLastInteraction;        
	
	if((volume > volumeThreshold) && (timeSinceLastInteraction > 0.3f )){
		clap(); //simulate a touch in the centre of the screen
		timeOfLastInteraction = timeNow;
	}
	
	// first update particles
	for(int i = 0; i < numParticles; i++) {
		if(particles[i].isAlive()) {
			particles[i].update();
		} else {
			if(touches.size()>0) {
				int ii = ofRandom(0, 100);
				ii %= touches.size();
				int shape = 0;
				if(mode!=0) {
					shape = touches[ii].shapeId;
				}
				particles[i].spawn(touches[ii].x, touches[ii].y, mode, shape);
			} else {
				int shape = 0;
				//if(mode!=0) shape = currShapeId;
				particles[i].spawn(ofRandomWidth(), ofRandomHeight(), mode, shape);
			}
		}
	}

	// then do attractions
	for(int i = 0; i < touches.size(); i++) {
		for(int j = 0; j < numParticles; j++) {
			ofVec2f pos = ofVec2f(touches[i].x, touches[i].y);
			//printf("%f, %f\n", pos.x, pos.y);
			particles[j].attract(pos);
		}
	}
	
	
	
	if(mode>0) {
		for(int i = 0; i < NUM_SWARM_PARTICLES; i++) {
			particles[i].shape = currShapeId;
		}
		
	} else {
		for(int i = 0; i < numParticles; i++) {
			particles[i].shape = MAGIC_CIRCLE;
		}
	}
	
	//printf("Touches: %d\n", touches.size());
	
	// then do collisions
	for(int i = 0; i < numParticles; i++) {
		for(int j = i+1; j < numParticles; j++) {
			if(i!=j) {
				collision(particles[j], particles[i]);
			}
		}
	}
}

void Follow::draw() {
	for(int i = 0; i < numParticles; i++) {
		particles[i].draw();
	}

	ofSetColor(100, 100, 100, 40);
	for(int i = 0; i < touches.size(); i++) {
		ofVec2f left = ofVec2f(touches[i].x, touches[i].y);
		ofCircle(left, 10);
	}
}


void Follow::collision(FollowParticle &p1, FollowParticle &p2) {
	float minDistSqr = p1.radius + p2.radius;
	minDistSqr *= minDistSqr;
	float currDistSqr = p2.pos.squareDistance(p1.pos);
	
	// there's a collision
	if(minDistSqr>currDistSqr) {
		// vector from bubble1 to 2
		ofVec2f dist = p2.pos - p1.pos;
		dist.normalize();
		dist *= sqrt(minDistSqr);
		p2.pos = ((p1.pos + dist)*0.1+p2.pos*0.9);
	}
}

bool Follow::touchDown(float x, float y, int touchId) {
	if(currShapeId<0 || currShapeId>=NUM_MAGIC_SHAPES) currShapeId = 0;
	touches.push_back(FollowTouch(x, y, touchId, currShapeId));
	return true;
}

bool Follow::touchMoved(float x, float y, int touchId) {
//	printf("x: %f  y: %f  id: %d\n", x, y, touchId);
	for(int i = 0; i < touches.size(); i++) {
		if(touchId==touches[i].touchId) {
			touches[i].x = x;
			touches[i].y = y;
			
			return true;
		}
	}
	return touchDown(x, y, touchId);
}

bool Follow::touchUp(float x, float y, int touchId) {
	for(int i = 0; i < touches.size(); i++) {
		if(touchId==touches[i].touchId) {
			touches.erase(touches.begin()+i);
			return true;
		}
	}
	return true;
}
void Follow::keyPressed(int key) {
	switch(key) {
		case 'a':
			FollowParticle::colorMode = COLOR_MODE_RAINBOW;
			break;
		case 's':
			FollowParticle::colorMode = COLOR_MODE_RED;
			break;
		case 'd':
			FollowParticle::colorMode = COLOR_MODE_GREEN;
			break;
		case 'f':
			FollowParticle::colorMode = COLOR_MODE_BLUE;
			break;
	}
	
}

void Follow::modeChanged() {
	if(mode==0) {
		numParticles = 1;
		particles[0].spawn(ofGetWidth()*0.5, ofGetHeight()*0.5, mode);
	} else if(mode==1) {
		numParticles = 1;
	} else if(mode==2) {
		numParticles = NUM_SWARM_PARTICLES;
		for(int i = 0; i < numParticles; i++) {
			particles[i].spawn(ofRandomWidth(), ofRandomHeight(), mode, currShapeId);
		}
		
	}
}