/**
 * RootContainer.h
 * emptyExample
 *
 * Created by Marek Bereza on 16/06/2011.
 *
 */

#pragma once


#include "Container.h"

namespace xmlgui {
	class ofGuiEventDispatcher {
	public:
		ofGuiEventDispatcher();
		void setup(xmlgui::Container *root);
		
		void enableEvents();
		void disableEvents();
		
		void enableInteraction();
		void disableInteraction();
		
		bool isEnabled();
		void setEnabled(bool enabled);
		
		void draw(ofEventArgs &e);	
		
		void mousePressed(ofMouseEventArgs &e);
		void mouseMoved(ofMouseEventArgs &e);	
		void mouseDragged(ofMouseEventArgs &e);
		void mouseReleased(ofMouseEventArgs &e);
		
		void keyPressed(ofKeyEventArgs &e);
		void keyReleased(ofKeyEventArgs &e);
		
		void touchDown(ofTouchEventArgs &e);
		void touchMoved(ofTouchEventArgs &e);
		void touchUp(ofTouchEventArgs &e);
	private:
		xmlgui::Container *root;
		bool enabled;
	};
};
