/*
 *  ofxWSHandler.h
 *  webServerExample
 *
 *  Created by Marek Bereza on 27/03/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "ofMain.h"
#include "mongoose.h"

class ofxWSRequestHandler {
public:
	/** Implement these methods in your handler to respond to */
	virtual void httpGet(string url) {}
	virtual void httpPost(string url, char *data, int dataLength) {}
	
	
protected:
	

	/** 
	 * if you want to write a string back
	 * to the user in a httpGet or httpPost, 
	 * use this method.
	 */
	void httpResponse(string data);
	
	/**
	 * Use this in your httpGet/Post to redirect the user afterwards
	 */
	void httpRedirect(string url);
	
	/**
	 * If you want to write raw data to the response, use this.
	 */
	void httpResponseData(char *data, int length);
	
	/**
	 * Returns the client's ip address
	 */
	string getIPAddress();
	
	/**
	 * gets a parameter from the request.
	 */
	string getRequestParameter(string name);

	/**
	 * Gets all the parameters at once, in a map
	 */
	map<string,string> getRequestParameters();
	
	/**
	 * returns the query string from the request
	 */
	string getQuery();
	
	
	
private:
	struct mg_connection *conn;
	string ipAddress;
	string query;
public:
	// internal workings, please ignore.
	void setConnection(struct mg_connection *_conn, string ip, string q) {conn = _conn; ipAddress = ip; query = q;}
};