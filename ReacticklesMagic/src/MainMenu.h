/**
 * MainMenu.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */
#include "TTApp.h"
#include "InteractiveObject.h"
#include "ReactickleButton.h"
class MainMenu: public TTApp {
public:
	void setup();
	void draw();
	
	// this is a list of all the things that can be interacted with
	vector<InteractiveObject*> items;
	
	// this is a subset of items - just the ones that are listed
	// as reactickles
	vector<ReactickleButton*> reactickleButtons;
	
	void touchDown(float x, float y, int touchId);
	void touchMoved(float x, float y, int touchId);
	void touchUp(float x, float y, int touchId);
	
private:
	void arrange();
	
	// the scrolling reactickles area
	ofRectangle scrollRect;
	
	// how much we're scrolled away from zero
	float scrollOffset;
	
	// scrolling touch stuff
	bool touching;
	float touchY;
	float deltaY;
	float totalHeight;
};