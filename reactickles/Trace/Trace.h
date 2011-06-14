/*
 *  Trace.h
 *
 *
 */

#include "Reactickle.h"
#include "msaColor.h"
#include "TraceShape.h"

class Trace: public Reactickle {
	
	void setup() {
        maximumLengthOfTrace = 200; //start with 200, make this interactive?
        positionInTrace = 0;
        
        currShapeID == MAGIC_CIRCLE;
	}
	
	void update() {
        for(int i=0; i < traces.size(); i++){
            traces[i].update();
        }
	}
	
	void draw() {
        glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        for(int i=0; i < traces.size(); i++){
            traces[i].draw();
        }
	}
    
	bool touchDown(float x, float y, int touchId){
        addNewTraceToTraces(x,y); 
        
        return true;
    }
    
	bool touchMoved(float x, float y, int touchId){
        addNewTraceToTraces(x,y); 
        
        return true;
    }
    
	bool touchUp(float x, float y, int touchId){
        return true;
    } 
    
    void addNewTraceToTraces(float x, float y){
        if(mode>0) {
            if(mode == 1){
                if (currShapeID == MAGIC_CIRCLE){
                    currShapeID = MAGIC_CROSS;
                }else{
                    currShapeID = MAGIC_CIRCLE;
                }
            }else{ // then it's 2!
                currShapeID++;
                currShapeID %= NUM_MAGIC_SHAPES;                
            }
        }else{
            currShapeID = MAGIC_CIRCLE;
        }         
        
        
        if(traces.size() < maximumLengthOfTrace){
            //then we want to keep growing the vector....
            TraceShape newShape;
            newShape.setup(ofVec2f(x,y), currShapeID);
            traces.push_back(newShape);
        }else{
            //otherwise, change an "old" trace shape
            traces[positionInTrace].setup(ofVec2f(x,y), currShapeID);
        }
        
        positionInTrace++;
        
        positionInTrace %= maximumLengthOfTrace;
    }
	
    vector<TraceShape> traces;
    
    int maximumLengthOfTrace;
    int positionInTrace;
    int currShapeID;
};