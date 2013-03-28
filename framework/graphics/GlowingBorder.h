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
 *  GlowingBorder.h
 *  emptyExample
 *
 *  Created by Marek Bereza on 26/01/2011.
 *  Copyright 2011 Marek Bereza. All rights reserved.
 *
 */
#include "ofVec2f.h"
#pragma once
/**
 * This creates a glowing border around a polygon
 */
class GlowingBorder {
public:
	
	
	GlowingBorder() {
		normals				= NULL;
		cornerCoordCounts	= NULL;
		cornerCoords		= NULL;
		cornerTexCoords		= NULL;
		edgeCoords			= NULL;
		edgeTexCoords		= NULL;
		
	}
	
	~GlowingBorder() {
		if(normals!=NULL) {
			delete [] normals;
			delete [] cornerCoordCounts;
			delete [] points;
			for(int i = 0; i < numPoints; i++) {
				delete [] edgeCoords[i];
				delete [] edgeTexCoords[i];
				delete [] cornerCoords[i];
				delete [] cornerTexCoords[i];
			}
			delete [] edgeCoords;
			delete [] edgeTexCoords;
			delete [] cornerCoords;
			delete [] cornerTexCoords;
		}
	}

	// set shouldNormalizeTexCoords to true if on iPhone.
	void setup(ofImage *img, int numPoints) {

		this->img = img;
		this->numPoints = numPoints;
		this->radius = this->img->getWidth()/2;
		//this->img->setAnchorPercent(0.5, 0.5);
		// allocate memory for all data needed
		points = new ofVec2f[numPoints];
		normals = new ofVec2f[numPoints];
		cornerCoordCounts = new int[numPoints];
		
		edgeCoords = new ofVec2f*[numPoints];
		edgeTexCoords = new ofVec2f*[numPoints];
		
		cornerCoords = new ofVec2f*[numPoints];
		cornerTexCoords = new ofVec2f*[numPoints];
		
		
		for(int i = 0; i < numPoints; i++) {
			edgeCoords[i]		= new ofVec2f[4];
			edgeTexCoords[i]	= new ofVec2f[4];
			cornerCoords[i]		= new ofVec2f[7];
			cornerTexCoords[i]	= new ofVec2f[7];
		}
		
	}
	
	
	
	
	
	float normalizeAngle(float angle) {
		if(angle>0) {
			while(angle>PI) {
				angle -= PI*2;
			}
		} else {
			while(angle<-PI) {
				angle += PI*2;
			}
		}
		return angle;
	}
	
#define SQUARE_ERROR 0
#define SQUARE_RIGHT 1
#define SQUARE_TOP 2
#define SQUARE_BOTTOM 3
#define SQUARE_LEFT 4
	
	
	bool lineSegmentIntersection(ofVec2f line1Start, ofVec2f line1End, ofVec2f line2Start, ofVec2f line2End, ofVec2f & intersection){
		ofVec2f diffLA, diffLB;
		float compareA, compareB;
		diffLA = line1End - line1Start;
		diffLB = line2End - line2Start;
		compareA = diffLA.x*line1Start.y - diffLA.y*line1Start.x;
		compareB = diffLB.x*line2Start.y - diffLB.y*line2Start.x;
		if (
			(
			 ( ( diffLA.x*line2Start.y - diffLA.y*line2Start.x ) < compareA ) ^
			 ( ( diffLA.x*line2End.y - diffLA.y*line2End.x ) < compareA )
			 )
			&&
			(
			 ( ( diffLB.x*line1Start.y - diffLB.y*line1Start.x ) < compareB ) ^
			 ( ( diffLB.x*line1End.y - diffLB.y*line1End.x) < compareB )
			 )
			)
		{
			float lDetDivInv = 1 / ((diffLA.x*diffLB.y) - (diffLA.y*diffLB.x));
			intersection.x =  -((diffLA.x*compareB) - (compareA*diffLB.x)) * lDetDivInv ;
			intersection.y =  -((diffLA.y*compareB) - (compareA*diffLB.y)) * lDetDivInv ;
			
			return true;
		}
		
		return false;
	}

	
	
	int findIntersection(float alpha, ofVec2f a, float radius, ofVec2f &intersection) {
		// left
		if(alpha>-3*PI/4 && alpha<-PI/4) {
			if(lineSegmentIntersection(ofVec2f(), a, ofVec2f(-radius, -radius), ofVec2f(-radius, radius), intersection)) {
				return SQUARE_LEFT;
			}
			// bottom
		} else if(alpha<-3*PI/4 || alpha>3*PI/4) {
			if(lineSegmentIntersection(ofVec2f(), a, ofVec2f(-radius, radius), ofVec2f(radius, radius), intersection)) {
				return SQUARE_BOTTOM;
			}
			// right
		} else if(alpha>PI/4 && alpha<3*PI/4) {
			if(lineSegmentIntersection(ofVec2f(), a, ofVec2f(radius, radius), ofVec2f(radius, -radius), intersection)) {
				return SQUARE_RIGHT;
			}
			// top
		} else if(alpha>-PI/4 && alpha<PI/4) {
			if(lineSegmentIntersection(ofVec2f(), a, ofVec2f(radius, -radius), ofVec2f(-radius, -radius), intersection)) {
				return SQUARE_TOP;
			}
		}
		return SQUARE_ERROR;
	}
	
	
		
	

	
	void drawEdges() {
		for(int i = 0; i < numPoints; i++) {
			glVertexPointer(2, GL_FLOAT, 0, &edgeCoords[i][0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &edgeTexCoords[i][0]);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
	}
	
	
	void drawCorners() {
		for(int i = 0; i < numPoints; i++) {
			glPushMatrix();
			glTranslatef(points[i].x, points[i].y, 0);
			glVertexPointer(2, GL_FLOAT, 0, &cornerCoords[i][0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &cornerTexCoords[i][0]);
			glDrawArrays(GL_TRIANGLE_FAN, 0, cornerCoordCounts[i]);
			glPopMatrix();
		}		
	}

	void calculateNormals() {
		for(int i = 0; i < numPoints; i++) {
			normals[i] = points[(i+1)%numPoints] - points[i];
			normals[i] = ofVec2f(normals[i].y, -normals[i].x);
			normals[i].normalize();
		}
	}
	
	
	void calculateEdges() {
		for(int i = 0; i < numPoints; i++) {
			ofVec2f o1, o2;
			
			ofVec2f a = points[i];
			ofVec2f b = points[(i+1)%numPoints];
			
			o1 = a + normals[i]*radius;
			o2 = b + normals[i]*radius;
			ofVec2f topTexCoord(radius, 0);
			
			topTexCoord.rotateRad(1, ofVec2f( radius, radius));

			edgeTexCoords[i][0] = ofVec2f(topTexCoord.x, topTexCoord.y);
			edgeCoords[i][0] = ofVec2f(o1.x, o1.y);
			edgeTexCoords[i][1] = ofVec2f(radius, radius);
			edgeCoords[i][1] = ofVec2f(a.x, a.y);
			edgeTexCoords[i][2] = ofVec2f(topTexCoord.x, topTexCoord.y);
			edgeCoords[i][2] = ofVec2f(o2.x, o2.y);
			edgeTexCoords[i][3] = ofVec2f(radius, radius);
			edgeCoords[i][3] = ofVec2f(b.x, b.y);
		}
	}
	
	void calculateAngles() {
		// cache the angles here for calculateEdges and calculateCorners
		
	}
	
	
	
	
	void calculateRectSegment(int pointId, float alpha, float beta) {
		
		ofVec2f centre = points[pointId];
		
		// normalize angles to -PI<angle<PI
		alpha = normalizeAngle(alpha);
		beta = normalizeAngle(beta);
		
		
		ofVec2f a(0, -radius*2);
		ofVec2f b(0, -radius*2);
		a.rotateRad(alpha);
		b.rotateRad(beta);
		

		ofVec2f intersectionA, intersectionB;
		
		
		int sideA = findIntersection(alpha, a, radius, intersectionA);
		int sideB = findIntersection(beta, b, radius, intersectionB);
		
		int currSide = sideA;

			
		int pos = 0;
		
		cornerTexCoords[pointId][pos] = ofVec2f(radius, radius);
		cornerCoords[pointId][pos] = ofVec2f(0, 0);
		pos++;
		cornerTexCoords[pointId][pos] = ofVec2f(intersectionA.x+radius, intersectionA.y+radius);
		cornerCoords[pointId][pos] = ofVec2f(intersectionA.x, intersectionA.y);
		pos++;
		if(sideA!=SQUARE_ERROR && sideB!=SQUARE_ERROR) {
			while(currSide!=sideB) {
				// draw the side, 
				if(currSide==SQUARE_LEFT) {
					cornerTexCoords[pointId][pos] = ofVec2f(0, 0);
					cornerCoords[pointId][pos] = ofVec2f(-radius, -radius);
					pos++;
					currSide = SQUARE_TOP;
				} else if(currSide==SQUARE_TOP) {
					cornerTexCoords[pointId][pos] = ofVec2f(radius*2, 0);
					cornerCoords[pointId][pos] = ofVec2f(radius, -radius);
					pos++;
					currSide = SQUARE_RIGHT;
				} else if(currSide==SQUARE_RIGHT) {
					cornerTexCoords[pointId][pos] = ofVec2f(radius*2, radius*2);
					cornerCoords[pointId][pos] = ofVec2f(radius, radius);
					pos++;
					currSide = SQUARE_BOTTOM;
				} else if(currSide==SQUARE_BOTTOM) {
					cornerTexCoords[pointId][pos] = ofVec2f(0, radius*2);
					cornerCoords[pointId][pos] = ofVec2f(-radius, radius);
					pos++;
					currSide = SQUARE_LEFT;
				}
			}
		}
		
		cornerTexCoords[pointId][pos] = ofVec2f(intersectionB.x+radius, intersectionB.y+radius);
		cornerCoords[pointId][pos] = ofVec2f(intersectionB.x, intersectionB.y);
		pos++;
		cornerCoordCounts[pointId] = pos;
	}
	
	
	
	void calculateCorners() {
		
		// draw fluff on the 3 corners
		for(int i = 0; i < numPoints; i++) {
			
			int pointBefore = i-1;
			if(pointBefore<0) pointBefore += numPoints;
			ofVec2f normal = normals[pointBefore];
			
			float alpha = atan2(normal.y,normal.x)   + PI/2;
			float beta = atan2(normals[i].y,normals[i].x) + PI/2;
			
			calculateRectSegment(i, alpha, beta);
		}
		
	}
	
	
	
	void normalizeTexCoords() {
		for(int i = 0; i < numPoints; i++) {
			for(int j = 0; j < 4; j++) {
				edgeTexCoords[i][j].x /= radius*2;
				edgeTexCoords[i][j].y /= radius*2;
			}
			
			for(int j = 0; j < cornerCoordCounts[i]; j++) {
				cornerTexCoords[i][j].x /= radius*2;
				cornerTexCoords[i][j].y /= radius*2;
			}
		}
	}
	
	void checkWinding() {
		
		ofVec2f a = points[1] - points[0];
		ofVec2f b = points[2] - points[0];
		float z = (a.x*b.y) - (a.y*b.x);
		
		// if the z of the cross product is negative, we need to reverse the winding
		if(z<0) {
			unsigned short int a=0;
			unsigned short int b=numPoints;
			ofVec2f swap;
			
			for(a;a<--b;a++) //increment a and decrement b until they meet eachother
			{
				swap=points[a];       //put what's in a into swap space
				points[a]=points[b];    //put what's in b into a
				points[b]=swap;       //put what's in the swap (a) into b
			}
		}
		
	}
	

	
	// works for 3 or 4 points. More, I don't know.
	void draw(ofVec2f *points, ofColor c) {
		for(int i = 0; i < numPoints; i++) {
			this->points[i] = points[i];
		}
		// gots to be clockwise!!
		checkWinding();
		
		calculateNormals();
		calculateAngles();
		calculateCorners();
		calculateEdges();

		normalizeTexCoords();

		
		
		
		ofEnableNormalizedTexCoords();
		color = c;
		ofSetColor(c.r, c.g, c.b, c.a);
		img->getTextureReference().bind();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		drawCorners();
		drawEdges();
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		img->getTextureReference().unbind();
		
		
		
	}
private:
	ofImage *img;
	float radius;
	ofVec2f *normals;
	ofVec2f *points;
	ofVec2f **edgeCoords;
	ofVec2f **edgeTexCoords;
	
	ofVec2f **cornerCoords;
	ofVec2f **cornerTexCoords;
	int *cornerCoordCounts;

	
	int numPoints;
	ofColor color;

};