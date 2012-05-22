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

	virtual void draw();
	
	virtual bool touchDown(float xx, float yy, int tid);
	virtual bool touchMoved(float xx, float yy, int tid);
	virtual bool touchUp(float xx, float yy, int tid);
		
	void setListener(ReactickleButtonListener *listener);
protected:
	virtual void setup(string name);
	string name;
	int currTouchId;
	bool down;
	ReactickleButtonListener *listener;
private:
	float startX;
	ofImage *screenshot;
	
	
	
	GlowingBorder border;
};