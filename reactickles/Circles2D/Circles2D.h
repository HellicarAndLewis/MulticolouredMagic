/**
 * Circles2D.h
 * magic
 *
 * Created by Marek Bereza on 11/04/2011.
 *
 */
#include "Reactickle.h"
#include "CircleParticle.h"
#define SPAWN_RATE 1
#define MAX_NUM_PARTICLES 200
class Circles2D: public Reactickle {
public:
	void update();
	void draw();

#ifndef TARGET_OF_IPHONE
	bool needsKinect() { return true; }
#endif
	virtual bool touchDown(float x, float y, int touchId);
	virtual bool touchMoved(float x, float y, int touchId);
	virtual bool touchUp(float x, float y, int touchId);
private:
	void spawn(ofVec2f pos);
	void collision(CircleParticle &bubble1, CircleParticle &bubble2);
	vector<CircleParticle> particles;
};