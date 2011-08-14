/*
 *  Cascades.cpp
 *  SomanticsMac
 *
 *  Created by base on 13/08/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Cascades.h"


void Cascades::setup()
{
/*
	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
	
	//If you want a landscape oreintation 
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
*/	
 
	ofBackground(127,127,127);
	
	box2d.init();
	box2d.setGravity(0, 10);
	//box2d.createBounds();
	box2d.setFPS(40.0);
	
	radius = 40.f;
		
	float x = 200.f;
	float y = 200.f;
	
	bodyShape = NULL;
	
	waterfallLEdge = 10;
	waterfallREdge = 400;
	
	scaledImage.allocate(VISION_WIDTH, VISION_HEIGHT);
	grayImage.allocate(VISION_WIDTH, VISION_HEIGHT);
	grayBg.allocate(VISION_WIDTH, VISION_HEIGHT);
	grayDiff.allocate(VISION_WIDTH, VISION_HEIGHT);
	canvas.allocate(VISION_WIDTH, VISION_HEIGHT);

	threshold = 70;
	amount = 0.9;

}


void Cascades::update()
{

	ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
	
	float height = ofGetHeight();
	
	vector<ofxBox2dCircle>::iterator cit = circles.begin();
	while( cit != circles.end()) {
		if(cit->getPosition().y > height) {
			circles.erase(cit);
		}
		++cit;
	}
	
	if( circles.size() < 100 ) { // > 100 on screen
		ofxBox2dCircle circle;
		circle.setPhysics(3.0, 0.5, 1.0);
		float pos = ofRandom(waterfallREdge - waterfallLEdge) + waterfallLEdge;
		circle.setup(box2d.getWorld(), pos, -100, radius);
		circles.push_back(circle); // add a new one
	}
	
	box2d.update();
	
	grayBg.convertToRange(0, 255.f*(1.f - amount));
	grayImage.convertToRange(0, 255.f*(amount));
	
	// grayBg = grayBg * 0.9 + grayImage * 0.1
	grayBg += grayImage;
	
	if(colorImg!=NULL) {
		scaledImage.scaleIntoMe(*colorImg);
		grayImage = scaledImage;
		
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
		
		checkBlobs();
		
	}
	
}

//--------------------------------------------------------------
void Cascades::draw(){
	
	ofSetColor(255, 255, 255);
	ofFill();
	
	vector<ofxBox2dCircle>::iterator cit = circles.begin();
	while( cit != circles.end()) {
		//cit->draw();
		ofCircle(cit->getPosition().x, cit->getPosition().y, 80);
		++cit;
	}
	
	ofSetColor(0, 0, 255);
	ofNoFill();
	
	vector<ofxCvBlob>::iterator c_it = contourFinder.blobs.begin();
	
	while(c_it != contourFinder.blobs.end() ) {
		c_it->draw();
		++c_it;
	}
	
	if(bodyShape != NULL) {
		bodyShape->draw();
	
		ofSetColor(0, 0, 255);
		ofFill();
		vector <ofPoint>::iterator pit = bodyShape->getVertices().begin();
		while(pit != bodyShape->getVertices().end() )
		{
			ofCircle(pit->x, pit->y, 5);
			++pit;
		}
	}
}


void Cascades::checkBlobs() 
{
	
	contourFinder.findContours(grayDiff, 120, (scaledImage.getWidth()*scaledImage.getHeight())/2, 5, false); // no holes
	
	if(contourFinder.blobs.size() < 1) return;
	
	vector<ofxCvBlob>::iterator c_it = contourFinder.blobs.begin();
	ofxCvBlob largest = contourFinder.blobs[0];
	
	while(c_it != contourFinder.blobs.end() ) {
		if(c_it->area > largest.area) largest = *c_it;
		++c_it;
	}
	
	cout << " largest " <<  largest.area << " " << largest.pts.size() << endl;
	
	
	// ------------------------------------------------
	// TODO read up on box2d && update shape instead of delete
	// and new(), seems like a complete waste
	// ------------------------------------------------
	
	/*
	int pCount = 0;
	vector <ofPoint>::iterator pit = largest.pts.begin();
	while(pit != largest.pts.end() ) {
		
		if(bodyShape.getVertices().size() < pCount) {
		
			bodyShape.addVertex( *pit );
		} else {
				
			ofPoint closest = bodyShape.getClosestPoint( *pit );
			closest.x = pit->x; // need something smarter here
			closest.y = pit->y; // need something smarter here
		}
		
		++pit;
		pCount++;
	}
	
	if(pCount < bodyShape.getVertices().size()) {
		bodyShape.getVertices().erase( bodyShape.getVertices().begin() + pCount, bodyShape.getVertices().end());
	}*/
	
#ifndef DEBUG
	if(bodyShape) {
		bodyShape->destroy();
		delete bodyShape;
	}
	
	bodyShape = new ofxBox2dPolygon();
	
	vector <ofPoint>::iterator pit = largest.pts.begin();
	while(pit != largest.pts.end() )
	{
		// triangulatePolygonWithOutline(resampled, outline);??
		bodyShape->addVertex( *pit );
		++pit;
	}
	bodyShape->simplify(15);

	bodyShape->create(box2d.getWorld());
	
	cout << " is good shape " << bodyShape->isGoodShape() << " ";
	
#endif
	
}

bool Cascades::touchDown(float x, float y, int touchId)
{
	
#ifdef DEBUG
	if(bodyShape) {
		bodyShape->destroy();
	
		delete bodyShape;
	}
	
	bodyShape = new ofxBox2dPolygon();
	
	ofVec2f ul( x - 50.f, y-50.f);
	ofVec2f ur( x + 50.f, y-50.f);
	ofVec2f lr( x + 50.f, y+50.f);
	ofVec2f ll( x - 50.f, y+50.f);
	
	bodyShape->addTriangle(ul, ur, lr);
	bodyShape->addTriangle(ul, ll, lr);

	bodyShape->create(box2d.getWorld());
#endif
	
}

bool Cascades::touchUp(float x, float y, int touchId)
{
}

bool Cascades::touchMoved(float x, float y, int touchId)
{
}

