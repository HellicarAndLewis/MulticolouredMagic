/**
 * SettingsPage.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */
#pragma once
#include "Reactickle.h"
#ifdef _WIN32
    #include "gui/ColorPicker.h"
#else
    #include "ColorPicker.h"
#endif

#include "SimpleButton.h"
#include "BrightnessSlider.h"
#include "ImageObject.h"
#include "CheckBox.h"
class SettingsPage: public Reactickle, public SimpleButtonListener {
public:
	void setup();
	void draw();
	void buttonPressed(string name);
	ColorPicker colorPicker;
	BrightnessSlider slider;

	ofImage *bgImage;

	ImageObject settingsTitle;
	ImageObject colourPickerTitle;
	ImageObject logo;
	/*

	ofImage *settingsTitle;
	ofImage *colourPickerTitle;
	ofImage *logo;
	 */
};
