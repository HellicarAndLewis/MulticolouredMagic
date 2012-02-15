/*
 *  Properties.cpp
 *
 *  Created by Marek Bereza on 25/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */


#include "Properties.h"
/**
 * Loads the file.
 */
void Properties::load(string path) {
	xmlFilePath = path;
	data.clear();
	ofxXmlSettings xml;
	xml.loadFile(xmlFilePath);
	
	xml.pushTag("properties");
	int numProps = xml.getNumTags("property");
	for(int i = 0; i < numProps; i++) {
		string key = xml.getAttribute("property", "key", "", i);
		string value = xml.getAttribute("property", "value", "", i);
		data[key] = value;
	}
}


/**
 * Saves the file. If you don't pass a parameter, it'll try to 
 * save it to the last place it was loaded from.
 */
bool Properties::save(string path) {
	if(path!="") xmlFilePath = path;
	if(xmlFilePath=="") {
		printf("Error, no xml file specified\n");
		return false;
	}
	
	ofxXmlSettings xml;
	xml.addTag("properties");
	xml.pushTag("properties");
	
	
	map<string,string>::iterator it;
	int i = 0;
	for ( it=data.begin() ; it != data.end(); it++ ) {
		xml.addTag("property");
		xml.setAttribute("property", "key", (*it).first, i);
		xml.setAttribute("property", "value", (*it).second, i);
		i++;
	}
	xml.saveFile(xmlFilePath);
	return true;
}

void Properties::getPropertyKeys(vector<string> &keysOut) {
	map<string,string>::iterator it;
	for ( it=data.begin() ; it != data.end(); it++ ) {
		keysOut.push_back((*it).first);
	}
}