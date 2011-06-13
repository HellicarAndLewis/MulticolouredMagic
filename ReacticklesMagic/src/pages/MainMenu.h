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