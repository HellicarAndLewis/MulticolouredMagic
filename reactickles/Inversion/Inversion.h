/**
 * Inversion.h
 * magic
 *
 * Created by Marek Bereza on 13/04/2011.
 *
 */
#include "Reactickle.h"
class InversionTouch: public ofVec2f {
public:
	InversionTouch(float x, float y, int touchId) {
		this->x = x;
		this->y = y;
		this->touchId = touchId;
	}
	int touchId;
};
class Inversion: public Reactickle {
public:
	
	bool needsKinect() { return true; }

	virtual void update();
	virtual void draw();
	virtual void touchDown(float x, float y, int touchId);
	virtual void touchMoved(float x, float y, int touchId);
	virtual void touchUp(float x, float y, int touchId);
	vector<InversionTouch> touches;

	// this really should be just an ofVec2f rather than a 
	// deque of them. It was originally needed as a trail.
	// haven't got time to change that right now.
	deque<ofVec2f> pos;
	void start();
	int currShapeId;
	ofVec2f lastPos;
};