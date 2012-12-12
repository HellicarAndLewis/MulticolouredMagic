/**
 * Settings.cpp
 * Somantics
 *
 * Created by Marek Bereza on 06/06/2011.
 *
 */

#include "Properties.h"
#include "Settings.h"
#include "constants.h"
#ifdef TARGET_OF_IPHONE
#include "ofxiPhoneExtras.h"
#else
#include "util.h"
#endif
Settings::Settings() {
#ifdef TARGET_OF_IPHONE
	path = ofxiPhoneGetDocumentsDirectory() + "/settings.xml";
#else
	path = getPreferencesDirectory(APP_NAME);
	path += "/settings.xml";// ofToDataPath("settings.xml", true);
#endif
	setDefaultValues();
	load();
}

void Settings::setDefaultValues() {
	settings["brightness"] = 1;
	settings["fgColor"] = 1;
	settings["bgColor"] = 2;
	settings["volume"] = 0.5;
}

void Settings::reset() {
	// default values
	setDefaultValues();
	save();

}

void Settings::save() {

	Properties p;

	map<string,float>::iterator it;
	for ( it=settings.begin() ; it != settings.end(); it++ ) {
		p.set((*it).first, (*it).second);
	}
	p.save(path);
	//printf("Saved to %s\n", path.c_str());
}
void Settings::load() {
	Properties p;
	p.load(path);
	vector<string> keys;
	p.getPropertyKeys(keys);
	for(int i = 0; i < keys.size(); i++) {
		settings[keys[i]] = p.getFloat(keys[i]);
	}

}
