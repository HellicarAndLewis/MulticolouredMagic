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
 *  GuiOscSender.h, created by Marek Bereza on 15/11/2012.
 */

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "Container.h"
namespace xmlgui {
	class GuiOscSender: public xmlgui::Listener {
	public:

		void setup(xmlgui::Container *gui, string host, int port) {
			this->gui = gui;
			guiOsc.setup(host, port);
			this->gui->addListener(this);
		}

		void controlChanged(xmlgui::Event *e) {
			ofxOscMessage m;
			m.setAddress("/gui");
			m.addStringArg(gui->id);
			m.addStringArg(e->control->id);
			m.addStringArg(e->control->valueToString());
			guiOsc.sendMessage(m);
//			printf("Sent /gui %s %s %s\n", gui->id.c_str(), e->control->id.c_str(), e->control->valueToString().c_str());
		}

		ofxOscSender guiOsc;
		xmlgui::Container *gui;
	};
}
