/**
 * Settings.cpp
 * Somantics
 *
 * Created by Marek Bereza on 06/06/2011.
 *
 */

#include "Properties.h"
#include "Settings.h"
#include "ofxiPhoneExtras.h"
Settings::Settings() {

	// default values
	settings["brightness"] = 0.5;
	settings["fgColor"] = 1;
	settings["bgColor"] = 2;
	
}


void Settings::save() {
	Properties p;
	
	map<string,float>::iterator it;
	for ( it=settings.begin() ; it != settings.end(); it++ ) {
		p.set((*it).first, (*it).second);
	}
}
void Settings::load() {
	string path = ofxiPhoneGetDocumentsDirectory() + "/settings.xml";
	Properties p;
	p.load(path);
	vector<string> keys;
	p.getPropertyKeys(keys);
	for(int i = 0; i < keys.size(); i++) {
		settings[keys[i]] = p.getFloat(keys[i]);
	}
	
}