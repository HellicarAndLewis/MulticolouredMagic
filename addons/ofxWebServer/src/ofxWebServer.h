#ifndef __OFXWEBSERVER__
#define __OFXWEBSERVER__

#include "ofMain.h"
#include "ofxWSRequestHandler.h"
#include "mongoose.h"

class ofxWebServer {
public:
	ofxWebServer();
	
	/**
	 * Starts a webserver that just serves up files
	 * with the root directory and port specified in
	 * the parameter. (root is relative to the data path)
	 */
	void start(string root = "./", int port = 8910);
	
	/**
	 * Stops the webserver
	 */
	void stop();
	
	/**
	 * To add custom actions to certain urls, you subclass
	 * ofxWSRequestHandler and pass it to this function, specifying
	 * the pattern you want to look for.
	 *
	 * e.g. addHandler("*", handler); 
	 * this would send all URL requests to the handler
	 * 
	 * e.g. addHandler("actions/*", handler);
	 * this would send any url beginning with actions/ to
	 * the handler.
	 */
	void addHandler(ofxWSRequestHandler *handler, string pattern);
	
	/** gets the IP address of this server */
	string getIPAddress();
	
private:
	struct mg_context *ctx;
};
#endif // __OFXWEBSERVER__
