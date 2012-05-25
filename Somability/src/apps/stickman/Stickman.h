//
//  Stickman.h
//  Somability
//
//  Created by Marek Bereza on 24/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Somability_Stickman_h
#define Somability_Stickman_h

#include "Reactickle.h"
class Stickman: public Reactickle {
	
public:
	
	
	void setup();
	void update();
	void draw();

	bool needsKinect() { return true; }
};


#endif
