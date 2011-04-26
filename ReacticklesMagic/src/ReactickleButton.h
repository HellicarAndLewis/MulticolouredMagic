/**
 * ReactickleButton.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */
#pragma once
#include "InteractiveObject.h"

class ReactickleButton: public InteractiveObject {
public:
	ReactickleButton(string screenshotUrl);
	
	void draw();
private:
	ofImage *screenshot;
};