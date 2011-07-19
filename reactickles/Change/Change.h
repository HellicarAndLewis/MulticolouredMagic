/*
 *  Change.h
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"
#include "msaColor.h"

class Change: public Reactickle {
    
    void start(){
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        int reactickleNumber = 7;
        m.setAddress( "/reacticklechange" );
        m.addIntArg( reactickleNumber );
        ReactickleApp::instance->sender.sendMessage( m );
#endif
    }
	
	void setup() {
		
//		noiseColour.setHSV(ofRandom(0.f,360.f), 1, 1);
		noiseColour.set(0,0,0);
	}
	
	bool touchDown(float x, float y, int id) {
		trigger(); 
		return true;
	}
	
	void trigger() {
		if(mode == 0){
			if(noiseColour == msaColor(255,255,255)){
				noiseColour.set(0,0,0);
			}else{
				noiseColour.set(255,255,255);
			}
		}else if(mode == 1){
			if(noiseColour == msaColor(0,0,0)){
				noiseColour.setHSV(ofRandom(0,360), 1, 1);
			}else{
				noiseColour.set(0,0,0);
			}               
		}else{
			noiseColour.setHSV(ofRandom(0,360), 1, 1);                
		}
        
#ifndef TARGET_OF_IPHONE
        //triggers are touch downs....
        ofxOscMessage m;
        m.setAddress( "/touchdown" );
        m.addIntArg(mode);
        ReactickleApp::instance->sender.sendMessage(m);
#endif
		
		timeOfLastNewCircle = ofGetElapsedTimef();
	}
	void update() {
		float timeNow = ofGetElapsedTimef();
		
		float timeSinceLastCircle = timeNow - timeOfLastNewCircle;
		
        if((volume > volumeThreshold) && (timeSinceLastCircle > 0.3f )){	
			
            trigger();
		}
	}
	
	void draw() {
		noiseColour.setGL();
		ofRect(0, 0, WIDTH, HEIGHT);
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
	
	float timeOfLastNewCircle;
	int colourPosition;
	msaColor noiseColour;
};