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
#include "ScrollView.h"
#include "Container.h"
class MainMenu: public Reactickle, public ReactickleButtonListener, public SimpleButtonListener, public Container {
public:
	void setup();
	void draw();
	
	
	void initMenu();


	void reactickleSelected(string name);
	void buttonPressed(string name);
private:
	ofImage bgImage;
	
	ScrollView scrollView;
	
	SimpleButton settingsButton;
	SimpleButton aboutButton;
};