/**
 * Gui.cpp
 * emptyExample
 *
 * Created by Marek Bereza on 19/06/2011.
 *
 */
#include "Gui.h"
#include "ofxXmlSettings.h"
#include "Instantiator.h"
xmlgui::Gui::Gui(): xmlgui::Container() {
	root = NULL;
}
bool xmlgui::Gui::loadFromXml(string file) {
	if(root!=NULL) {
		removeChild(root);
		delete root;
		root = NULL;
	}
	
	if(file=="") file = fileName;
	else fileName = file;

	TiXmlDocument doc(ofToDataPath(file));
	if(!doc.LoadFile()) return false;
	TiXmlElement* rootElement = doc.FirstChildElement()->ToElement();
	
	// find out what the root tag is
	string firstTagName = rootElement->Value();
	
	
	root = (Container*)INSTANTIATE(firstTagName);
	
	
	
	// this should recurse, calling createControl as it goes.
	root->loadFromXmlObject(rootElement);
	
	addChild(root);
	setup(root);
	return true;
}

void xmlgui::Gui::setRoot(xmlgui::Container *r) {
	this->root = r;
	addChild(root);
	setup(root);
}

xmlgui::Container *xmlgui::Gui::getRoot() {
	return root;
}

void xmlgui::Gui::saveToXml(string file) {
	//if(file=="") file = fileName;
	//else fileName = file;
	
	root->saveToXml(file);
/*
	if(children.size()>0) {
		if(children[0]->isContainer()) {
			printf("Saved first child to container\n");
			((Container*)children[0])->saveToXml(file);
		}
	}*/
//	Container::saveToXml(file);
}
xmlgui::Control *xmlgui::Gui::getControlById(string ctrl) {
	return root->getControlById(ctrl);
	
}