/**
 * CircleSwarm.h
 * magic
 *
 * Created by Marek Bereza on 12/04/2011.
 *
 */
#include "TTApp.h"
#include "SwarmParticle.h"
#define NUM_SWARM_PARTICLES 150
class SwarmTouch: public ofVec2f {
public:
	int touchId;
	int shapeId;
	SwarmTouch(float x, float y, int touchId, int shapeId) {
		this->shapeId = shapeId;
		this->touchId = touchId;
		this->x = x;
		this->y = y;
	}
};
class CircleSwarm: public TTApp {
public:
	float timeOfLastInteraction;
	bool needsKinect() { return true; }
	void update();
	void draw();
	void init();
	
	void clap();
	void modeChanged();
	virtual void touchDown(float x, float y, int touchId);
	virtual void touchMoved(float x, float y, int touchId);
	virtual void touchUp(float x, float y, int touchId);
	void collision(SwarmParticle &p1, SwarmParticle &p2);
private:
	vector<SwarmTouch> touches;
	SwarmParticle particles[NUM_SWARM_PARTICLES];
	void keyPressed(int key);
	int numParticles;
	int currShapeId;
};