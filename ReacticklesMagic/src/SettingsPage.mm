/**
 * SettingsPage.mm
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "SettingsPage.h"
#include "constants.h"
void SettingsPage::draw() {
	ofSetHexColor(0xFF0000);
	ofRect(0, 0, WIDTH, volume*(float)HEIGHT);
}