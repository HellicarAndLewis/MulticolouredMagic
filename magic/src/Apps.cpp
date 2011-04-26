/*
 *  Apps.cpp
 *  audioInputExample
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */


#include "MagicApp.h"
#include "ExampleApp.h"
#include "01JGLCircleGetsBigger.h"
#include "02JGLGridOfSquaresToCircles.h"
#include "03JGLColourChangeOnNoise.h"
#include "ClapBang.h"
#include "AudioBalloonApp.h"
#include "Circles2D.h"
#include "ClapClock.h"
#include "CircleSwarm.h"
#include "Inversion.h"
#include "Expander.h"

void MagicApp::initApps() {
	// add your app here
	apps.push_back(new Expander());
	apps.push_back(new ClapClock());
	apps.push_back(new Inversion());
	apps.push_back(new CircleSwarm());

	apps.push_back(new Circles2D());
	apps.push_back(new GridOfSquaresApp());
	apps.push_back(new ClapBang());
	apps.push_back(new ColourChangeOnNoiseApp());
	apps.push_back(new CircleBiggerApp());
}