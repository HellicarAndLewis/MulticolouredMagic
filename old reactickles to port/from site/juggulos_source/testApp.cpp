#include "testApp.h"


bool	ringShow;



int		myInt4;
int		myInt5;
int		myInt6;



float gravitySetter;
float windSetter;
float vibrationSetter = 0;

float centreBallX[4];
float centreBallY[4];

float ButterflyRadius = 60.0f;
float ButterflyRotSpeed = 0.003;
float ButterflySizeSpeed = 0.001;
float ButterflyMaxSize = 20.0;


//--------------------------------------------------------------
void testApp::setup(){
	
	
zoom.setZoomParams(ofGetWidth()/2, ofGetHeight()/2, 180, 0.0, 1.5);
	
	
	

	gravity = ofxVec3f(0.0, 1.0f, 0.0);
	wind = ofxVec3f(0.5f, 0.0, 0.0);
	vibration = 0.5;
	
	/*
	b1.color[0] = 0;
	b2.color[1] = 0;
	b3.color[2] = 0;
	b4.color[0] = 0;
	b4.color[1] = 0;
	*/
	 
	balls[0] = &b1; //use a reference so we can access the pointer later
	balls[1] = &b2;
	balls[2] = &b3;
	balls[3] = &b4;
	
	
	
		
	gravitySetter = 0.2;
	windSetter = 0.5;
	
	ringShow = false;
	
	
	
	//ofBackground(colorA, colorB, colorC);
	
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	// 'gui' is a global variable declared in ofxSimpleGuiToo.h
	gui.addTitle("Physics");
	gui.addSlider("Gravity", gravitySetter, 0.0, 5.0f); 
	gui.addSlider("Wind", windSetter, 0.0, 5.0f); 
	//gui.addToggle("myBool1", myBool1);
	//gui.addButton("Randomize Background", randomizeButton);
	
	
	// start a new group
	gui.addTitle("Ring Properties");
	gui.addSlider("Vibration", vibrationSetter, 0.0, 20.0f);
	gui.addSlider("Maximum Size", ButterflyMaxSize, 5.0f, 150.0);
	gui.addSlider("Rotation Speed", ButterflyRotSpeed, 0.0001, 0.003);
	//gui.addSlider("Radius", ButterflyRadius, 10.0f, 60.0f);
	//gui.addSlider("Size speed", ButterflySizeSpeed, 0.001, 1.0);
	//gui.addSlider("myInt2", myInt2, 3, 8);
	gui.addToggle("Click for Rings", ringShow);	
	
	// new group, this time separate into it's own column
	gui.addTitle("Background").setNewColumn(true);
	//gui.addToggle("Save Background", backSave);	
	//gui.addToggle("myBool3", myBool3);	
	//gui.addSlider("myFloat3", myFloat3, 0.0, 1);
	//gui.addSlider("myFloat4", myFloat4, 0.0, 20);
	gui.addSlider("Red Value", myInt4, 0, 255);
	gui.addSlider("Green Value", myInt5, 0, 255);
	gui.addSlider("Blue Value", myInt6, 0, 255);
	//gui.addContent("Camera feed", vidGrabber);
	//gui.addContent("Inverted", videoTexture);
	
	
			
	
	gui.loadFromXML();
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 2.0));
	
	zoom.setup(ofGetWidth(), ofGetHeight());

	
	

	
	zoom.setZoomParams(ofGetWidth()/2, ofGetHeight()/2, 320, 0.0, 1.5);
	ofBackground(myInt4, myInt5, myInt6);
	gravity = ofxVec3f(0.0, gravitySetter, 0.0);
	wind = ofxVec3f(windSetter, 0.0, 0.0);
	vibration = vibrationSetter;
	
	
	
	b1.addForce(gravity);
	b2.addForce(gravity);
	b3.addForce(gravity);
	b4.addForce(gravity);
	
	b1.addForce(wind);
	b2.addForce(wind);
	b3.addForce(wind);
	b4.addForce(wind);
	
	b1.updateBall();
	b2.updateBall();
	b3.updateBall();
	b4.updateBall();
	
	
	

	checkCollision();
	
	

}


//--------------------------------------------------------------
void testApp::draw(){
	
	
	
	zoom.beginRender();
		
	b1.drawFrame();
	b2.drawFrame();
	b3.drawFrame();
	b4.drawFrame();
	
	b1.moveShape();
	b2.moveShape();
	b3.moveShape();
	b4.moveShape();
	zoom.endRender();
	
	
	zoom.draw(0,0, ofGetHeight(), ofGetHeight(), true);
	
	
	
	if (ringShow == true){
		extraRings();
	}
	
	drawConnectors();
	
	gui.draw();
	
	
		
	
	
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	
	if(key>='0' && key<='9') {
		gui.setPage(key - '0');
		gui.show();
	} else {
		switch(key) {
			case ' ': gui.toggleDraw(); break;
			case '[': gui.prevPage(); break;
			case ']': gui.nextPage(); break;
			case 'p': gui.nextPageWithBlank(); break;
			//case 'h': gui.hide(); break;
			//case 's': gui.show(); break;
		}
	}
	
	if(key=='f') ofToggleFullscreen();	
	

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
	
		b1.pauseBall(mouseX, mouseY);
		b2.pauseBall(mouseX, mouseY);
		b3.pauseBall(mouseX, mouseY);
		b4.pauseBall(mouseX, mouseY);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::resized(int w, int h){

}

//--------------------------------------------------------------
void testApp::drawConnectors(){
	ofPushStyle();
	
	int i, j;
	for (i=0; i<numBalls; i++)
	{
		for(j=i+1; j<numBalls; j++) {
			ofSetColor(0,0,0);
			ofLine(balls[i]->location.x, balls[i]->location.y, balls[j]->location.x, balls[j]->location.y);
			
		}
	}
	
	ofPopStyle();
}

//--------------------------------------------------------------
void testApp::checkCollision(){
	
	int i, j;
	for(i=0; i<numBalls; i++)
	{
		for(j=i+1; j<numBalls; j++)
		{
			if(balls[i]->location.x+100 > balls[j]->location.x && balls[i]->location.x < balls[j]->location.x+100)
			{
				if (balls[i]->location.y+100 > balls[j]->location.y && balls[i]->location.y < balls[j]->location.y+100)
				{
					balls[i]->collision(balls[j]);
				}
			}
		}
	}
	
}
//--------------------------------------------------------------
void testApp::extraRings(){
ofPushStyle();
	
	for (int i=0; i<numBalls; i++)
	{
		for (int j=0; j<4; j++)
		{
			
		ofSetColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
	
			
		float radius = ButterflyRadius + (ButterflyRadius/6.0)*j;
		float rotSpeed = ButterflyRotSpeed+(4-j)*(ButterflyRotSpeed/3.0);
			radius *= sin(vibration);
		float time = ofGetElapsedTimeMillis();
		float angle = time*(i+1)*rotSpeed;
		float delX = sin(angle)*radius;
		float delY = cos(angle)*radius;
			float sizeAngle = time*ButterflySizeSpeed;
			float size = sin(sizeAngle)*ButterflyMaxSize;
		ofCircle(balls[i]->location.x+delX,balls[i]->location.y+delY, size);
		}
		
	}
	ofPopStyle();
}



