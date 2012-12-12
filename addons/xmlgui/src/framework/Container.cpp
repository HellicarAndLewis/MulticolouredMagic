/**
 * Container.cpp
 * emptyExample
 *
 * Created by Marek Bereza on 16/06/2011.
 *
 */

#include "Container.h"
#include "Gui.h"
#include "Instantiator.h"


xmlgui::Container::Container(): Control() {
	type = "container";
	parent = NULL;
	bgImage = NULL;
	layoutType = LayoutType_absolute;
	keyboardFocusedControl = NULL;
	focusedControl = NULL;
	opaque = false;

}

bool xmlgui::Container::isOpaque() {
	return opaque;
}
void xmlgui::Container::setOpaque(bool opaque) {
	if(this->opaque!=opaque) {
		this->opaque = opaque;
		deque<Control*>::iterator it;
		for(it = children.begin(); it != children.end(); it++) {
			if((*it)!=NULL && (*it)->isContainer()) {

				((xmlgui::Container*)(*it))->setOpaque(opaque);
			}
		}
	}
}

void xmlgui::Container::clear() {
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		if((*it)!=NULL) {
			delete (*it);
			(*it) = NULL;
		}
	}
	children.clear();
}
xmlgui::Container::~Container() {
	clear();
}
void xmlgui::Container::draw() {
	if(bgImage!=NULL) {
		bgImage->draw(x, y, width, height);

	}
	drawChildren();
}

void xmlgui::Container::setLayoutType(LayoutType layoutType) {
	this->layoutType = layoutType;

}
void xmlgui::Container::addChild(Control *child) {
	child->parent = this;
	if(layoutType==LayoutType_vertical) {
		if(children.size()>0) {
			child->x = children.back()->x;
			child->y = children.back()->y + children.back()->height + AUTO_LAYOUT_PADDING;
		}
	}
	//printf("Adding child %s, %d\n", child->name.c_str(), child->isContainer());
	children.push_back(child);
	if(child->isContainer()) {
		//printf("Cascading listeners to %s\n", child->name.c_str());
		for(int i = 0; i < listeners.size(); i++) {
			((Container*)child)->addListener(listeners[i]);
		}
	}
}

bool xmlgui::Container::removeChild(Control *child) {
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		if((*it)==child) {
			children.erase(it);
			if(child==keyboardFocusedControl) keyboardFocusedControl = NULL;
			return true;
		}
	}
	return false;
}


void xmlgui::Container::setKeyboardFocus(Control *keyboardFocusedControl) {


	if(parent!=NULL) { // propagate down
		parent->setKeyboardFocus(keyboardFocusedControl);

	} else { // we're the root so act upon it
		if(this->keyboardFocusedControl!=NULL) this->keyboardFocusedControl->focus = false;
		keyboardFocusedControl->focus = true;
		this->keyboardFocusedControl = keyboardFocusedControl;
	}
}

void xmlgui::Container::touchOver(int x, int y, int id) {
	x -= this->x;
	y -= this->y;
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		(*it)->over = (*it)->inside(x, y);
		(*it)->touchOver(x, y, id);
	}
}
void xmlgui::Container::notifyChange(xmlgui::Event *e) {

	for(int i = 0; i < listeners.size(); i++) {
		listeners[i]->controlChanged(e);
	}
}
bool xmlgui::Container::touchDown(int x, int y, int id) {
	x -= this->x;
	y -= this->y;
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		(*it)->over = (*it)->down = (*it)->inside(x, y);
		// if you're a container, pass the touch down, if you're a control only pass the touch down if you're in the box

		if(((*it)->isContainer() || (*it)->inside(x, y)) && (*it)->touchDown(x, y, id)) {
			focusedControl = (*it);
			xmlgui::Event e((*it), xmlgui::Event::TOUCH_DOWN);
			notifyChange(&e);

			return true;
		}
	}
	focusedControl = NULL;
	return false;
}

bool xmlgui::Container::touchMoved(int x, int y, int id) {
	x -= this->x;
	y -= this->y;


#ifdef XMLGUI_STICKY
	xmlgui::Control *c = focusedControl;
	if(c==NULL) {
		return false;
	} else {
		c->over = c->inside(x, y);
		c->down = true;
		if(c->touchMoved(x, y, id)) {
#else
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		xmlgui::Control *c = (*it);

		c->over = c->down = c->inside(x, y);
		if((c->isContainer() || c->inside(x, y)) && c->touchMoved(x, y, id)) {
#endif



			xmlgui::Event e(c, xmlgui::Event::TOUCH_MOVED);
			notifyChange(&e);

			return true;
		}
	}
			focusedControl = NULL;
	return false;
}



bool xmlgui::Container::touchUp(int x, int y, int id) {
	x -= this->x;
	y -= this->y;

#ifdef XMLGUI_STICKY
	xmlgui::Control *c = focusedControl;
	if(c==NULL) {
		return false;
	} else {
#else
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		xmlgui::Control *c = (*it);
#endif
		c->over = c->down = false;


#ifdef XMLGUI_STICKY
		if(c->touchUp(x, y, id)) {
#else
		if((c->isContainer() || c->inside(x, y)) && c->touchUp(x, y, id)) {
#endif
			xmlgui::Event e(c, xmlgui::Event::TOUCH_UP);
			notifyChange(&e);


			focusedControl = NULL;
			return true;
		}
	}
	return false;
}

void xmlgui::Container::drawChildren() {
	glPushMatrix();
	glTranslatef(x, y, 0);
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		(*it)->draw();
	}
	glPopMatrix();
}


xmlgui::Control *xmlgui::Container::hitTest(float x, float y) {
	x -= this->x;
	y -= this->y;
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		Control *hit = (*it)->hitTest(x, y);
		if(hit!=NULL) return hit;
	}
	// if no children hit-test successfully try this actual container
	if(inside(x+this->x, y+this->y)) return this;
	return NULL;
}

void xmlgui::Container::saveToXmlObject(ofxXmlSettings &xml) {
	printf("Saving a %s with %d children\n", type.c_str(), children.size());
	// this adds a tag of name 'type'
	Control::saveToXmlObject(xml);
	int which = xml.getNumTags(type) - 1;
	xml.addAttribute(type, "bgImage", bgImageUrl, which);
	xml.pushTag(type, which);

	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		(*it)->saveToXmlObject(xml);
	}

}

void xmlgui::Container::saveToXml(string file) {
	ofxXmlSettings xml;
	saveToXmlObject(xml);
	xml.saveFile(file);
}
/*
void gui::Container::loadFromXml(string file) {
	ofxXmlSettingsHelper xml;
	xml.loadFile(file);
	x = xml.getAttribute(type, "x", 0, 0);
	y = xml.getAttribute(type, "y", 0, 0);
	width = xml.getAttribute(type, "width", 0, 0);
	height = xml.getAttribute(type, "height", 0, 0);
	name = xml.getAttribute(type, "name", "", 0);
	vector<ParameterInfo> parameterInfo;
	getParameterInfo(parameterInfo);
	for(int i = 0; i < parameterInfo.size(); i++) {

	}

	xml.pushTag(type);
	loadFromXmlObject(xml);

}*/

void xmlgui::Container::loadFromXmlObject(TiXmlElement *xml) {
	Control::loadFromXmlObject(xml);

	const char *_bgImageUrl = xml->Attribute("bgImage");
	if(_bgImageUrl!=NULL) {
		printf("Loading image\n");
		bgImageUrl = _bgImageUrl;
		bgImage = xmlgui::Resources::getImage(bgImageUrl);
		if(bgImage==NULL) printf("Image couldn't be loaded\n");
	}
	// now we've loaded this container, load the children
	TiXmlNode *childNode = xml->FirstChild();
	if(childNode!=NULL) {
		TiXmlElement *child = childNode->ToElement();
		for(child; child; child = child->NextSiblingElement()) {
			string tagName = child->ValueStr();
			Control *ctrl = INSTANTIATE(tagName);
			ctrl->loadFromXmlObject(child);
			addChild(ctrl);
		}
	}
}

bool xmlgui::Container::keyPressed(int key) {
	if(keyboardFocusedControl!=NULL) {
		return keyboardFocusedControl->keyPressed(key);
	} else {
		return false;
	}

	/*
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		if((*it)->keyPressed(key)) {
			return true;
		}
	}
	return false;
	 */
}
void xmlgui::Container::addListener(Listener *listener) {
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		if((*it)->isContainer()) {
			Container *c = (Container*)(*it);
			c->addListener(listener);
		}
	}
	listeners.push_back(listener);
}

xmlgui::Control *xmlgui::Container::getControlById(string id) {
	deque<Control*>::iterator it;
	for(it = children.begin(); it != children.end(); it++) {
		if((*it)->id==id) {
			return (*it);
		}
	}
	return NULL;
}

float xmlgui::Container::getFloat(string controlId) {
	return 0;
}
int xmlgui::Container::getInt(string controlId) {
	return 0;
}
bool xmlgui::Container::getBool(string controlId) {
	return 0;
}
string xmlgui::Container::getString(string controlId) {
	getControlById(controlId);
	return "";
}

int xmlgui::Container::getNumChildren() {
	return children.size();
}
xmlgui::Control *xmlgui::Container::getChild(int index) {
	return children[index];
}

void xmlgui::Container::pointToValue(string controlName, void *pointer) {
	xmlgui::Control *c = getControlById(controlName);
	if(c!=NULL) {
		c->pointToValue(pointer);
	}
}
