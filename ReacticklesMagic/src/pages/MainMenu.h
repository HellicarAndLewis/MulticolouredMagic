/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * MainMenu.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */
#include "Reactickle.h"
#include "InteractiveObject.h"
#include "ReactickleButton.h"
#include "SimpleButton.h"
#include "ImageObject.h"
class MainMenu: public Reactickle, public ReactickleButtonListener, public SimpleButtonListener {
public:
	void setup();
	void draw();
	
	
	// this is a subset of items - just the ones that are listed
	// as reactickles
	vector<ReactickleButton*> reactickleButtons;
	void initMenu();
	bool touchDown(float x, float y, int touchId);
	bool touchMoved(float x, float y, int touchId);
	bool touchUp(float x, float y, int touchId);
	void reactickleSelected(string name);
	void buttonPressed(string name);
private:
	void arrange();
	
	// the scrolling reactickles area
	ofRectangle scrollRect;
	
	// how much we're scrolled away from zero
	float scrollOffset;
	
	// scrolling touch stuff
	bool touching;
	float touchX;
	float deltaX;
	float totalWidth;
	
	SimpleButton settingsButton;
	SimpleButton aboutButton;
	ImageObject bgImage;
	ImageObject logo;
};