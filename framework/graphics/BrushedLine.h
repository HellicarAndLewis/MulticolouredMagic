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
 *  BrushedLine.h
 *  iPhoneEmptyExample
 *
 *  Created by Marek Bereza on 28/01/2011.
 *  Copyright 2011 Marek Bereza. All rights reserved.
 *
 */

/**
 * This class lets you draw a line with an image 
 * and it'll stretch it across the line to give 
 * you a nice smoothed stroke.
 *
 * see: http://answers.oreilly.com/topic/949-how-to-work-around-the-iphones-anti-aliasing-limitations/
 */
#pragma once
#include "ofMain.h"

class BrushedLine {
public: 
	BrushedLine() {
		img = NULL;
		size = 10;
		
		// texcoords are always the same.
		texCoords[0] = ofVec2f(0, 1);
		texCoords[1] = ofVec2f(0, 0);
		texCoords[2] = ofVec2f(0.5, 1);
		texCoords[3] = ofVec2f(0.5, 0);
		texCoords[4] = ofVec2f(0.5, 1);
		texCoords[5] = ofVec2f(0.5, 0);
		texCoords[6] = ofVec2f(1, 1);
		texCoords[7] = ofVec2f(1, 0);
		imageBound = false;
		
	}
	void setup(ofImage *img, float size) {
		this->img = img;
		this->size = size;
	}
	
	void drawLine(ofVec2f &a, ofVec2f &b) {
		bool mustUnbind = false;
		if(!imageBound) {
			bindImage();
			mustUnbind = true;
		}
		ofVec2f E = (b - a).getNormalized() * size;
		ofVec2f N = ofVec2f(-E.y, E.x);
		ofVec2f S = -N;
		ofVec2f NE = N + E;
		ofVec2f NW = N - E;
		ofVec2f SW = -NE;
		ofVec2f SE = -NW;
		coords[0] = (a + SW);
		coords[1] = (a + NW);
		coords[2] = (a + S);
		coords[3] = (a + N);
		coords[4] = (b + S);
		coords[5] = (b + N);
		coords[6] = (b + SE);
		coords[7] = (b + NE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glVertexPointer(2, GL_FLOAT, 0, &coords[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		if(mustUnbind) unbindImage();
		
	}
	
	void drawLines(vector<ofVec2f> &points, bool close = false) {
		bindImage();
		for(int i = 0; i+1 < points.size(); i++) {
			ofVec2f a = points[i];
			ofVec2f b = points[i+1];
			
			drawLine(points[i], points[i+1]);
		}
		
		// close the loop if necessary.
		if(close) {
			drawLine(points[0], points[points.size()-1]);
		}
		unbindImage();
	}
	void drawLines(ofVec2f *points, int numPoints, bool close = false) {
		
		bindImage();
		for(int i = 0; i+1 < numPoints; i++) {
			ofVec2f a = points[i];
			ofVec2f b = points[i+1];
			
			drawLine(points[i], points[i+1]);
			
			
		}
		
		// close the loop if necessary.
		if(close) {
			drawLine(points[0], points[numPoints-1]);
		}
		unbindImage();
	}
	void setSize(float size) {
		this->size = size;
	}
	float size;
private:
	
	void bindImage() {
		if(!imageBound) {
			imageBound = true;
			img->getTextureReference().bind();
		}
	}
	
	void unbindImage() {
		if(imageBound) {
			img->getTextureReference().unbind();
			imageBound = false;
		}
	}
	
	bool imageBound;
	ofImage *img;
	
	ofVec2f texCoords[8];
	ofVec2f coords[8];
};