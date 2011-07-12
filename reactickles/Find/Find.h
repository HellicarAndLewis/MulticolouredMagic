/*
 *  Find.h
 *
 *
 */

#include "Reactickle.h"
#include "msaColor.h"
#include "MagicShapes.h"

class Find: public Reactickle {
    
    void start(){
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        int reactickleNumber = 8;
        m.setAddress( "/reacticklechange" );
        m.addIntArg( reactickleNumber );
        ReactickleApp::instance->sender.sendMessage( m );
#endif
    }
	
	void setup() {
        currShapeID = 0;
        
        mode = 0;
        
        newShapePositionAndColour();       
        
		posOfShape = targetPosOfShape;
		findColour = targetFindColour;
		
        timeOfLastInteraction = ofGetElapsedTimef();
	}
    
    void newShapePositionAndColour(){
        targetFindColour.setHSV(ofRandom(0.f,360.f), 1, 1);
        targetPosOfShape = ofVec2f(ofRandom(0.f, ofGetWidth()), ofRandom(0.f, ofGetHeight()));
        radius = ofRandom(100.f, 260.f);
        
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
        
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        m.setAddress( "/shapechange" );
        m.addIntArg( currShapeID );
        ReactickleApp::instance->sender.sendMessage( m );
#endif
        
    }
	
	void update() {
		float timeNow = ofGetElapsedTimef();
		
		float timeSinceLastInteraction = timeNow - timeOfLastInteraction;
		
		if((volume > volumeThreshold) && (timeOfLastInteraction > 0.3f )){			
            newShapePositionAndColour();
            
			timeOfLastInteraction = timeNow;
		}        
        
		float l = 0.7;
		posOfShape = posOfShape * l + targetPosOfShape * (1.f - l);
		findColour = findColour * l + targetFindColour * (1.f - l);
		
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
        
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        m.setAddress( "/touchdown" );
        m.addIntArg(mode);
        ReactickleApp::instance->sender.sendMessage(m);
#endif
        
        return true;
    }
    
	bool touchMoved(float x, float y, int touchId){
        touchDown(x, y, touchId);
    }
    
	bool touchUp(float x, float y, int touchId){
        return true;
    }
    
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

	msaColor findColour;
	ofVec2f posOfShape;
	msaColor targetFindColour;
    ofVec2f targetPosOfShape;
    int currShapeID;
    float timeOfLastInteraction;
    float radius;
};