/*
 *  Change.h
 *
 *  Created by Marek Bereza on 05/07/2010.
 *  Copyright 2010 Marek Bereza. All rights reserved.
 *
 */

#include "Reactickle.h"

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
		noiseColour.setHsb(0,0,0);
	}
	
	bool touchDown(float x, float y, int id) {
		trigger(); 
		return true;
	}
	
	void trigger() {
		if(mode == 0){
			if(noiseColour != ofColor(0,0,0)){
				noiseColour.set(0,0,0);
			}else{
				int colorIndex = Settings::getInstance()->settings["fgColor"];
				if(colorIndex==20) {
					noiseColour.set(255,255,255);
				} else {
					noiseColour.setHex(ColorPicker::colors[colorIndex]);
				}
				
			}
			
		}else if(mode == 1){
			if(noiseColour == ofColor(0,0,0)){
				
				int colorIndex = Settings::getInstance()->settings["fgColor"];
				if(colorIndex==20) {
					noiseColour.setHsb(ofRandom(0,255), 255,255);
				} else {
					noiseColour.setHex(ColorPicker::colors[colorIndex]);
				}
				
				
				
			}else{
				noiseColour.setHsb(0,0,0);
			} 
			
		}else{
			noiseColour.setHsb(ofRandom(0,255), 255, 255);                
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
		printf("Volume:: %f\n", volume);
        if((volume > volumeThreshold) && (timeSinceLastCircle > 0.3f )){	
			
            trigger();
		}
	}
	
	void draw() {
		ofSetColor(noiseColour);
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
	ofColor noiseColour;
};