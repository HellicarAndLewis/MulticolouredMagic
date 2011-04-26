/**
 * Circles2D.h
 * magic
 *
 * Created by Marek Bereza on 11/04/2011.
 *
 */
#include "TTApp.h"
#include "CircleParticle.h"
#define SPAWN_RATE 1
#define MAX_NUM_PARTICLES 200
class Circles2D: public TTApp {
public:
	void update();
	void draw();

	
	bool needsKinect() { return true; }
	virtual void touchDown(float x, float y, int touchId);
	virtual void touchMoved(float x, float y, int touchId);
	virtual void touchUp(float x, float y, int touchId);
private:
	void spawn(ofVec2f pos);
	void collision(CircleParticle &bubble1, CircleParticle &bubble2);
	vector<CircleParticle> particles;
};