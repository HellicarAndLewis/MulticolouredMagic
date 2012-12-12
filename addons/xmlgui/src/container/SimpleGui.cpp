/**
 *  SimpleGui.cpp
 *
 *  Created by Marek Bereza on 13/11/2012.
 */

#include "SimpleGui.h"
#pragma once
#include "Container.h"
#include "Instantiator.h"
#include "Slider.h"
#include "Toggle.h"
#include "SegmentedControl.h"
#include "List.h"
#include "PushButton.h"
#include "ofGuiEventDispatcher.h"
#include "Drawable.h"
#include "Panner.h"
#include "IntSlider.h"
#include "Meter.h"
#include "Slider2D.h"
#include "TextField.h"
#include "IntField.h"
#include "HorizontalRule.h"
#include "RangeSlider.h"
#include "FloatField.h"


//#include "SliderBank.h"


//#define SIMPLE_GUI_WIDTH 150

namespace xmlgui {


	SimpleGui::SimpleGui(): xmlgui::Container() {
		addListener(this);
		setLayoutType(xmlgui::LayoutType_vertical);
		x = 10;
		y = 20;
		mustAddNewColumn = false;
		isSetup = false;
		SIMPLE_GUI_WIDTH = 150;
	}

	void SimpleGui::setup() {
		events.setup(this);
		isSetup = true;
		enabled = false;
		setEnabled(true);
		setEnabled(false);
	}

	void SimpleGui::setEnabled(bool enabled) {
		if(!isSetup) this->setup();
		if(this->enabled!=enabled) {
			events.setEnabled(enabled);
			this->enabled = enabled;
		}
	}


	void SimpleGui::controlChanged(xmlgui::Event *e) {
		this->ctrlChanged(e);
		if(settingsFile!="") {
			saveSettings();
		}
	}

	Title *SimpleGui::addTitle(string title) {
		Title *t = (Title*) INSTANTIATE_WITH_ID("title", title);
		addChild(t);
		columnCheck();
		return t;
	}

	RangeSlider *SimpleGui::addRangeSlider(string name, float *value, float min, float max) {
		RangeSlider *r = (RangeSlider*)INSTANTIATE_WITH_ID("rangeslider", name);
		r->pointToValue(value);
		r->min = min;
		r->max = max;
		addChild(r);
		columnCheck();
		return r;
	}


	Drawable *SimpleGui::addDrawable(string name, ofBaseDraws &baseDraws) {
		Drawable *drawable = (Drawable*)INSTANTIATE_WITH_ID("drawable", name);
		drawable->drawable = &baseDraws;
		drawable->width = SIMPLE_GUI_WIDTH;
		drawable->height = baseDraws.getHeight()*SIMPLE_GUI_WIDTH/baseDraws.getWidth();
		addChild(drawable);
		columnCheck();
		return drawable;

	}
	IntSlider *SimpleGui::addSlider(string name, int &value, int min, int max) {
		IntSlider *slider = (IntSlider*)INSTANTIATE_WITH_ID("intslider", name);
		slider->pointToValue(&value);
		slider->min = min;
		slider->max = max;
		slider->width = SIMPLE_GUI_WIDTH;
		slider->showValue = true;
		addChild(slider);
		columnCheck();
		return slider;

	}
	Slider *SimpleGui::addSlider(string name, float &value, float min, float max) {
		Slider *slider = (Slider*)INSTANTIATE_WITH_ID("slider", name);
		slider->pointToValue(&value);
		slider->min = min;
		slider->max = max;
		slider->width = SIMPLE_GUI_WIDTH;
		slider->showValue = true;
		addChild(slider);
		columnCheck();
		return slider;

	}


	Slider2D *SimpleGui::addSlider2D(string name, float *value, float minX, float maxX, float minY, float maxY) {
		Slider2D *s2d = (Slider2D*) INSTANTIATE_WITH_ID("slider2d", name);
		s2d->pointToValue(value);
		s2d->minX = minX;
		s2d->minY = minY;
		s2d->maxX = maxX;
		s2d->maxY = maxY;

		s2d->width = SIMPLE_GUI_WIDTH;
		s2d->height = SIMPLE_GUI_WIDTH;
		s2d->showValue = true;
		addChild(s2d);
		columnCheck();
		return s2d;

	}



	HorizontalRule *SimpleGui::addHR() {
		string dummy = ofToString(ofRandomuf());
		HorizontalRule *r = (HorizontalRule*)INSTANTIATE_WITH_ID("horizontalrule", dummy);
		r->width = SIMPLE_GUI_WIDTH;
		addChild(r);
		columnCheck();
		return r;
	}

	Meter *SimpleGui::addMeter(string name, float &value) {
		Meter *slider = (Meter*)INSTANTIATE_WITH_ID("meter", name);
		slider->pointToValue(&value);
		slider->width = SIMPLE_GUI_WIDTH;
		addChild(slider);
		columnCheck();
		return slider;

	}
	Meter *SimpleGui::addMeter(string name, float &value, float min, float max) {
		Meter *slider = (Meter*)INSTANTIATE_WITH_ID("meter", name);
		slider->pointToValue(&value);
		slider->min = min;
		slider->max = max;
		slider->width = SIMPLE_GUI_WIDTH;
		addChild(slider);
		columnCheck();
		return slider;

	}

	Panner *SimpleGui::addPanner(string name, float &value, float min, float max) {
		Panner *slider = (Panner*)INSTANTIATE_WITH_ID("panner", name);
		slider->min = min;
		slider->max = max;
		slider->width = SIMPLE_GUI_WIDTH;
		slider->pointToValue(&value);
		slider->showValue = true;
		addChild(slider);
		columnCheck();

		return slider;
	}

	Toggle *SimpleGui::addToggle(string name, bool &value) {
		Toggle *tog = (Toggle*)INSTANTIATE_WITH_ID("toggle", name);
		tog->pointToValue(&value);
		tog->width = tog->height; // make it square
		addChild(tog);
		columnCheck();
		return tog;
	}

	PushButton *SimpleGui::addPushButton(string name) {
		PushButton *tog = (PushButton*)INSTANTIATE_WITH_ID("pushbutton", name);
		tog->width = 80;
		tog->height = 20;
		addChild(tog);
		columnCheck();
		return tog;

	}
	SegmentedControl *SimpleGui::addSegmented(string name, int &value, string options) {
		SegmentedControl *seg = (SegmentedControl*)INSTANTIATE_WITH_ID("segmented", name);
		seg->pointToValue(&value);
		seg->width = SIMPLE_GUI_WIDTH;
		seg->options = options;
		seg->load();
		addChild(seg);
		columnCheck();
		return seg;
	}
	
	
	
	SegmentedControl *SimpleGui::addSegmented(string name, int &value, vector<string> options) {
		
		SegmentedControl *seg = (SegmentedControl*)INSTANTIATE_WITH_ID("segmented", name);
		seg->pointToValue(&value);
		seg->width = SIMPLE_GUI_WIDTH;
		seg->opts = options;
		addChild(seg);
		columnCheck();
		return seg;
	}
	
	
	
	Spinner *SimpleGui::addSpinner(string name, int &value, string options) {
		vector<string> opts = ofSplitString(options, "|");
		return addSpinner(name, value, opts);
	}
	
	
	
	Spinner *SimpleGui::addSpinner(string name, int &value, vector<string> options) {
		
		Spinner *seg = (Spinner*)INSTANTIATE_WITH_ID("spinner", name);
		seg->pointToValue(&value);
		seg->width = SIMPLE_GUI_WIDTH;
		seg->opts = options;
		addChild(seg);
		columnCheck();
		return seg;
	}
	
	

	List *SimpleGui::addList(string name, int &value, vector<string> options) {
		List *list = (List*)INSTANTIATE_WITH_ID("list", name);
		list->pointToValue(&value);
		list->items = options;
		list->width = SIMPLE_GUI_WIDTH;
		addChild(list);
		columnCheck();
		return list;
	}

	IntField *SimpleGui::addIntField(string name, int &value) {
		IntField *field = (IntField*)INSTANTIATE_WITH_ID("intfield", name);
		field->pointToValue(&value);
		field->width = SIMPLE_GUI_WIDTH;
		addChild(field);
		columnCheck();
		return field;
	}


	FloatField *SimpleGui::addFloatField(string name, float &value) {
		FloatField *field = (FloatField*)INSTANTIATE_WITH_ID("floatfield", name);
		field->pointToValue(&value);
		field->width = SIMPLE_GUI_WIDTH;

		addChild(field);
		columnCheck();
		return field;
	}



	TextField *SimpleGui::addTextField(string name, string &value) {
		TextField *field = (TextField*)INSTANTIATE_WITH_ID("textfield", name);
		field->pointToValue(&value);
		field->width = SIMPLE_GUI_WIDTH;
		addChild(field);
		columnCheck();
		return field;
	}


	void SimpleGui::saveSettings(string file) {
		if(file=="") {
			if(this->settingsFile=="") {
				ofLogError() << "No settings file specified, will not save gui settings";
				return;
			}
		} else {
			this->settingsFile = file;
		}
		ofxXmlSettings xml;
		xml.addTag("settings");
		xml.pushTag("settings");
		for(int i = 0; i < children.size(); i++) {
			xml.addTag("setting");
			xml.addAttribute("setting", "id", children[i]->id, i);
			xml.addAttribute("setting", "value", children[i]->valueToString(), i);
		}
		xml.saveFile(settingsFile);
	}


	void SimpleGui::loadSettings(string file) {
		this->settingsFile = file;
		ofxXmlSettings xml;
		xml.loadFile(file);

		xml.pushTag("settings");
		int numTags = xml.getNumTags("setting");
		for(int i = 0; i < numTags; i++) {
			string id = xml.getAttribute("setting", "id", "", i);
			string value = xml.getAttribute("setting", "value", "", i);
			xmlgui::Control *c = getControlById(id);
			if(c!=NULL) {
				c->valueFromString(value);
			} else {

				ofLogError() << "Could not find control named '" << id << "'";
			}

		}
	}

	void SimpleGui::columnCheck() {
		if(mustAddNewColumn) {
			// move the last added item onto a new column
			if(children.size()>0) {
				children.back()->y = 0;
				children.back()->x = children[children.size()-2]->x + SIMPLE_GUI_WIDTH + AUTO_LAYOUT_PADDING;
			}
			mustAddNewColumn = false;
		}
	}

	void SimpleGui::enableInteraction() {
		events.enableInteraction();
	}


	void SimpleGui::disableInteraction() {
		events.disableInteraction();
	}
}


