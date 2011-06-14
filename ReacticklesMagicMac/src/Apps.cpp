/*
 *  Apps.cpp
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */


#include "MagicApp.h"

#include "Expand.h"
#include "Orbit.h"
#include "Flip.h"
#include "Follow.h"
#include "Trail.h"
#include "Grid.h"
#include "Cascade.h"
#include "Change.h"
#include "Find.h"
#include "Trace.h"

void MagicApp::initApps() {
	// add your app here
	apps.push_back(new Expand());
    apps.push_back(new Orbit());
    apps.push_back(new Flip());
    apps.push_back(new Follow());
    apps.push_back(new Trail());
    apps.push_back(new Grid());
    apps.push_back(new Cascade());
    apps.push_back(new Change());
    apps.push_back(new Find());
    apps.push_back(new Trace());
}