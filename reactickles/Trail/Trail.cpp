/**
 * Trail.cpp
 * magic
 *
 * Created by Marek Bereza on 11/04/2011.
 *
 */
#include "constants.h"

#include "Trail.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif

void Trail::start() {
	currShapeId = MAGIC_CIRCLE;

}

void Trail::update() {
    float timeNow = ofGetElapsedTimef();

	float timeSinceLastInteraction = timeNow - timeOfLastInteraction;

	if((volume > volumeThreshold) && (timeSinceLastInteraction > 0.3f )){
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
        }else{
            currShapeId = MAGIC_CIRCLE;
        }

#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        m.setAddress( "/shapechange" );
        m.addIntArg( currShapeId );
        ReactickleApp::instance->sender.sendMessage( m );
#endif

		timeOfLastInteraction = timeNow;
	}

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
		   particles[i].pos.x-particles[i].radius>WIDTH
		   ||
		   particles[i].pos.y-particles[i].radius>HEIGHT) {

			particles.erase(particles.begin()+i);
			i--;
		}
	}
}


void Trail::draw() {
	//ofClear(100, 0, 0, 255);
	//glDisable(GL_DEPTH_TEST);
		ofBackground(0,0,0);
	ofClear(0, 0, 0, 0);

	for(int i = 0; i < particles.size(); i++) particles[i].draw(currShapeId);
}


void Trail::spawn(ofVec2f pos, ofColor color) {
	if(particles.size()<MAX_NUM_PARTICLES) {
		particles.push_back(TrailParticle());
		particles.back().pos = pos;
		particles.back().color = color;
	}
}

void Trail::collision(TrailParticle &p1, TrailParticle &p2) {
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

bool Trail::touchDown(float x, float y, int touchId) {

    touchMoved(x, y, touchId);

	return true;
}

bool Trail::touchMoved(float x, float y, int touchId) {
	int colorIndex = Settings::getInstance()->settings["fgColor"];

	if(mode==0) {
		if(ofRandom(0, 1)>0.1) return true;
	} else if(mode==1) {
		if(ofRandom(0, 1)>0.5) return true;
	}
	for(int i = 0; i < SPAWN_RATE; i++) {
		ofColor color;
		if(colorIndex==20) {
			color.setHsb(ofRandom(0, 360), 190, 255, 255);
		} else {
			color.setHex(ColorPicker::colors[colorIndex]);
			color.setBrightness(ofRandom(125, 255));
		}
		spawn(ofVec2f(x, y), color);
	}
	return true;
}


bool Trail::touchUp(float x, float y, int touchId) {
	touchMoved(x, y, touchId);
	return true;
}
