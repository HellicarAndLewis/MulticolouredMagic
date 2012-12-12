/**
 * Editor.h
 * emptyExample
 *
 * Created by Marek Bereza on 16/06/2011.
 *
 */
#include "Container.h"
#include "ofGuiEventDispatcher.h"
#include "MenuBar.h"
#include "Instantiator.h"
#include "Inspector.h"
#include "Gui.h"

namespace xmlgui {
	class Editor: public Container, public Listener {
	public:
		Editor();
		void controlChanged(Event *e);
		void setup(Gui *root);

		void setupMenus();
		void touchOver(int x, int y, int id);
		bool touchDown(int x, int y, int id);
		bool touchMoved(int x, int y, int id);
		bool touchUp(int x, int y, int id);
		bool keyPressed(int k);
		void draw();
		void setEnabled(bool enable);
		bool isEnabled();
	private:
		void deleteFocusedControl();
		bool enabled;
		bool resizing;
		Gui *root;
		Control *rolledOverControl;
		Control *focusedControl;
		ofVec2f lastMousePosition;
		ofGuiEventDispatcher eventDispatcher;
		MenuBar *menuBar;
		Inspector inspector;
		
		// this is what the aspect ratio of the control was before 
		// the user started scaling it.
		float initialAspect;
		ofVec2f initialPos;
	};
};