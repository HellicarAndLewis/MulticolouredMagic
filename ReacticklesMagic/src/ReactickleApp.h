/**
 * ReactickleApp.h
 * ReacticklesMagic
 *
 * This holds all the core functionality of the app,
 * accessible anywhere in the app.
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "Reactickle.h"

class ReactickleApp: public ofxiPhoneApp {
public:
	virtual void launchReactickle(Reactickle *reactickle) = 0;
	static ReactickleApp *instance;
};