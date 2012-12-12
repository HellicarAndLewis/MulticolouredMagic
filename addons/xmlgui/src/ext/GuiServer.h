/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  GuiServer.h, created by Marek Bereza on 14/11/2012.
 */

#pragma once
#include "Container.h"
#include "ofxWebServer.h"
#include "ofxOsc.h"

namespace xmlgui {
	class GuiServer: public ofxWSRequestHandler {

	public:
		
		GuiServer();
		~GuiServer();
		
		void setup();
		void update();
		void addGui(xmlgui::Container *gui);
		void httpGet(string url);
		void httpPost(string url, char *data, int dataLength);
		
	private:
		ofxWebServer ws;
		ofxOscReceiver osc;
		vector<xmlgui::Container*> guis;
		bool started;
		
		void smoothChange(xmlgui::Control *c, float value);
		map<xmlgui::Control*, float> smoothControls;
		float getControlRange(xmlgui::Control *c);
	};
}
