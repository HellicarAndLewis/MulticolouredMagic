/**
 * Pane.h
 * emptyExample
 *
 * Created by Marek Bereza on 05/07/2011.
 *
 */

#include "Container.h"
class Pane: public xmlgui::Container {
public:
	int bgColor;
	ofImage *bg;
	string bgImageUrl;
	int labelColor;
	bool drawingLabel;
	Pane(): Container() {
		bgColor = 0x002244;
		bg = NULL;
		drawingLabel = false;
		labelColor = 0;
	}

	void load() {
		bg = xmlgui::Resources::getImage(bgImageUrl);


		if(bg!=NULL) {
			scalable = false;
			width = bg->getWidth();
			height = bg->getHeight();
		}

	}


	void draw() {
		if(bg!=NULL) {
			bg->draw(x, y);
		} else {
			setRGBA(bgColor);
			ofRect(x, y, width, height);
		}
		Container::draw();


		if(drawingLabel) {
			setRGBA(labelColor);
			xmlgui::Resources::drawString(name, x+3, y+14);
		}
	}
	void getParameterInfo(vector<ParameterInfo> &params) {
		params.push_back(ParameterInfo("Colour", "bgColor", "colourpicker", &bgColor));
		params.push_back(ParameterInfo("Background Image", "bgImage", "file", &bgImageUrl));
		params.push_back(ParameterInfo("Show Label", "showLabel", "toggle", &drawingLabel));
		params.push_back(ParameterInfo("Label Colour", "labelColor", "colourpicker", &labelColor));
	}


};
