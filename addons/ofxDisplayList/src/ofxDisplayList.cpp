#include "ofxDisplayList.h"

ofxDisplayList::ofxDisplayList() {
//#pragma warning - I commented somehting out in ofxDisplaylist I shoulnd't have
	_id = glGenLists(1);
	_ready = false;
	_references = new int;
	(*_references) = 1;
}

ofxDisplayList::ofxDisplayList(const ofxDisplayList& list) {
	_id = list._id;
	_ready = list._ready;
	_references = list._references;
	(*_references)++;
}

ofxDisplayList::~ofxDisplayList() {
	(*_references)--;
	if(*_references == 0) {
		delete _references;
		glDeleteLists(_id, 1);
	}
}

bool ofxDisplayList::ready() const {
	return _ready;
}

void ofxDisplayList::update() {
	_ready = false;
}

void ofxDisplayList::begin(bool execute) {
	glNewList(_id, execute ? GL_COMPILE_AND_EXECUTE : GL_COMPILE);
}

void ofxDisplayList::end() {
	glEndList();
	_ready = true;
}

bool ofxDisplayList::draw() {
	if(!_ready)
		return false;
	glCallList(_id);
	return true;
}
