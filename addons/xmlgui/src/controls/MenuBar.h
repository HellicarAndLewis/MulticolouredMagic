/**
 * MenuBar.h
 * emptyExample
 *
 * Created by Marek Bereza on 27/06/2011.
 *
 */
#include "Container.h"
#include "Menu.h"
class MenuBar: public xmlgui::Container {
public:
	MenuBar(): Container() {
		x = 0;
		y = 0;
		width = ofGetWidth();
		height = EDITOR_MENU_HEIGHT;
	}
	
	
	void addMenu(string name) {
		Menu *menu = new Menu();
		
		menu->name = menu->id = name;
		
		if(children.size()==0) {
			menu->x = 20; // a bit of padding for the first menu item
		} else {
			menu->x = children.back()->x + children.back()->width;
		}
		addChild(menu);
	}
	
	void addItem(string menuName, string name) {
		Menu *menu = (Menu*)getControlById(menuName);
		if(menu!=NULL) {
			menu->addItem(name);
		}
	}
	
	void draw() {
		width = ofGetWidth();
		ofSetHexColor(0xFFFFFF);
		ofRect(x, y, width, height);
		Container::draw();
	}
	void hideAllMenus() {
		
		deque<Control*>::iterator it;
		for(it = children.begin(); it != children.end(); it++) {
			((Menu*)(*it))->hide();
		}
	}
	
	void touchOver(int x, int y, int id) {
		Container::touchOver(x, y, id);		
	}
	
	bool touchDown(int x, int y, int id) {
		bool hitMenu = Container::touchDown(x, y, id);
		//if(!hitMenu) hideAllMenus();
		return hitMenu;
	}
};