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
	
private:
    void addNewTraceToTraces(float x, float y);    
    
    
  
	
    vector<TraceShape> traces;
    
    int maximumLengthOfTrace;
    int positionInTrace;
    int currShapeID;
};