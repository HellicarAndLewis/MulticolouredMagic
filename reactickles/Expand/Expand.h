/**
 * Expand.h
 * magic
 *
 * Created by Joel Gethin Lewis on 13/04/2011.
 *
 */

#include "Reactickle.h"
#include "ReactickleApp.h"


class Expand: public Reactickle {
public:
    void start();    
    
	void setup();	
	void update();
	
	void draw();
    bool touchDown(float x, float y, int touchId);    
    void nextShape();
    
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
		shapeScale = 1.f;
    }
	
private:
	float timeOfLastInteraction;
    float bigShapeRadius;
    ofVec2f centreOfBigShape;
    
    bool drawACircle;
    int currentShapeType;
    
    float shapeScale;
    
    bool whiteBg;
};