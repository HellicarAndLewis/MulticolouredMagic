/*
 *  ofxWSRequestHandler.cpp
 *  webServerExample
 *
 *  Created by Marek Bereza on 27/03/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */


#include "ofxWSRequestHandler.h"

void ofxWSRequestHandler::httpResponse(string data) {
	mg_printf(conn, "%s",data.c_str());
}


void ofxWSRequestHandler::httpResponseData(char *data, int length) {
	mg_write(conn, (const void *)data, length);
}

void ofxWSRequestHandler::httpRedirect(string url) {
	// a bit hacky but have no internet right now, so this is good for now
	string refr = "<html><head><meta HTTP-EQUIV=\"REFRESH\" content=\"0; url=";
	refr += url + "\"></head></html>\r\n";
	httpResponse(refr);
}
/**
 * Returns the client's ip address
 */
string ofxWSRequestHandler::getIPAddress() {
	return ipAddress;
}

/**
 * gets a parameter from the request.
 */
string ofxWSRequestHandler::getRequestParameter(string name) {
	string result = "";
	int pos = query.find(name+"=");
	if(pos!=-1) {
		int end = query.find("&", pos);
		pos = pos + name.size() + 1;
		if(end!=-1) {
			result = query.substr(pos, end - pos);
		} else {
			result = query.substr(pos);
		}
	}
	return result;
}

map<string,string> ofxWSRequestHandler::getRequestParameters() {
	map<string,string> params;
	if(query!="") {
		vector<string> s = ofSplitString(query, "&");
		for(int i = 0; i < s.size(); i++) {
			
			vector<string> keyvalue = ofSplitString(s[i], "=");
			if(keyvalue.size()>1) {
				string key = keyvalue[0];
				string value = keyvalue[1];
				printf("%s = %s\n", key.c_str(), value.c_str());
				params[key] = value;
			} else {
				params[s[i]] = "";
			}
		}
	}
	return params;
	
}
/**
 * returns the query string from the request
 */
string ofxWSRequestHandler::getQuery() {
	return query;
}