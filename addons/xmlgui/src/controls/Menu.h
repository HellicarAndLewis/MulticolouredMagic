/**
 * Menu.h
 * emptyExample
 *
 * Created by Marek Bereza on 27/06/2011.
 *
 */
#pragma once
#include "Container.h"
#include "MenuItem.h"
#include "Resources.h"
#define EDITOR_MENU_HEIGHT 20
class Menu: public xmlgui::Container {
public:
	bool showing;
	vector<MenuItem*> items;
	Menu() {
		showing = false;
		x = 0;
		y = 0;
		width = 100;
		height = EDITOR_MENU_HEIGHT;
	}
	
	void addItem(string name) {
		MenuItem *item = new MenuItem();
		item->id = item->name = name;

		if(items.size()==0) {
			item->y = height;
		} else {
			item->y = items.back()->y + items.back()->height;
		}
		items.push_back(item);
	}
	
	void draw() {

		if(showing) {
			ofSetHexColor(0x4444CC);
			ofRect(x, y, width, height);
			ofSetHexColor(0xFFFFFF);
		} else {
			ofSetHexColor(0x000000);
		}
		xmlgui::Resources::drawString(name, x+3, y+14);
		
		// only draw children if they're there.
		Container::draw();

	}
	
	void show() {
		showing = true;
		for(int i = 0; i < items.size(); i++) {
			addChild(items[i]);
		}
		height = EDITOR_MENU_HEIGHT*(children.size()+1);

	}
	void hide() {
		showing = false;
		children.clear();
		height = EDITOR_MENU_HEIGHT;
	}
	
	void touchOver(int x, int y, int id) {
		Container::touchOver(x, y, id);
		if(showing && !inside(x, y)) hide();
	}
	
	bool touchUp(int x, int y, int id) {
		// see if we're in any of the childen. if so, action it and hide
		if(showing) {
			ofRectangle topOfMenuRect(x, y, width, EDITOR_MENU_HEIGHT);
			if(topOfMenuRect.inside(x, y)) {
				//hide();
			} else {
				x -= this->x;
				y -= this->y;

				deque<Control*>::iterator it;
				for(it = children.begin(); it != children.end(); it++) {
					if((*it)->touchUp(x, y, id)) {
						xmlgui::Event e((*it), xmlgui::Event::TOUCH_UP);
						for(int i = 0; i < listeners.size(); i++) {
							listeners[i]->controlChanged(&e);
						}
						hide();
						
						return true;
					} else {
						Control *c = (*it);
					}
				}
			}
		}
		return false;
	}

	bool touchDown(int x, int y, int id) {

		if(inside(x, y)) {
			if(!showing) {
				show();
			}
			return true;
		} else {
			hide();
			return false;
		}
	}
};