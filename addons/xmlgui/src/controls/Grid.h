/*
 *  GuiGrid.h
 *  Gui
 *
 *  Created by Marek Bereza on 05/05/2010.
 *
 */
#include "Control.h"
#include "GridSequence.h"

class Grid: public xmlgui::Control {
public:
	int steps;
	int notes;
	int bgColor;
	int noteColor;
	int lineColor;

	bool adding;
	float position;
	string bgImgUrl;
	ofImage *bg;

	Grid(): Control() {
		position = 0;
		adding = true;
		notes = 7;
		steps = 16;
		width = 200;
		height = 100;
		lineColor = 0xFFFFFF;
		noteColor = 0xCC0000;
		bgColor = 0;
		bgImgUrl = "";
		bg = NULL;
		value = new GridSequence();
		((GridSequence*)value)->toggle(1,1,1);
	}

	void load() {
		bg = xmlgui::Resources::getImage(bgImgUrl);
		if(bg!=NULL) {
			scalable = false;
			width = bg->getWidth();
			height = bg->getHeight();
		}
	}

	void draw() {

		if(bg!=NULL) {
			ofSetHexColor(0xFFFFFF);
			bg->draw(x, y);
		} else {

			setRGBA(bgColor);
			ofRect(x, y, width, height);

			ofNoFill();
			setRGBA(lineColor);
			ofRect(x, y, width, height);
		}

		float cellHeight = (float)height/notes;
		float cellWidth = (float)width/steps;



		ofFill();
		setRGBA(noteColor);
		((GridSequence*)value)->rewind();
		Note *n;
		while((n = ((GridSequence*)value)->nextNote())!=NULL) {
			ofRect(x + cellWidth*n->step, y + cellHeight*n->note, cellWidth, cellHeight);
		}



		setRGBA(lineColor);
		for(int i = 1; i < notes; i++) {
			ofLine(x, y + cellHeight*i, x+width, y + cellHeight*i);
		}

		for(int i = 1; i < steps; i++) {
			ofLine(x + cellWidth*i, y, x + cellWidth*i, y +height);
		}
		ofLine(x+width*position, y, x+width*position, y*height);
		ofFill();

	}




	bool touchDown(int _x, int _y, int touchId) {

		float cellHeight = (float)height/notes;
		float cellWidth = (float)width/steps;
		int note = _y - y;
		note /= cellHeight;
		int step = _x - x;
		step /= cellWidth;

		if(note<notes && step<steps) {
			adding = ((GridSequence*)value)->toggle(note, step, 255);
		}
		return true;
	}

	bool touchMoved(int _x, int _y, int touchId) {
		float cellHeight = (float)height/notes;
		float cellWidth = (float)width/steps;
		int note = _y - y;
		note /= cellHeight;
		int step = _x - x;
		step /= cellWidth;
		if(note<notes && step<steps) {
			((GridSequence*)value)->set(note, step, 255, adding);
		}
		return true;
	}





	void getParameterInfo(vector<ParameterInfo> &params) {
		params.push_back(ParameterInfo("notes", "notes", "intfield", &notes));
		params.push_back(ParameterInfo("steps", "steps", "intfield", &steps));
		params.push_back(ParameterInfo("BG Color", "bgColor", "colourpicker", &bgColor));
		params.push_back(ParameterInfo("Line Color", "lineColor", "colourpicker", &lineColor));
		params.push_back(ParameterInfo("Note Color", "noteColor", "colourpicker", &noteColor));
		params.push_back(ParameterInfo("BG Image", "bg", "file", &bgImgUrl));
	}

	string valueToString() { return ((GridSequence*)value)->valueToString(); }
	void valueFromString(string inp) {
		if(value!=NULL) delete ((GridSequence*)value);
		value = new GridSequence();
		((GridSequence*)value)->valueFromString(inp);

	}

};
