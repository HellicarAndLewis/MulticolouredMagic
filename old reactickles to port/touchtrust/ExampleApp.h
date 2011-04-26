/*
 *  ExampleApp.h
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"

class ExampleApp: public Reactickle {
	void draw() {
		ofSetColor(0xFF0000);
		ofRect(0, 0, ofGetWidth()*volume, ofGetHeight());
	}
	
};