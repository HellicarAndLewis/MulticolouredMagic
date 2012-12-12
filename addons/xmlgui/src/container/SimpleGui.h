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
#include "Title.h"
#include "Spinner.h"



//#include "SliderBank.h"


//#define SIMPLE_GUI_WIDTH 150

namespace xmlgui {

	class SimpleGui: public xmlgui::Container, public xmlgui::Listener {
	public:

		SimpleGui();


		virtual void setup();

		void setEnabled(bool enabled);
		// implement this method if you want to receive
		// control changed stuff in your superclass as
		// you can't implement an xmlgui::Listener
		virtual void ctrlChanged(xmlgui::Event *e) {

		}
		void controlChanged(xmlgui::Event *e);
		Title 		 	*addTitle(string title);
		RangeSlider		*addRangeSlider(string name, float *value, float min, float max);
		Drawable		*addDrawable(string name, ofBaseDraws &baseDraws);
		IntSlider		*addSlider(string name, int &value, int min, int max);
		Slider			*addSlider(string name, float &value, float min, float max);
		Slider2D		*addSlider2D(string name, float *value, float minX, float maxX, float minY, float maxY);
		HorizontalRule	*addHR();
		Meter			*addMeter(string name, float &value);
		Meter			*addMeter(string name, float &value, float min, float max);
		Panner			*addPanner(string name, float &value, float min, float max);
		Toggle			*addToggle(string name, bool &value);
		PushButton		*addPushButton(string name);
		SegmentedControl *addSegmented(string name, int &value, string options);
		SegmentedControl *addSegmented(string name, int &value, vector<string> options);
		List			*addList(string name, int &value, vector<string> options);
		
		
		Spinner			*addSpinner(string name, int &value, string options);
		Spinner			*addSpinner(string name, int &value, vector<string> options);

		IntField		*addIntField(string name, int &value);
		FloatField		*addFloatField(string name, float &value);
		TextField		*addTextField(string name, string &value);


		void saveSettings(string file = "");


		void loadSettings(string file);

		void columnCheck();
		void addColumn() {
			mustAddNewColumn = true;
		}
		xmlgui::ofGuiEventDispatcher events;



		void toggle() {
			setEnabled(!enabled);
		}

		void setColumnWidth(float width) {
			setWidth(width);
		}

		// this must be called before adding controls!
		void setWidth(float width) {
			SIMPLE_GUI_WIDTH = width;
		}
		float getColumnWidth() {
			return SIMPLE_GUI_WIDTH;
		}
		bool isEnabled() { return enabled; }

		void enableInteraction();
		void disableInteraction();
	private:
		bool enabled;
		bool mustAddNewColumn;
		bool isSetup;
		string settingsFile;
		float SIMPLE_GUI_WIDTH;
	};
};
