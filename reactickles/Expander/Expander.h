/**
 * Expander.h
 * magic
 *
 * Created by Joel Gethin Lewis on 13/04/2011.
 *
 */

#include "Reactickle.h"

#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class Expander: public Reactickle {
public:
	void setup(){
        ofSetCircleResolution(42); //42 is the answer to everything!
        
		timeOfLastInteraction = ofGetElapsedTimef();
    
        bigShapeRadius = 400.f;
        
        centreOfBigShape = ofVec2f(ofGetWidth()/2.f, ofGetHeight()/2.f);  
        
        currentShapeType = 0;
        
        drawACircle = false;
        
        shapeScale = 1.f;
        
        whiteBg = false;
        
        // open an outgoing connection to HOST:PORT
        sender.setup( HOST, PORT );
	}
	
	void update(){
		float timeNow = ofGetElapsedTimef();
		
		float timeSinceLastInteraction = timeNow - timeOfLastInteraction;        
		
		if((volume > volumeThreshold) && (timeSinceLastInteraction > 0.3f )){
            touchDown(ofGetWidth()/2.f, ofGetHeight()/2.f, 0); //simulate a touch in the centre of the screen
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
                if(whiteBg){
                    ofSetColor(ofColor::white);
                    ofRect(0, 0, ofGetWidth(), ofGetHeight());
                    ofSetColor(ofColor::black);
                }else{
                    ofSetColor(ofColor::white);
                }
                drawShape(currentShapeType, centreOfBigShape, bigShapeRadius*shapeScale);                
                break;
            default:
                break;
        }
        
        ofPopStyle(); //pop back what was there before
	}
    
    void touchDown(float x, float y, int touchId){        
        ofxOscMessage simpleMessage;
        
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
                
                simpleMessage.setAddress( "/shapechange" );
                simpleMessage.addIntArg( shapeType );
                sender.sendMessage( simpleMessage );
                
                break;
            case 1:
                nextShape();
                
                timeOfLastInteraction = ofGetElapsedTimef();                
                break;
            case 2:
                shapeScale += 0.5f;
                
                if(shapeScale >= 5.f){
                    shapeScale = 1.f;
                    nextShape();
                    whiteBg = !whiteBg;
                }
				timeOfLastInteraction = ofGetElapsedTimef();                
                break;
            default:
                break;
        }
        
        ofxOscMessage m;
        m.setAddress( "/touchdown" );
        m.addIntArg(mode);
        sender.sendMessage(m);
    }
    
    void nextShape(){
        currentShapeType++;
        
        if(currentShapeType >= NUM_MAGIC_SHAPES || currentShapeType < 0) { //safety!
            currentShapeType = 0;
        }
        
        ofxOscMessage m;
		m.setAddress( "/shapechange" );
		m.addIntArg( currentShapeType );
		sender.sendMessage( m );
    }
	
	float timeOfLastInteraction;
    float bigShapeRadius;
    ofVec2f centreOfBigShape;
    
    bool drawACircle;
    int currentShapeType;
    
    float shapeScale;
    
    bool whiteBg;
    
    ofxOscSender sender;
};