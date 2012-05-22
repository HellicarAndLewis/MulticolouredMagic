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
#include "Container.h"
#include "ImageObject.h"

class MainMenu: public Reactickle, public ReactickleButtonListener, public SimpleButtonListener {
public:
	void setup();
	void draw();
	
	
	void initMenu();

	
	void addReactickleButton(ReactickleButton *reactickleButton);
	void reactickleSelected(string name);
	void buttonPressed(string name);
private:
	ofImage *bgImage;
	ImageObject logo;
	int reactickleButtonCount;
};