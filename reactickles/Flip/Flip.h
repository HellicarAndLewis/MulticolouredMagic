/**
 * Flip.h
 * magic
 *
 * Created by Marek Bereza on 13/04/2011.
 *
 */
#include "Reactickle.h"
class FlipTouch: public ofVec2f {
public:
	FlipTouch(float x, float y, int touchId) {
		this->x = x;
		this->y = y;
		this->touchId = touchId;
	}
	int touchId;
};
class Flip: public Reactickle {
public:
	
	bool needsKinect() { return true; }

	virtual void update();
	virtual void draw();
	virtual bool touchDown(float x, float y, int touchId);
	virtual bool touchMoved(float x, float y, int touchId);
	virtual bool touchUp(float x, float y, int touchId);
	vector<FlipTouch> touches;

	// this really should be just an ofVec2f rather than a 
	// deque of them. It was originally needed as a trail.
	// haven't got time to change that right now.
	deque<ofVec2f> pos;
	void start();
	int currShapeId;
	ofVec2f lastPos;
};