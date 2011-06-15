/*
 *  Find.h
 *
 *
 */

#include "Reactickle.h"
#include "msaColor.h"
#include "MagicShapes.h"

class Find: public Reactickle {
	
	void setup() {
        currShapeID = 0;
        
        mode = 0;
        
        newShapePositionAndColour();       
        
        timeOfLastInteraction = ofGetElapsedTimef();
	}
    
    void newShapePositionAndColour(){
        findColour.setHSV(ofRandom(0.f,360.f), 1, 1);
        posOfShape = ofVec2f(ofRandom(0.f, ofGetWidth()), ofRandom(0.f, ofGetHeight()));
        radius = ofRandom(80.f, 200.f);
        
        if(mode>0) {
            if(mode == 1){
                if (currShapeID == MAGIC_CIRCLE){
                    currShapeID = MAGIC_CROSS;
                }else{
                    currShapeID = MAGIC_CIRCLE;
                }
            }else{
                currShapeID++;
                currShapeID %= NUM_MAGIC_SHAPES;                
            }
        }else{
            currShapeID = MAGIC_CIRCLE;
        }        
    }
	
	void update() {
		float timeNow = ofGetElapsedTimef();
		
		float timeSinceLastInteraction = timeNow - timeOfLastInteraction;
		
		if((volume > volumeThreshold) && (timeOfLastInteraction > 0.3f )){			
            newShapePositionAndColour();
            
			timeOfLastInteraction = timeNow;
		}        
        
	}
	
	void draw() {
		findColour.setGL();
        drawShape(currShapeID, posOfShape, radius);
	}
    
	bool touchDown(float x, float y, int touchId){
        float forgiveness = 2.f;
        
        ofVec2f touchPoint = ofVec2f(x,y);
        
        ofVec2f difference = posOfShape - touchPoint;
        
        if(difference.length() < forgiveness + radius){
            newShapePositionAndColour();            
        }
        
        return true;
    }
    
	bool touchMoved(float x, float y, int touchId){
        float forgiveness = 2.f;
        
        ofVec2f touchPoint = ofVec2f(x,y);
        
        ofVec2f difference = posOfShape - touchPoint;
        
        if(difference.length() < forgiveness + radius){
            newShapePositionAndColour();            
        }
        
        return true;
    }
    
	bool touchUp(float x, float y, int touchId){
        return true;
    }
    
    int getNumModes() {
		return 3;
	}
	
	msaColor findColour;
    ofVec2f posOfShape;
    int currShapeID;
    float timeOfLastInteraction;
    float radius;
};