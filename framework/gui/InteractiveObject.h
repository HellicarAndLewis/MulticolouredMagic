/**
 * InteractiveObject.h
 *
 * Created by Marek Bereza on 09/02/2011.
 *
 */
#pragma once

#include "ofMain.h"

class InteractiveObject: public ofRectangle {
public:
	virtual bool touchDown(float xx, float yy, int tid) { return false; }
	virtual bool touchMoved(float xx, float yy, int tid) { return false; }
	virtual bool touchUp(float xx, float yy, int tid) { return false; }
	virtual void draw() {}
	virtual void setAlpha(float alpha) {}
	virtual bool isContainer() { return false; }
};