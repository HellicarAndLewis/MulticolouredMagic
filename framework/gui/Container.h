/**
 * Container.h
 * SomanticsMac
 *
 * Created by Marek Bereza on 11/05/2011.
 *
 */
#pragma once
#include "InteractiveObject.h"

class Container: public InteractiveObject {
public:
	virtual bool touchDown(float x, float y, int touchId) {
		x -= this->x;
		y -= this->y;
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchDown(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}
	
	virtual bool touchMoved(float x, float y, int touchId) {
		x -= this->x;
		y -= this->y;
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchMoved(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}
	
	virtual bool touchUp(float x, float y, int touchId) {
		x -= this->x;
		y -= this->y;
		for(int i = 0; i < items.size(); i++) {
			if(items[i]->touchUp(x, y, touchId)) {
				return true;
			}
		}
		return false;
	}

	
	virtual void draw() {
		glPushMatrix();
		glTranslatef(x, y, 0);
		for(int i = 0; i < items.size(); i++) {
			items[i]->draw();
		}
		glPopMatrix();
	}
	void add(InteractiveObject *obj) {
		items.push_back(obj);
	}
	void add(InteractiveObject &obj) {
		items.push_back(&obj);
	}
protected:
	vector<InteractiveObject*> items;
};