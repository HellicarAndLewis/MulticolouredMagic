/**
 * ClapClock.h
 * magic
 *
 * Named by Marek Bereza on 12/04/2011.
 * Hacked by Joel Gethin Lewis on 12/04/2011.
 *
 */

#include "TTApp.h"
class ClapClock: public TTApp {
public:
	void setup(){
        ofSetCircleResolution(42); //42 is the answer to everything!
        
        numberOfShapes = 0;
        
        numberOfMiddleShapes = 0;
        numberOfInnerShapes = 0;        
        
		timeOfLastInteraction = ofGetElapsedTimef();
        
        ofColor shapesColour = ofColor::red;
        ofColor bigShapeColour = ofColor::red;  
        
        shapesRadius = 40.f;
        bigShapeRadius = 400.f;
        maxNumberOfShapes = 20;    
        maxNumberOfMiddleShapes = 8;
        maxNumberOfInnerShapes = 4;
        
        centreOfBigShape = ofVec2f(ofGetWidth()/2.f, ofGetHeight()/2.f);  
        startOfShapes.x = centreOfBigShape.x;
        startOfShapes.y = centreOfBigShape.y - (bigShapeRadius/2) - (shapesRadius/2);
        
        startOfMiddleShapes.x = centreOfBigShape.x;
        startOfMiddleShapes.y = startOfShapes.y * 1.33f;
        
        startOfInnerShapes.x = centreOfBigShape.x;
        startOfInnerShapes.y = startOfShapes.y * 1.66f;     
        
        shapeOnScreen = false;
        
        radiansPerShape = (2*PI)/maxNumberOfShapes;
        
        radiansPerMiddleShape = (2*PI)/maxNumberOfMiddleShapes;
        
        radiansPerInnerShape = (2*PI)/maxNumberOfInnerShapes;
        
        currentShapeType = 0;
	}
	
	void update(){
		float timeNow = ofGetElapsedTimef();
		
		float timeSinceLastInteraction = timeNow - timeOfLastInteraction;        
		
		if((volume > volumeThreshold) && (timeSinceLastInteraction > 0.3f )){
            touchDown(ofGetWidth()/2.f, ofGetHeight()/2.f, 0); //simulate a touch in the centre of the screen
		}
	}
	
	void draw() {
        ofPushStyle(); //for safety in terms of drawing, and not messing up anyone elses code
        ofBackground(0); //set to black (0 brightness)
        ofFill();
        
        switch (mode) {
            case 0:
                if (shapeOnScreen) {
                    drawShape(currentShapeType, centreOfBigShape, bigShapeRadius); //using the new MagicShapes.h file
                }
                break;
            case 1:
                if(numberOfShapes > 0){
                    ofSetColor(shapesColour);
                    
                    ofVec2f currentShapePosition = startOfShapes;
                    
                    for(int i=0; i< numberOfShapes; i++){
                        drawShape(currentShapeType, currentShapePosition, shapesRadius);
                        
                        currentShapePosition = currentShapePosition.getRotatedRad(radiansPerShape, centreOfBigShape);
                    }
                    
                }else{
                    ofSetColor(bigShapeColour);
                    drawShape(currentShapeType, centreOfBigShape, bigShapeRadius);
                }
                break;
            case 2:
                if(numberOfShapes > 0){
                    ofSetColor(shapesColour);
                    
                    ofVec2f currentShapePosition = startOfShapes;
                    
                    for(int i=0; i< numberOfShapes; i++){
                        drawShape(currentShapeType, currentShapePosition, shapesRadius);
                        
                        currentShapePosition = currentShapePosition.getRotatedRad(radiansPerShape, centreOfBigShape);
                    }
                    
                    if(numberOfMiddleShapes > 0){
                        
                        currentShapePosition = startOfMiddleShapes;
                        
                        for(int i=0; i< numberOfMiddleShapes; i++){
                            drawShape(currentShapeType, currentShapePosition, shapesRadius);
                            
                            currentShapePosition = currentShapePosition.getRotatedRad(radiansPerMiddleShape, centreOfBigShape);
                        }
                    }
                    
                    if(numberOfInnerShapes > 0){
                        currentShapePosition = startOfInnerShapes;
                        
                        for(int i=0; i< numberOfInnerShapes; i++){
                            drawShape(currentShapeType, currentShapePosition, shapesRadius);
                            
                            currentShapePosition = currentShapePosition.getRotatedRad(radiansPerInnerShape, centreOfBigShape);
                        }
                    }
                }else{
                    ofSetColor(bigShapeColour);
                    drawShape(currentShapeType, centreOfBigShape, bigShapeRadius);
                }                
                
                break; //nothing for the most complicated version yet...
            default:
                break;
        }
        
        ofPopStyle(); //pop back what was there before
	}
    
    void touchDown(float x, float y, int touchId){        
        switch (mode) {
            case 0:
                shapeOnScreen = !shapeOnScreen;
                
                if(!shapeOnScreen){
                    nextShape();
                }
                
                timeOfLastInteraction = ofGetElapsedTimef();                
                break;
            case 1:
                numberOfShapes++;
                
                if(numberOfShapes > maxNumberOfShapes){
                    numberOfShapes = 0;
                    bigShapeColour = ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));            
                    shapesColour = bigShapeColour;
                    nextShape();
                }
                
                timeOfLastInteraction = ofGetElapsedTimef();                
                break;
            case 2:
                if (numberOfShapes < maxNumberOfShapes) {
                    numberOfShapes++;
                }else if (numberOfMiddleShapes < maxNumberOfMiddleShapes){
                    numberOfMiddleShapes++;
                }else if (numberOfInnerShapes <= maxNumberOfInnerShapes){
                    numberOfInnerShapes++;
                }
                
                if((numberOfShapes >= maxNumberOfShapes) && (numberOfMiddleShapes >= maxNumberOfMiddleShapes) && (numberOfInnerShapes > maxNumberOfInnerShapes)){
                    numberOfShapes = 0;
                    numberOfMiddleShapes = 0;
                    numberOfInnerShapes = 0;
                    
                    bigShapeColour = ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));            
                    shapesColour = bigShapeColour;
                    nextShape();
                }
                
                timeOfLastInteraction = ofGetElapsedTimef();                   
                
                break;
            default:
                break;
        }
    }
    
    void nextShape(){
        currentShapeType++;
        
        if(currentShapeType >=NUM_MAGIC_SHAPES || currentShapeType < 0) { //safety!
            currentShapeType = 0;
        }
    }
	
	float timeOfLastInteraction;
    int numberOfShapes;
    ofColor shapesColour;
    ofColor bigShapeColour;
    float shapesRadius;
    float bigShapeRadius;
    int maxNumberOfShapes;
    ofVec2f startOfShapes;
    ofVec2f centreOfBigShape;
    
    bool shapeOnScreen;
    float radiansPerShape;
    int currentShapeType;
    
    int maxNumberOfMiddleShapes;
    int maxNumberOfInnerShapes;
    
    int numberOfMiddleShapes;
    int numberOfInnerShapes;
    
    float radiansPerMiddleShape;
    float radiansPerInnerShape;    
    
    ofVec2f startOfMiddleShapes;
    ofVec2f startOfInnerShapes;
};