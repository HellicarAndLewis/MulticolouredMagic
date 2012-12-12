/*
 *  GuiFPSCounter.h
 *  Gui
 *
 *  Created by Marek Bereza on 11/02/2010.
 *
 */

class FPSCounter: public xmlgui::Control {
public:
	
	
	FPSCounter(): Control() {
		height = 25;
		width = 60;
	}
	
	void draw() {
		ofSetColor(0, 100, 0);
		ofRect(x, y, width, height);
		ofSetColor(255, 255, 255);
		xmlgui::Resources::drawString(ofToString(ofGetFrameRate(), 3), x+3, y+14);
	}
};