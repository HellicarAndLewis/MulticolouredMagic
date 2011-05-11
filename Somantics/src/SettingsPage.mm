/**
 * SettingsPage.mm
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "SettingsPage.h"
#include "constants.h"

void SettingsPage::setup() {
	//colorPicker.setup();
	root.add(&colorPicker);
}

void SettingsPage::draw() {
	//ofSetHexColor(0xFF0000);
	//ofRect(0, 0, WIDTH, volume*(float)HEIGHT);
	root.draw();
}


void SettingsPage::touchDown(float x, float y, int touchId) {
	root.touchDown(x, y, touchId);
}

void SettingsPage::touchMoved(float x, float y, int touchId) {
	root.touchMoved(x, y, touchId);
}

void SettingsPage::touchUp(float x, float y, int touchId) {
	root.touchUp(x, y, touchId);
}


