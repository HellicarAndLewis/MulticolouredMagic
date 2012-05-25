//
//  Stickman.cpp
//  Somability
//
//  Created by Marek Bereza on 24/05/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Stickman.h"
#include "Skeletons.h"
#include "constants.h"

void Stickman::setup() {
	
}
void Stickman::update() {
	
}

void Stickman::draw() {
	glPushMatrix();
	glScalef((float)WIDTH/640.f, (float)HEIGHT/480.f, 1);
	for(int i = 0; i < Skeletons::getInstance().size(); i++) {
		ofxOpenNIUser &user = Skeletons::getInstance().getUser(i);
		user.drawSkeleton();
	}
	glPopMatrix();
//	printf("%d skelingtons\n", Skeletons::getInstance().size());
}
