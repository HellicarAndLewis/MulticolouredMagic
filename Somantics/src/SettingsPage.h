/**
 * SettingsPage.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */
#pragma once
#include "Reactickle.h"
#include "SomanticsColorPicker.h"
class SettingsPage: public Reactickle {
public:
	void setup();
	void draw();
	void touchDown(float x, float y, int touchId);
	void touchMoved(float x, float y, int touchId);
	void touchUp(float x, float y, int touchId);
	SomanticsColorPicker colorPicker;
	Container root;
};