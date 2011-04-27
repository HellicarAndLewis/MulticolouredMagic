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
	colorPicker.setup();
	items.push_back(&colorPicker);
}

void SettingsPage::draw() {
	//ofSetHexColor(0xFF0000);
	//ofRect(0, 0, WIDTH, volume*(float)HEIGHT);
	for(int i = 0; i < items.size(); i++) {
		
		items[i]->draw();
	}
}


void SettingsPage::touchDown(float x, float y, int touchId) {
	for(int i = 0; i < items.size(); i++) {
		if(items[i]->touchDown(x, y, touchId)) {
			return;
		}
	}
}

void SettingsPage::touchMoved(float x, float y, int touchId) {
	for(int i = 0; i < items.size(); i++) {
		if(items[i]->touchMoved(x, y, touchId)) {
			return;
		}
	}
}

void SettingsPage::touchUp(float x, float y, int touchId) {

	for(int i = 0; i < items.size(); i++) {
		if(items[i]->touchUp(x, y, touchId)) {
			return;
		}
	}
}


