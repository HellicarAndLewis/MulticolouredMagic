/*
 *  Trace.h
 *
 *
 */

#include "Reactickle.h"
#include "TraceShape.h"

class Trace: public Reactickle {
public:
	
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
    void addNewTraceToTraces(float x, float y);    
    
    
  
	
    vector<TraceShape> traces;
    
    int maximumLengthOfTrace;
    int positionInTrace;
    int currShapeID;
};