/*
 *  Find.h
 *
 *
 */

#include "Reactickle.h"
#include "MagicShapes.h"

class Find: public Reactickle {
    
	void setup();
    

	
	void update();
	
	void draw();
    
	bool touchDown(float x, float y, int touchId);
    
	bool touchMoved(float x, float y, int touchId);    
	bool touchUp(float x, float y, int touchId);
    
    int getNumModes() {
		return 3;
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