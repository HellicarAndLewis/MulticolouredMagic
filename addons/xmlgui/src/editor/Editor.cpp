/**
 * Editor.cpp
 * emptyExample
 *
 * Created by Marek Bereza on 16/06/2011.
 *
 */

#include "Editor.h"
#ifdef TARGET_OF_OSX
#include "ofxMacKeys.h"
#endif
xmlgui::Editor::Editor(): Container() {
	enabled = false;
	resizing = false;
	focusedControl = NULL;
	rolledOverControl = NULL;
	addListener(this);
}
void xmlgui::Editor::controlChanged(Event *e) {
	string n = e->control->id.c_str();
	if(n.find("new ")==0) {
		string ctrlType = n.substr(4);
		Control *ctrl = INSTANTIATE(ctrlType);
		ctrl->x = 100;
		ctrl->y = 100;
		Control *con = root->getRoot();
		if(con!=NULL) {
			((Container*)con)->addChild(ctrl);
		} else {
			root->addChild(ctrl);
		}

	} else if(n=="Save") {
		root->getRoot()->saveToXml("gui.xml");
	} else if(n=="Save As...") {
		ofFileDialogResult result = ofSystemSaveDialog("default.xml", "Save As...");
		if(result.bSuccess) {
			root->getRoot()->saveToXml(result.filePath);
		}

	} else if(n=="Delete") {

		deleteFocusedControl();


	} else if(n=="Duplicate") {
		if(focusedControl != NULL && focusedControl->parent!=NULL) {
			Control *newControl = focusedControl->clone();
			newControl->x += 10;
			newControl->y += 10;
			newControl->id += "1";
			focusedControl->parent->addChild(newControl);
			focusedControl = newControl;
		}
	}
}
void xmlgui::Editor::deleteFocusedControl() {
	if(focusedControl != NULL && focusedControl->parent!=NULL) {
		focusedControl->parent->removeChild(focusedControl);
		if(focusedControl==rolledOverControl) {
			rolledOverControl = NULL;
		}

		// let the inspector know we're deleting a control in case
		// its gui is pointing to it.
		inspector.setControl(NULL);
		delete focusedControl;
		focusedControl = NULL;
	}
}
void xmlgui::Editor::setup(Gui *root) {
	addChild(root);
	this->root = root;
	eventDispatcher.setup(this);

	setEnabled(true);
	setupMenus();
	addChild(&inspector);
}
/*
void gui::Editor::setupInspector() {
	inspector = new Inspector();
	addChild(inspector);
}*/
void xmlgui::Editor::setupMenus() {
	menuBar = (MenuBar*)INSTANTIATE("menubar");

	menuBar->addMenu("File");
	menuBar->addItem("File", "Save");
	menuBar->addItem("File", "Save As...");
	menuBar->addMenu("Edit");
	//menuBar->addItem("Edit", "Duplicate");
	menuBar->addItem("Edit", "Delete");
	menuBar->addItem("Edit", "Duplicate");

	menuBar->addMenu("Create");

	for(int i = 0; i < Instantiator::getInstance()->size(); i++) {
		menuBar->addItem("Create", string("new ") + Instantiator::getInstance()->at(i));
	}


	addChild(menuBar);
}


void xmlgui::Editor::setEnabled(bool enable) {
	this->enabled = enable;
	if(this->enabled) {
		eventDispatcher.enableEvents();
	} else {
		eventDispatcher.disableEvents();
	}
}

bool xmlgui::Editor::isEnabled() { return enabled; }

bool xmlgui::Editor::keyPressed(int k) {
	if(Container::keyPressed(k)) return true;
	#ifdef TARGET_OF_OSX
	if(ofxMacCommandKeyDown()) {
		if(k=='s' || k=='S') {
			root->saveToXml("gui.xml");
		}
	}

	#endif
	if(k==OF_KEY_BACKSPACE) {
		deleteFocusedControl();
	}

	if(focusedControl!=NULL) {
		int increment = 1;

        #ifdef TARGET_OF_OSX
		if(ofxMacShiftKeyDown()) {
			increment = 10;
		}
		#endif

		if(k==OF_KEY_UP) {
			focusedControl->y -= increment;
		} else if(k==OF_KEY_DOWN) {
			focusedControl->y += increment;
		} else if(k==OF_KEY_LEFT) {
			focusedControl->x -= increment;
		} else if(k==OF_KEY_RIGHT) {
			focusedControl->x += increment;
		}
	}

}

void xmlgui::Editor::touchOver(int x, int y, int id) {
	menuBar->touchOver(x, y,id);
	inspector.touchOver(x, y,id);
	Control *ctrl = root->hitTest(x, y);

	if(ctrl!=NULL) {
		rolledOverControl = ctrl;
		ofVec2f pos = ctrl->getAbsolutePosition();
		// find out if the mouse is over the bottom right hand corner

		// bottom right
		pos += ofVec2f(ctrl->width, ctrl->height);
		pos -= ofVec2f(x, y);
		if(pos.x<5 && pos.y<5) {
			printf("Corner\n");
		}

	} else {
		rolledOverControl = NULL;
	}
}


bool xmlgui::Editor::touchDown(int x, int y, int id) {

	if(menuBar->touchDown(x, y,id)) return true;
	if(inspector.touchDown(x, y,id)) return true;
	rolledOverControl = NULL;
	Control *ctrl = root->hitTest(x, y);
	focusedControl = ctrl;
	if(focusedControl!=NULL) {
		printf("Hit control: %s\n", ctrl->id.c_str());
		inspector.setControl(focusedControl);
		lastMousePosition = ofVec2f(x, y);


		ofVec2f pos = focusedControl->getAbsolutePosition();
		// find out if the mouse is over the bottom right hand corner

		// bottom right
		pos += ofVec2f(focusedControl->width, focusedControl->height);
		pos -= ofVec2f(x, y);
		if(focusedControl->scalable && pos.x<5 && pos.y<5) {
			resizing = true;
			initialAspect = focusedControl->width/focusedControl->height;
		} else {
			initialPos = focusedControl->getAbsolutePosition();
			resizing = false;
			#ifdef TARGET_OF_OSX
			if(ofxMacAltKeyDown()) {
				if(focusedControl != NULL && focusedControl->parent!=NULL) {
					Control *newControl = focusedControl->clone();
					//newControl->x += 10;
					//newControl->y += 10;
					newControl->id += "1";
					focusedControl->parent->addChild(newControl);
					focusedControl = newControl;
					inspector.setControl(focusedControl);
				}
			}
			#endif
		}

	}
	return false;
}

bool xmlgui::Editor::touchMoved(int x, int y, int id) {
	if(menuBar->touchMoved(x, y,id)) return true;
	if(inspector.touchMoved(x, y,id)) return true;
	// do dragging
	if(focusedControl!=NULL) {
		ofVec2f delta = ofVec2f(x, y) - lastMousePosition;
		if(resizing) {

			focusedControl->width += delta.x;
#ifdef TARGET_OF_OSX
			if(ofxMacShiftKeyDown()) {
				focusedControl->height = focusedControl->width/initialAspect;
			} else {

#endif
				focusedControl->height += delta.y;


#ifdef TARGET_OF_OSX
			}
#endif
		} else {
#ifdef TARGET_OF_OSX
			if(ofxMacShiftKeyDown()) {
				if(ABS(initialPos.x - focusedControl->x) > ABS(initialPos.y - focusedControl->y)) {
					// snap to x axis
					focusedControl->x += delta.x;
					focusedControl->y = initialPos.y;
				} else {

					// snap to y axis
					focusedControl->x = initialPos.x;
					focusedControl->y += delta.y;
				}

			} else {
#endif
				focusedControl->x += delta.x;
				focusedControl->y += delta.y;
#ifdef TARGET_OF_OSX
			}
#endif
		}
		lastMousePosition = ofVec2f(x, y);

	}
	return false;
}
bool xmlgui::Editor::touchUp(int x, int y, int id) {
	if(menuBar->touchUp(x, y,id)) return true;
	if(inspector.touchUp(x, y,id)) return true;
	return false;
}

void xmlgui::Editor::draw() {
	Container::draw();
	if(focusedControl!=NULL) {
		ofNoFill();
		ofSetHexColor(0xFFFFFF);
		ofVec2f pos = focusedControl->getAbsolutePosition();
		ofRect(pos.x, pos.y, focusedControl->width, focusedControl->height);
		ofFill();
	}

	if(rolledOverControl!=NULL) {
		ofSetHexColor(0xFFFFFF);
		ofVec2f pos = rolledOverControl->getAbsolutePosition();
		ofRect(pos.x + rolledOverControl->width-5, pos.y+rolledOverControl->height-5, 5, 5);

		ofSetHexColor(0x002244);
		ofRect(0, ofGetHeight()-20, ofGetWidth(), 20);
		string path = "";
		Control *c = rolledOverControl;
		while(c!=NULL && c->parent!=NULL && c->parent->parent!=NULL) {
			if(path!="") path = "  >>  " + path;
			string idStr = "";
			if(c->id!="") idStr = "['" +c->id+ "']";
			path = c->type + idStr + path;
			c = c->parent;
		}
		ofSetHexColor(0xFFFFFF);
		xmlgui::Resources::drawString(path, 3, ofGetHeight()-4);
	}
}
