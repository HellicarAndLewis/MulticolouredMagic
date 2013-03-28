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

//
//  MagicShapes.cpp
//  magic
//
//  Created by Joel Gethin Lewis on 13/04/2011.
//  Copyright 2011 Hellicar&Lewis. All rights reserved.
//

#include "MagicShapes.h"
//#include "ofxDisplayList.h"

//ofxDisplayList *heartDisplayList = NULL;
ofPath *heartDisplayList = NULL;

void drawTriangle(ofVec2f centre, float size, float rotation) {
    size *= 1.15;
    glPushMatrix();
    glTranslatef(centre.x, centre.y, 0);
    if(rotation==0) glRotatef(rotation, 0, 0, 1);
    glScalef(size, size, 1);
    ofBeginShape();
    ofVertex(0, 0.866*-0.5);
    ofVertex(0.5, 0.866*0.5);
    ofVertex(-0.5, 0.866*0.5);
    ofEndShape(true);
    glPopMatrix();
}

void drawCircle(ofVec2f centre, float size, float rotation) {
    ofCircle(centre, size*0.5);
}

void drawCross(ofVec2f centre, float size, float rotation) {
    glPushMatrix();
    glTranslatef(centre.x, centre.y, 0);
    // rotate 45 degrees
    glRotatef(rotation+45, 0, 0, 1);
    glScalef(size, size, 1);
    float strokeWidth = 0.32;
    ofRect(-0.5, -0.5*strokeWidth, 1, strokeWidth);
    ofRect(-0.5*strokeWidth, -0.5, strokeWidth, 1);
    glPopMatrix();
    
    
    
}
float heart1(float x) {
	float xx = ABS(x) - 1;
	xx *= xx;
	float y = sqrt(1 - xx);
	return y-0.01;
}
float heart2(float x) {
	float sqrt2Inv = 1.f/sqrt(2);
	float xx = sqrt(ABS(x))*sqrt2Inv;
	float y = -3*sqrt(1 - xx);
	return y;
}
void drawHeart(ofVec2f centre, float size, float rotation) {
    // from: http://www.wolframalpha.com/input/?i=%281-%28|x|-1%29^2%29^0.5%3D-3%281-%28|x|%2F2%29^0.5%29^0.5

	float f[4];
	glGetFloatv(GL_CURRENT_COLOR, f);
	
	if(heartDisplayList==NULL) {
		heartDisplayList = new ofPath();
		heartDisplayList->moveTo(-2, heart1(-2));
		
		
		for(float x = -1.95; x <= 2; x += 0.05) {
			heartDisplayList->lineTo(x, heart1(x));
		}
		
		for(float x = 2; x >= -1.95; x -= 0.05) {
			heartDisplayList->lineTo(x, heart2(x));
		}
	}
	glPushMatrix();
    glTranslatef(centre.x, centre.y, 0);
    if(rotation==0) glRotatef(rotation, 0, 0, 1);
    glScalef(size*0.25, -size*0.25, 1);
    glTranslatef(0, 1, 0);
	heartDisplayList->setFillColor(ofColor(f[0]*255, f[1]*255, f[2]*255, 255));
	heartDisplayList->draw();
    glPopMatrix();
 
}

void drawHexagon(ofVec2f centre, float size, float rotation) {
    
    float v = 0.433;
    
    glPushMatrix();
    glTranslatef(centre.x, centre.y, 0);
    if(rotation==0) glRotatef(rotation, 0, 0, 1);
    glScalef(size, size, 1);
	ofVec2f points[8];
	points[0] = ofVec2f(0, 0);
    points[1] = ofVec2f(0.5, 0);
    points[2] = ofVec2f(0.25, -v);
    points[3] = ofVec2f(-0.25, -v);
    points[4] = ofVec2f(-0.5, 0);
    points[5] = ofVec2f(-0.25, v);
    points[6] = ofVec2f(0.25, v);
    points[7] = ofVec2f(0.5, 0);
	
	
	
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer(2, GL_FLOAT, 0, points );
	
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, 8);
    glPopMatrix();

}
void drawSquare(ofVec2f centre, float size, float rotation) {
    glPushMatrix();
    glTranslatef(centre.x, centre.y, 0);
    if(rotation==0) glRotatef(rotation, 0, 0, 1);
    glScalef(size, size, 1);
    ofRect(-0.5, -0.5, 1, 1);
    glPopMatrix();
}



void drawShape(int type, ofVec2f centre, float size, float rotation) {
	if(type>=NUM_MAGIC_SHAPES || type<0) {
		printf("drawShape() - invalid shape: %d\n", type);
		return;
	}
	
	switch(type) {
		case MAGIC_CIRCLE:
			drawCircle(centre, size, rotation);
			break;
			
		case MAGIC_TRIANGLE:
			drawTriangle(centre, size, rotation);
			break;
			
		case MAGIC_CROSS:
			drawCross(centre, size, rotation);
			break;
			
		case MAGIC_HEART:
			drawHeart(centre, size, rotation);
			break;
			
		case MAGIC_HEXAGON:
			drawHexagon(centre, size, rotation);
			break;
			
		case MAGIC_SQUARE:
			drawSquare(centre, size, rotation);
			break;
			
		default:
			drawCircle(centre, size, rotation);
			break;
	}
}


