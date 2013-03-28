/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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