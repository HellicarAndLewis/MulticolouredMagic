/*
 *  Find.h
 *
 *
 */

#include "Reactickle.h"
#include "MagicShapes.h"

class Find: public Reactickle {
    
    void start();
	
	void setup();
    

	
	void update();
	
	void draw();
    
	bool touchDown(float x, float y, int touchId);
    
	bool touchMoved(float x, float y, int touchId);    
	bool touchUp(float x, float y, int touchId);
    
    int getNumModes() {
		return 3;
	}
    
    void modeChanged() {        
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        m.setAddress("/modechange");
        m.addIntArg( mode );
        ReactickleApp::instance->sender.sendMessage( m );
#endif
    }	
private:
    void newShapePositionAndColour();
	ofColor findColour;
	ofVec2f posOfShape;
	ofColor targetFindColour;
    ofVec2f targetPosOfShape;
    int currShapeID;
    float timeOfLastInteraction;
    float radius;
};