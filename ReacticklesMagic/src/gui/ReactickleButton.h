/**
 * ReactickleButton.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */
#pragma once
#include "InteractiveObject.h"
#include "GlowingBorder.h"

class ReactickleButtonListener {
public:
	virtual void reactickleSelected(string name) = 0;
};
class ReactickleButton: public InteractiveObject {
public:
	ReactickleButton(string name);
	
	void draw();
	
	bool touchDown(float xx, float yy, int tid);
	bool touchMoved(float xx, float yy, int tid);
	bool touchUp(float xx, float yy, int tid);
		
	void setListener(ReactickleButtonListener *listener);
private:
	float startX;
	ofImage *screenshot;
	string name;
	ReactickleButtonListener *listener;
	int currTouchId;
	bool down;
	GlowingBorder border;
};