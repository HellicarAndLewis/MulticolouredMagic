#pragma once

#include "ofMain.h"

class ofxDisplayList {
protected:
	GLuint _id;
	bool _ready;
	int* _references;
public:
	ofxDisplayList();
	ofxDisplayList(const ofxDisplayList& list);
	~ofxDisplayList();
	bool ready() const;
	void update();
	void begin(bool execute = true);
	void end();
	bool draw();
};

// <3 kyle mcdonald
