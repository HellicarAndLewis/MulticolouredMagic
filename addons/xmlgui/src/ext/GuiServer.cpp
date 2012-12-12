/**
 *  GuiServer.cpp
 *
 *  Created by Marek Bereza on 14/11/2012.
 */

#include "GuiServer.h"
#include "ofxXmlSettings.h"
#include "Slider.h"
#include "Panner.h"

xmlgui::GuiServer::GuiServer() {
	started = false;
}

xmlgui::GuiServer::~GuiServer() {
	if(started) {
		ws.stop();
	}
}
void xmlgui::GuiServer::setup() {
	started = true;
	ws.start();
	ws.addHandler(this, "*");
	osc.setup(12345);
}

void xmlgui::GuiServer::smoothChange(xmlgui::Control *c, float value) {
	smoothControls[c] = value;
}

float xmlgui::GuiServer::getControlRange(xmlgui::Control *c) {
	if(c->type=="slider") {
		Slider *s = (Slider*)c;
		return s->max - s->min;
	} else if(c->type=="panner") {
		Panner *p = (Panner*)c;
		return p->max - p->min;
		
	} else {
		printf("Asking for the range of something that isn't a slider or a panner in GuiServer!\n");
		return -1;
	}
}
void xmlgui::GuiServer::update() {
	ofxOscMessage m;
	while(osc.getNextMessage(&m)) {
		if(m.getAddress()=="/gui") {
			string name = m.getArgAsString(0);
			for(int i = 0; i < guis.size(); i++) {
				if(guis[i]->name==name) {
					
					xmlgui::Control *c = guis[i]->getControlById(m.getArgAsString(1));
					if(c!=NULL) {
						if(c->type=="slider" || c->type=="panner") {
							smoothChange(c, ofToFloat(m.getArgAsString(2)));
						} else {
							c->valueFromString(m.getArgAsString(2));
							xmlgui::Event e(c, xmlgui::Event::TOUCH_UP);
							c->parent->notifyChange(&e);
						}
					}
					break;
				}
			}
		}
	}
	
	float filter = 0.3;
	map<xmlgui::Control*, float>::iterator it = smoothControls.begin();
	while(it != smoothControls.end()) {
		xmlgui::Control *c = (*it).first;
		
		float f = c->getFloat() * filter + (*it).second * (1.f-filter);
		c->setValue(f);
		xmlgui::Event e(c, xmlgui::Event::TOUCH_UP);
		c->parent->notifyChange(&e);
		float diff = ABS(f - (*it).second);
		
		// we're pretty much there, so set it 
		if(diff/getControlRange(c)<0.01) {
			c->setValue((*it).second);
			xmlgui::Event e(c, xmlgui::Event::TOUCH_UP);
			c->parent->notifyChange(&e);
			smoothControls.erase(it++);
		} else {
			it++;
		}
		
	}
}

void xmlgui::GuiServer::addGui(xmlgui::Container *gui) {
	guis.push_back(gui);
}

void xmlgui::GuiServer::httpGet(string url) {
	printf("GET %s\n", url.c_str());
	if(url=="/") {
		
		ofxXmlSettings xml;
		xml.addTag("guis");
		xml.pushTag("guis");
		
		for(int i = 0; i < guis.size(); i++) {
		//	printf("%s\n", guis[i]->name.c_str());
			xml.addTag("gui");
			xml.setAttribute("gui", "name", guis[i]->name, i);
		}
		string xmlStr = "";
		xml.copyXmlToString(xmlStr);
		httpResponse("text/xml", xmlStr);
		return;
	} else {
		for(int i = 0; i < guis.size(); i++) {
			if(url.find(guis[i]->name)==1) {
				ofxXmlSettings xml;
				guis[i]->saveToXmlObject(xml);

				string xmlStr = "";
				xml.copyXmlToString(xmlStr);
				httpResponse("text/xml", xmlStr);
				return;
			}
		}
		ofxXmlSettings xml;
		xml.addTag("NotFound");
		string xmlStr = "";
		xml.copyXmlToString(xmlStr);
		httpResponse("text/xml", xmlStr);
		return;
	}
}

void xmlgui::GuiServer::httpPost(string url, char *data, int dataLength) {
	printf("POST %s\n", url.c_str());
}