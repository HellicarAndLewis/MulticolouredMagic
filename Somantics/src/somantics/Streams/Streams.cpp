/*
 *  Streams.cpp
 *  SomanticsMac
 *
 *
 */

#include "Streams.h"

void Streams::setup()
{
	
}

void Streams::update()
{

	vector<ofPoint>::iterator ip = lLine.getVertices().begin();
	while( ip != lLine.getVertices().end() ) {
		ip->y -= 1;
		++ip;
	}
	
	
	ip = rLine.getVertices().begin();
	while( ip != rLine.getVertices().end() ) {
		ip->y -= 1;
		++ip;
	}

	lHue+=0.001f;
	rHue+=0.001f;
	
	if(lHue > 254.f) {
		lHue+=0.f;
	}
	
	if(rHue > 254.f) {
		rHue+=0.f;
	}
	
	lColor.setHue(lHue);
	rColor.setHue(rHue);
}

void Streams::draw()
{
	ofSetColor(lColor);
	lLine.draw();
	
	ofSetColor(rColor);
	rLine.draw();
}

bool Streams::touchDown(float x, float y, int touchId)
{
	if( lLine.size() < 0 ) {
		ofPoint l(x, y);
		lLine.addVertex(l);
	} else if( rLine.size() < 0 ) {
		ofPoint r(x, y);
		rLine.addVertex(r);
	} else {
		
		float lDist = ofDist(lLine.getVertices().back().x, lLine.getVertices().back().y, x, y);
		float rDist = ofDist(rLine.getVertices().back().x, rLine.getVertices().back().y, x, y);
		
		if(  lDist < rDist ) {
			ofPoint l(x, y);
			lLine.addVertex( l );
		} else {
			ofPoint r(x, y);
			rLine.addVertex( r );
		}
		
	}
}

bool Streams::touchUp(float x, float y, int touchId)
{
}

bool Streams::touchMoved(float x, float y, int touchId)
{
	if( lLine.size() < 0 ) {
		ofPoint l(x, y);
		lLine.addVertex(l);
	} else if( rLine.size() < 0 ) {
		ofPoint r(x, y);
		rLine.addVertex(r);
	} else {
		
		float lDist = ofDist(lLine.getVertices().back().x, lLine.getVertices().back().y, x, y);
		float rDist = ofDist(rLine.getVertices().back().x, rLine.getVertices().back().y, x, y);
		
		if(  lDist < rDist ) {
			ofPoint l(x, y);
			lLine.addVertex( l );
		} else {
			ofPoint r(x, y);
			rLine.addVertex( r );
		}
		
	}
}
