/**
 * Follow.h
 * magic
 *
 * Created by Marek Bereza on 12/04/2011.
 *
 */
#include "Reactickle.h"
#include "FollowParticle.h"
#define NUM_SWARM_PARTICLES 150
class FollowTouch: public ofVec2f {
public:
	int touchId;
	int shapeId;
	FollowTouch(float x, float y, int touchId, int shapeId) {
		this->shapeId = shapeId;
		this->touchId = touchId;
		this->x = x;
		this->y = y;
	}
};
class Follow: public Reactickle {
public:
	float timeOfLastInteraction;
	bool needsKinect() { return true; }
	void update();
	void draw();
	void start();
	
	void clap();
	void modeChanged();
	virtual bool touchDown(float x, float y, int touchId);
	virtual bool touchMoved(float x, float y, int touchId);
	virtual bool touchUp(float x, float y, int touchId);
	void collision(FollowParticle &p1, FollowParticle &p2);
private:
	vector<FollowTouch> touches;
	FollowParticle particles[NUM_SWARM_PARTICLES];
	void keyPressed(int key);
	int numParticles;
	int currShapeId;
};