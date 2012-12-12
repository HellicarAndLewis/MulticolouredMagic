/**
 * RootContainer.h
 * emptyExample
 *
 * This is, like, the root container of the gui, dude.
 * It's also the bootstrap of the dynamic instantiation
 * of the different types of gui control according to 
 * the corresponding tag name.
 * 
 * Created by Marek Bereza on 19/06/2011.
 *
 */

#pragma once
#include "Container.h"
#include "ofGuiEventDispatcher.h"
namespace xmlgui {
	class Gui: public Container, public ofGuiEventDispatcher {
	public:
		Gui();
		
		// this is like the gui bootstrap
		virtual bool loadFromXml(string file = "");
		void saveToXml(string file = "");
		Container *getRoot();
		void setRoot(Container *r);
		Control *getControlById(string ctrl);
	private:
		string fileName;
		ofGuiEventDispatcher eventDispatcher;
	protected:
		Container *root;
		
	};
};