/*
 *  Properties.h
 *
 *
 *  Created by Marek Bereza on 22/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */
#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include <map>

/**
 *  \brief Simple wrapper for ofxXmlSettings, to write property lists.
 * 
 *  Use it like a hash map, then you can load and save it.
 * 
 *  The file format is xml, so easy on the eye when editing.
 */
class Properties {
public:
	
	/**
	 * Loads the file.
	 */
	void load(string path);	
	/**
	 * Saves the file. If you don't pass a parameter, it'll try to 
	 * save it to the last place it was loaded from.
	 */
	bool save(string path = "");	
	
	void set(string key, string value) {
		data[key] = value;
	}
	
	
	
	string get(string key, string defaultValue = "") {
		if(data.find(key)==data.end()) {
			data[key] = defaultValue;
			return defaultValue;
		}
		return data[key];
	}
	
	
	void set(string key, int value) {
		set(key, ofToString(value));
	}
	
	void set(string key, float value) {
		set(key, ofToString(value));
	}
	
	int getInt(string key, int defaultValue = 0) {
		return ofToInt(get(key, ofToString(defaultValue)));
	}
	
	float getFloat(string key, float defaultValue = 0) {
		return ofToFloat(get(key, ofToString(defaultValue)));
	}
	string toString() {
		string line, buf;
		ifstream InFile( xmlFilePath.c_str() );
		while(getline(InFile,line))
			buf += line;
		return buf;
	}
	
	void getPropertyKeys(vector<string> &keysOut);
	
private:
	string xmlFilePath;
	map<string,string> data;
	
};