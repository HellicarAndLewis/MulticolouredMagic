/*
 *  Example2.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "TTApp.h"

class Example2: public TTApp {
	void draw() {
		ofSetHexColor(0x00FF00);
		ofRect(0, 0, ofGetWidth(), ofGetHeight()*movement);
	}
	
};