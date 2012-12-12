/**
 * LabeledControl.h
 * PdGui
 *
 * Created by Marek Bereza on 06/07/2011.
 *
 */
#include "Container.h"

#pragma once
class LabeledControl: public xmlgui::Control {
public:
	LabeledControl(): Control() {
		labelColor = 0xFFFFFF;
		drawingLabel = true;

	}
	void drawLabel(float x = -1, float y = -1) {
		if(drawingLabel) {
			if(x==-1) {
				x = this->x;
				y = this->y;
			}
			setRGBA(labelColor);
			xmlgui::Resources::drawString(name, x, y);
		}
	}

	void drawCustomLabel(string label, float x, float y) {
		if(drawingLabel) {
			if(parent->isOpaque()) {
				ofSetColor(0, 0, 0, 150);
				ofRect( x, y-10, width, 14);
			}
			setRGBA(labelColor);
			xmlgui::Resources::drawString(label, x, y);

		}
	}


	void getParameterInfo(vector<ParameterInfo> &params) {
		params.push_back(ParameterInfo("Draw Label", "drawlabel", "toggle", &drawingLabel));
		params.push_back(ParameterInfo("Label Color", "labelColor", "colourpicker", &labelColor));
	}

	bool drawingLabel;
	int labelColor;
};
