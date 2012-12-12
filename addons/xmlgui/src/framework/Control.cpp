/**
 * Control.cpp
 * emptyExample
 *
 * Created by Marek Bereza on 16/06/2011.
 *
 */

#include "Control.h"
#include "Container.h"
#include "Instantiator.h"

xmlgui::Control::Control() {
	type = "control";
	over = false;
	down = false;
	focus = false;
	scalable = true;
	value = NULL;
	width = 100;
	height = 20;
}

void xmlgui::Control::draw() {
	ofSetHexColor(0xFFFFFF);
	ofRect(*this);

}
xmlgui::Control *xmlgui::Control::hitTest(float x, float y) {
	if(inside(x, y)) {
		return this;
	} else {
		return NULL;
	}
}

void xmlgui::Control::saveToXmlObject(ofxXmlSettings &xml) {

	// create tag,
	xml.addTag(type);

	// know which tag we are in case there's multiples
	int which = xml.getNumTags(type) - 1;
	xml.addAttribute(type, "name", name, which);
	xml.addAttribute(type, "id", id, which);
	xml.addAttribute(type, "x", x, which);
	xml.addAttribute(type, "y", y, which);
	xml.addAttribute(type, "width", width, which);
	xml.addAttribute(type, "height", height, which);

	vector<ParameterInfo> parameterInfo;
	getParameterInfo(parameterInfo);
	for(int i = 0; i < parameterInfo.size(); i++) {
		Control *c = INSTANTIATE(parameterInfo[i].type);
		c->pointToValue(parameterInfo[i].value);
		xml.addAttribute(type, parameterInfo[i].xmlName, c->valueToString(), which);
		delete c;
	}
}

void xmlgui::Control::loadFromXmlObject(TiXmlElement *xml) {

	// take all the base settings from this element
	name = xml->Attribute("name");
	id = xml->Attribute("id");
	xml->QueryFloatAttribute("x", &x);
	xml->QueryFloatAttribute("y", &y);
	xml->QueryFloatAttribute("width", &width);
	xml->QueryFloatAttribute("height", &height);
	// then take all the "parameterinfo" from it

	vector<ParameterInfo> parameterInfo;
	getParameterInfo(parameterInfo);

	//printf("Got %d params in %s\n", parameterInfo.size(), name.c_str());
	for(int i = 0; i < parameterInfo.size(); i++) {
		//printf("Param: %s\n", parameterInfo[i].name.c_str());
		//printf("Type: %s\n", parameterInfo[i].type.c_str());
		Control *c = INSTANTIATE(parameterInfo[i].type);
		c->pointToValue(parameterInfo[i].value);


		const char *vv = xml->Attribute(parameterInfo[i].xmlName.c_str());
		if(vv!=NULL) {
			string val = string(vv);
//			printf("val: %s\n", val.c_str());
			c->valueFromString(string(xml->Attribute(parameterInfo[i].xmlName.c_str())));
		} else {
			printf("No default value for %s in %s\n", parameterInfo[i].name.c_str(), name.c_str());
		}
		delete c;
	}

	load();

}
ofVec2f xmlgui::Control::getAbsolutePosition() {
	ofVec2f pos(x, y);
	Container *p = parent;
	while(p!=NULL) {
		pos += ofVec2f(p->x, p->y);
		p = p->parent;
	}
	return pos;
}

float *xmlgui::Control::getFloatArray() {
	return (float*)value;
}


float xmlgui::Control::getFloat() {
		return fval(value);
}
int xmlgui::Control::getInt() {
		return ival(value);
}
bool xmlgui::Control::getBool() {
	return bval(value);
}
string xmlgui::Control::getString() {
	return sval(value);
}


void xmlgui::Control::setValue(float val) {
	fval(value) = val;
}
void xmlgui::Control::setValue(bool val) {
	bval(value) = val;
}
void xmlgui::Control::setValue(int val) {
	ival(value) = val;
}
void xmlgui::Control::setValue(string value) {
	valueFromString(value);
}

xmlgui::Control *xmlgui::Control::clone() {

	Control *c = INSTANTIATE(type);

	c->name = name;
	c->id = id;
	c->x = x;
	c->y = y;
	c->width = width;
	c->height = height;


	// parentInfo and parameterInfo will be identical except
	// for the pointers

	vector<ParameterInfo> parameterInfo;
	c->getParameterInfo(parameterInfo);


	vector<ParameterInfo> parentInfo;
	getParameterInfo(parentInfo);

	// this is the parameter info for the cloned control
	for(int i = 0; i < parameterInfo.size(); i++) {

		// this writer writes to the pointer pointing into the
		// attribute of the cloned control
		Control *writer = INSTANTIATE(parameterInfo[i].type);
		writer->pointToValue(parameterInfo[i].value);


		Control *reader = INSTANTIATE(parentInfo[i].type);
		reader->pointToValue(parentInfo[i].value);

		writer->valueFromString(reader->valueToString());
		delete reader;
		delete writer;
	}
	c->load();
	return c;
}

void setRGBA(int colour) {
	int r = (0x00FF0000 & colour)>>16;
	int g = (0x0000FF00 & colour)>>8;
	int b = (0x000000FF & colour);
	int a = 0xFF - ((0xFF000000 & colour)>>24);
	ofSetColor(r, g, b, a);
}
xmlgui::Control *xmlgui::Control::position(float x, float y) {
	this->x = x;
	this->y = y;
	return this;
}
xmlgui::Control *xmlgui::Control::size(float width, float height) {
	this->width = width;
	this->height = height;
	return this;
}

xmlgui::Control::~Control() {
	//printf("Goodbye, '%s' - '%s'\n", name.c_str(), type.c_str());
}
