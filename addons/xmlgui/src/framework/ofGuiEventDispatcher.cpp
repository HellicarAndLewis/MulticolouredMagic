/**
 * ofGuiEventDispatcher.cpp
 * emptyExample
 *
 * Created by Marek Bereza on 16/06/2011.
 *
 */

#include "ofGuiEventDispatcher.h"
#include "Container.h"
xmlgui::ofGuiEventDispatcher::ofGuiEventDispatcher() {
	this->enabled = false;
}

void xmlgui::ofGuiEventDispatcher::setup(Container *root) {
	this->root = root;
}
void xmlgui::ofGuiEventDispatcher::draw(ofEventArgs &e) {
	root->draw();
}


void xmlgui::ofGuiEventDispatcher::mousePressed(ofMouseEventArgs &e) {

	root->touchDown(e.x, e.y, e.button);
}

void xmlgui::ofGuiEventDispatcher::mouseMoved(ofMouseEventArgs &e) {
	root->touchOver(e.x, e.y, e.button);
}

void xmlgui::ofGuiEventDispatcher::mouseDragged(ofMouseEventArgs &e) {
	root->touchMoved(e.x, e.y, e.button);
}

void xmlgui::ofGuiEventDispatcher::mouseReleased(ofMouseEventArgs &e) {
	root->touchUp(e.x, e.y, e.button);
}

void xmlgui::ofGuiEventDispatcher::keyPressed(ofKeyEventArgs &e) {
	root->keyPressed(e.key);
}

void xmlgui::ofGuiEventDispatcher::keyReleased(ofKeyEventArgs &e) {
	root->keyReleased(e.key);
}


void xmlgui::ofGuiEventDispatcher::touchDown(ofTouchEventArgs &e) {
	root->touchDown(e.x, e.y, e.id);
}

void xmlgui::ofGuiEventDispatcher::touchMoved(ofTouchEventArgs &e) {
	root->touchMoved(e.x, e.y, e.id);
}

void xmlgui::ofGuiEventDispatcher::touchUp(ofTouchEventArgs &e) {
	root->touchUp(e.x, e.y, e.id);
}

void xmlgui::ofGuiEventDispatcher::enableInteraction() {
	ofAddListener(ofEvents().mousePressed, this, &xmlgui::ofGuiEventDispatcher::mousePressed);
	ofAddListener(ofEvents().mouseMoved, this, &xmlgui::ofGuiEventDispatcher::mouseMoved);
	ofAddListener(ofEvents().mouseDragged, this, &xmlgui::ofGuiEventDispatcher::mouseDragged);
	
	ofAddListener(ofEvents().touchDown, this, &xmlgui::ofGuiEventDispatcher::touchDown);
	ofAddListener(ofEvents().touchUp, this, &xmlgui::ofGuiEventDispatcher::touchUp);
	ofAddListener(ofEvents().touchMoved, this, &xmlgui::ofGuiEventDispatcher::touchMoved);
	
	ofAddListener(ofEvents().mouseReleased, this, &xmlgui::ofGuiEventDispatcher::mouseReleased);
	ofAddListener(ofEvents().keyPressed, this, &xmlgui::ofGuiEventDispatcher::keyPressed);
	ofAddListener(ofEvents().keyReleased, this, &xmlgui::ofGuiEventDispatcher::keyReleased);
}


void xmlgui::ofGuiEventDispatcher::enableEvents() {

	enableInteraction();
	
	ofAddListener(ofEvents().draw, this, &xmlgui::ofGuiEventDispatcher::draw);
	

	
}

void xmlgui::ofGuiEventDispatcher::disableInteraction() {
	ofRemoveListener(ofEvents().mousePressed, this, &xmlgui::ofGuiEventDispatcher::mousePressed);
	ofRemoveListener(ofEvents().mouseMoved, this, &xmlgui::ofGuiEventDispatcher::mouseMoved);
	ofRemoveListener(ofEvents().mouseDragged, this, &xmlgui::ofGuiEventDispatcher::mouseDragged);
	
	ofRemoveListener(ofEvents().touchDown, this, &xmlgui::ofGuiEventDispatcher::touchDown);
	ofRemoveListener(ofEvents().touchUp, this, &xmlgui::ofGuiEventDispatcher::touchUp);
	ofRemoveListener(ofEvents().touchMoved, this, &xmlgui::ofGuiEventDispatcher::touchMoved);
	
	ofRemoveListener(ofEvents().mouseReleased, this, &xmlgui::ofGuiEventDispatcher::mouseReleased);
	ofRemoveListener(ofEvents().keyPressed, this, &xmlgui::ofGuiEventDispatcher::keyPressed);
	ofRemoveListener(ofEvents().keyReleased, this, &xmlgui::ofGuiEventDispatcher::keyReleased);
}

void xmlgui::ofGuiEventDispatcher::disableEvents() {
	disableInteraction();
	ofRemoveListener(ofEvents().draw, this, &xmlgui::ofGuiEventDispatcher::draw);
	

}

bool xmlgui::ofGuiEventDispatcher::isEnabled() {
	return enabled;
}
void xmlgui::ofGuiEventDispatcher::setEnabled(bool enabled) {

	if(enabled!=this->enabled) {
		if(enabled) {
			enableEvents();
		} else {
			disableEvents();
		}
	}
	this->enabled = enabled;
}