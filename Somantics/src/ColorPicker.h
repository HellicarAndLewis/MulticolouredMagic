/**
 * ColorPicker.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */
#include "InteractiveObject.h"

class ColorPicker: public InteractiveObject {
public:
	void setup();
	void draw();
	ofImage *colors;
	bool touchDown(float xx, float yy, int tid);
	bool touchMoved(float xx, float yy, int tid);
	bool touchUp(float xx, float yy, int tid);
private:
	
	unsigned char *colorVals;
	
	ofColor getColor(int pos);
};