//
//  MagicShapes.cpp
//  magic
//
//  Created by Joel Gethin Lewis on 13/04/2011.
//  Copyright 2011 Hellicar&Lewis. All rights reserved.
//

#include "MagicShapes.h"
#include "ofxDisplayList.h"

ofxDisplayList *heartDisplayList = NULL;


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

void drawHeart(ofVec2f centre, float size, float rotation) {
    // from: http://www.wolframalpha.com/input/?i=%281-%28|x|-1%29^2%29^0.5%3D-3%281-%28|x|%2F2%29^0.5%29^0.5
    
	if(heartDisplayList==NULL) {
		heartDisplayList = new ofxDisplayList();
		heartDisplayList->begin(false);

		ofBeginShape();
		
		for(float x = -2; x <= 2; x += 0.05) {
			float xx = ABS(x) - 1;
			xx *= xx;
			float y = sqrt(1 - xx);
			ofVertex(x, y-0.01);
		}
		
		ofEndShape(true);
		
		ofBeginShape();
		float sqrt2Inv = 1.f/sqrt(2);
		for(float x = -2; x <= 2; x += 0.05) {
			float xx = sqrt(ABS(x))*sqrt2Inv;
			float y = -3*sqrt(1 - xx);
			ofVertex(x, y);
		}
		
		ofEndShape(true);
		heartDisplayList->end();
	}
	glPushMatrix();
    glTranslatef(centre.x, centre.y, 0);
    if(rotation==0) glRotatef(rotation, 0, 0, 1);
    glScalef(size*0.25, -size*0.25, 1);
    glTranslatef(0, 1, 0);
	heartDisplayList->draw();
    glPopMatrix();
 
}

void drawHexagon(ofVec2f centre, float size, float rotation) {
    
    float v = 0.433;
    
    glPushMatrix();
    glTranslatef(centre.x, centre.y, 0);
    if(rotation==0) glRotatef(rotation, 0, 0, 1);
    glScalef(size, size, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    glVertex2f(0.5, 0);
    glVertex2f(0.25, -v);
    glVertex2f(-0.25, -v);
    glVertex2f(-0.5, 0);
    glVertex2f(-0.25, v);
    glVertex2f(0.25, v);
    glVertex2f(0.5, 0);
    glEnd();
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


