
#include "testApp.h"

//--------------------------------------------------------------
testApp::testApp(){
}

//--------------------------------------------------------------
void testApp::setup() {
	
	
	ofSetVerticalSync(true);
	ofBackground(20, 20, 20);
	ofSetLogLevel(OF_LOG_NOTICE);
	ofEnableAlphaBlending();
	ofEnableSmoothing();
	
	bDrawLines  = false;
	bMouseForce = false;
	
	box2d.init();
	box2d.setGravity(0, 10);
	box2d.createFloor();
	box2d.checkBounds(true);
	box2d.setFPS(30.0);
	
	

	for(int j=0; j<10; j++){
	// lets draw a simple lanscape
	ofPoint p(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
	int segs = 10;
	lineStrip[j].setWorld(box2d.getWorld());
	lineStrip[j].clear();
	for(int i=0; i<segs; i++) {
		p.x += 15;
		lineStrip[j].addPoint(p.x, p.y);
	}
	lineStrip[j].createShape();
			  }
	ofBackground(255, 255, 255);
	
}

//--------------------------------------------------------------
void testApp::update() {
	
	
	
	box2d.update();
	

	
}


//--------------------------------------------------------------
void testApp::draw() {
	

	ofSetRectMode(OF_RECTMODE_CENTER);
	for(int i=0; i<boxes.size(); i++) {
		//boxes[i].draw();
		ofPushMatrix();
		ofPushStyle();
		ofFill();
		ofSetColor(boxes[i].getPosition().x/4, 255-boxes[i].getPosition().x/4, boxes[i].getPosition().x/4+125);
		ofTranslate(boxes[i].getPosition().x, boxes[i].getPosition().y, 0);
		ofRotateZ(boxes[i].getRotation());
		ofRect(0, 0, 60, 60);
		ofPopStyle();
		ofPushStyle();
		ofNoFill();
		ofSetColor(0, 0, 0);
		ofRect(0, 0, 60, 60);
		ofPopStyle();
		ofPopMatrix();
	}

	for(int i =0; i<10; i++){
	lineStrip[i].draw();
	}
	//box2d.draw();
	
	px = mouseX;
	py = mouseY;
	

}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	

	
	if(key == 'r') {
		//boxes.destroyShape();

		for(int i=0; i<10; i++){
			lineStrip[i].clear();
			ofPoint p(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
			int segs = 10;
			lineStrip[i].setWorld(box2d.getWorld());
			lineStrip[i].clear();
			for(int j=0; j<segs; j++) {
				p.x += 15;
				lineStrip[i].addPoint(p.x, p.y);
			}
			lineStrip[i].createShape();
		}
		}
		
	if(key == 'f') {
		ofToggleFullscreen();
		box2d.createFloor(ofGetWidth(), ofGetHeight());
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
	
	float w = 60;	
	float h = 60;	
	ofxBox2dRect rect;
	rect.setPhysics(3.0, 0.53, 0.1);
	rect.setup(box2d.getWorld(), mouseX, mouseY, w, h);
	boxes.push_back(rect);
	

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

	float w = 60;	
	float h = 60;	
	ofxBox2dRect rect;
	rect.setPhysics(3.0, 0.53, 0.1);
	rect.setup(box2d.getWorld(), mouseX, mouseY, w, h);
	boxes.push_back(rect);

	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
		box2d.createFloor(w, h);
}

