/**
 * Control.h
 * emptyExample
 *
 * Created by Marek Bereza on 16/06/2011.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

#include "ParameterInfo.h"
#include "Resources.h"
#define bval(A) (*((bool*)A))
#define ival(A) (*((int*)A))
#define fval(A) (*((float*)A))
#define dval(A) (*((double*)A))
#define faval(A, B) (*(((float*)A)+B))
#define sval(A) (*((string*)A))


namespace xmlgui {
	class Container;	
	class Control: public ofRectangle {
		
	public:
		virtual ~Control();
		// human readable name
		string name;
		
		// computer readable, no spaces, unique, preferably
		string id;
		
		// string type, as specified in Controls.cpp
		string type;
		
		
		// the parent control, or null if this is the root.
		Container *parent;
		
		
		// whether the mouse is over
		bool over;
		
		// whether the mouse is down
		bool down;
		
		// whether the control has focus
		bool focus;
		
		// whether the control should be scaleable, this will be false when using images
		bool scalable;
		
		// 
		ofVec2f getAbsolutePosition();
		
		// you can resize and position the control here,
		// it returns a reference to itself, so you can
		// chain the commands one after the other.
		Control *position(float x, float y);
		Control *size(float width, float height);
		
		Control();
		
		
		virtual void draw();
		
		
		// this is a temporary solution to 
		// load any assets based on setting that have 
		// been loaded with the custom settings. e.g.
		// images etc.
		virtual void load() {}

		
		
		virtual void touchOver(int x, int y, int id) { }
		virtual bool touchMoved(int x, int y, int id){ return inside(x, y); }
		virtual bool touchDown(int x, int y, int id){ return inside(x, y); }
		virtual bool touchUp(int x, int y, int id){ return inside(x, y); }
		virtual bool keyPressed(int key) { return false; }
		virtual bool keyReleased(int key) { return false; }
		virtual void getParameterInfo(vector<ParameterInfo> &parameterInfo) {}
		
		
		// this helps with the polymorphism, probably don't need to override it
		// if you're subclassing "Container" it sets it to true.
		virtual bool isContainer() { return false; };
		
		// this returns the control currently under (x,y) or null if there is none.
		virtual Control *hitTest(float x, float y);
		
		// stuff for saving to xml - don't use these directly
		virtual void saveToXmlObject(ofxXmlSettings &xml);
		virtual void loadFromXmlObject(TiXmlElement *xml);

	
		// todo: make protected and in the cpp file
		void maskOn(int _x, int _y, int _w, int _h) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(_x, ofGetHeight()-(_y+_h), _w, _h);
		}
		void maskOff() {
			glDisable(GL_SCISSOR_TEST);
		}
		
		void pointToValue(void *value) {
			
			// here's a nice memory leak
//			delete this->value;
			this->value = value;
		}
		
		
		// helpers for getting values out of the controls
		float getFloat();
		int getInt();
		bool getBool();
		string getString();
		
		float *getFloatArray();
		
		void setValue(float val);
		void setValue(bool val);
		void setValue(int val);
		void setValue(string value);
		
		// you should override this if you want your gui control to be saveable
		virtual string valueToString() {return "";}
		virtual void   valueFromString(string valStr) {}
		
		
		// this clones an existing control
		Control *clone();
		
	protected:
		void *value;
		
	};
	
};


// this function sets the gl colour
// its argument is like a hex number 0xAARRGGBB
// except the AA (alpha channel) is inverted
// so you can type in numbers without an alpha
// channel and it will still work.
void setRGBA(int rgba);
