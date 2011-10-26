/**
 * Expand.h
 * magic
 *
 * Created by Joel Gethin Lewis on 13/04/2011.
 *
 */

#include "Reactickle.h"
#include "ReactickleApp.h"
#include "constants.h"

class Expand: public Reactickle {
public:
    void start(){
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        int reactickleNumber = 0;
        m.setAddress( "/reacticklechange" );
        m.addIntArg( reactickleNumber );
        ReactickleApp::instance->sender.sendMessage( m );
#endif
    }
    
    
	void setup(){
        ofSetCircleResolution(42); //42 is the answer to everything!
        
		timeOfLastInteraction = ofGetElapsedTimef();
    
        bigShapeRadius = 400.f;
        
        centreOfBigShape = ofVec2f(WIDTH/2.f, HEIGHT/2.f);  
        
        currentShapeType = 0;
        
        drawACircle = false;
        
        shapeScale = 1.f;
        
        whiteBg = false;
	}
	
	void update(){
		float timeNow = ofGetElapsedTimef();
		
		float timeSinceLastInteraction = timeNow - timeOfLastInteraction;        
		printf("volume: %f\n", volume);
		if((volume > volumeThreshold) && (timeSinceLastInteraction > 0.3f )){
            touchDown(WIDTH/2.f, HEIGHT/2.f, 0); //simulate a touch in the centre of the screen
		}
	}
	
	void draw() {
		ofSetHexColor(0xFFFFFF);
        ofPushStyle(); //for safety in terms of drawing, and not messing up anyone elses code
        //ofBackground(0); //set to black (0 brightness)
        ofFill();
        
        switch (mode) {
            case 0:


                if (!drawACircle) {
                    drawCross(centreOfBigShape, bigShapeRadius);
                    //drawCircle(centreOfBigShape, bigShapeRadius);
                }else{
                    drawCircle(centreOfBigShape, bigShapeRadius);
                }
                break;
            case 1:
                drawShape(currentShapeType, centreOfBigShape, bigShapeRadius);
                break;
            case 2:
                if(!whiteBg){// had to flip this because I couldn't get a heart to draw in white(?)
                    ofSetColor(ofColor::white);
                    ofRect(0, 0, WIDTH, HEIGHT);
                    ofSetColor(ofColor::black);
                }else{
                    ofSetColor(ofColor::white);
                }
				
				//if(currentShapeType==MAGIC_HEART) {
				//	drawShape(MAGIC_CIRCLE, centreOfBigShape, bigShapeRadius*shapeScale);                
				//} else {
					drawShape(currentShapeType, centreOfBigShape, bigShapeRadius*shapeScale);                
				//}
                break;
            default:
                break;
        }
        
        ofPopStyle(); //pop back what was there before
	}
	
    bool touchDown(float x, float y, int touchId){  
		
		
#ifndef TARGET_OF_IPHONE
        ofxOscMessage simpleMessage;
#endif
        switch (mode) {
            case 0:
                drawACircle = !drawACircle;
                
                timeOfLastInteraction = ofGetElapsedTimef(); 
                
                int shapeType;
                
                if(drawACircle){
                    shapeType = 0;
                }else{
                    shapeType = 2;
                }
#ifndef TARGET_OF_IPHONE
                simpleMessage.setAddress( "/shapechange" );
                simpleMessage.addIntArg( shapeType );
                ReactickleApp::instance->sender.sendMessage( simpleMessage );
#endif
                break;
            case 1:
                nextShape();
                
                timeOfLastInteraction = ofGetElapsedTimef();                
                break;
				
            case 2:
				
			{
				float maxScale = 5;
				// custom sizes for each shape to grow to
				switch(currentShapeType) {
					case MAGIC_CIRCLE: maxScale = 4; break;
					case MAGIC_CROSS: maxScale = 4.5; break;
					case MAGIC_TRIANGLE: maxScale = 7.4; break;
					case MAGIC_HEART: maxScale = 6.0; break;
					case MAGIC_HEXAGON: maxScale = 4.0; break;
					case MAGIC_SQUARE: maxScale = 3.0; break;
				}
				shapeScale += 0.5f;
				
				// make triangles, hearts and crosses grow faster
				if((currentShapeType==MAGIC_CROSS || currentShapeType==MAGIC_TRIANGLE || currentShapeType==MAGIC_HEART) && shapeScale>2) shapeScale += 0.5;

				if(shapeScale >= maxScale){
					shapeScale = 0.6;
					nextShape();
					whiteBg = !whiteBg;
				}
				timeOfLastInteraction = ofGetElapsedTimef();                
				break;
			}
            default:
                break;
        }
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
        m.setAddress( "/touchdown" );
        m.addIntArg(mode);
        ReactickleApp::instance->sender.sendMessage(m);
#endif
		return true;
    }
    
    void nextShape(){
        currentShapeType++;
        
        if(currentShapeType >= NUM_MAGIC_SHAPES || currentShapeType < 0) { //safety!
            currentShapeType = 0;
        }
#ifndef TARGET_OF_IPHONE
        ofxOscMessage m;
		m.setAddress( "/shapechange" );
		m.addIntArg( currentShapeType );
		ReactickleApp::instance->sender.sendMessage( m );
#endif
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
		shapeScale = 1.f;
    }
	
	float timeOfLastInteraction;
    float bigShapeRadius;
    ofVec2f centreOfBigShape;
    
    bool drawACircle;
    int currentShapeType;
    
    float shapeScale;
    
    bool whiteBg;
};