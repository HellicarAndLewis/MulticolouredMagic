/*
 *  main.cpp
 *  intersect
 *
 *  Created by Ben Jones on 27/02/2010.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "testApp.h"

int main() {
	ofSetupOpenGL(1024, 768, OF_FULLSCREEN);
	ofRunApp(new testApp);
}


