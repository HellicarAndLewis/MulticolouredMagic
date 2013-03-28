/**
 * == Simplified BSD *** MODIFIED FOR NON-COMMERCIAL USE ONLY!!! *** ==
 * Copyright (c) 2011, Cariad Interactive LTD
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice, this list of 
 *     conditions and the following disclaimer.
 * 
 *   * Redistributions in binary form must reproduce the above copyright notice, this list of 
 *     conditions and the following disclaimer in the documentation and/or other materials provided 
 *     with the distribution.
 * 
 *   * Any redistribution, use, or modification is done solely for personal benefit and not for any 
 *     commercial purpose or for monetary gain
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
