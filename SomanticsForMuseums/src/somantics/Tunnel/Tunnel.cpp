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

#include "Tunnel.h"
#include "constants.h"
#include "Settings.h"
#ifdef _WIN32
#include "gui/ColorPicker.h"
#else
#include "ColorPicker.h"
#endif
#ifndef TARGET_OF_IPHONE
#include "contourutils.h"
#endif
#define BRUSHED_LINE_SIZE 6
//--------------------------------------------------------------
void Tunnel::setup(){

	Silhouette::setup();

	ofEnableNormalizedTexCoords();
	brushedLine.setup(ImageCache::getImage("img/blob.png"), BRUSHED_LINE_SIZE);
}

//--------------------------------------------------------------
void Tunnel::update(){
	// take the snapshots and make them bigger
	for(int i = 0; i < history.size(); i++) {
		ofVec2f centre;
		for(int k = 0; k < history[i].size(); k++) {
			centre += history[i][k];
		}
		centre /= history[i].size();
		float maxDistSquared = 0;
		for(int k = 0; k < history[i].size(); k++) {
			ofVec2f dist = history[i][k] - centre;
			dist.normalize();
			history[i][k] -= dist*7;
			float distSquared = centre.distanceSquared(history[i][k]);
			if(maxDistSquared<distSquared) {
				maxDistSquared = distSquared;
			}
		}
		if(maxDistSquared<400) {
			history.erase(history.begin()+i);
			i--;
		}
		//printf("max dist: %f\n", maxDistSquared);

	}
#ifndef TARGET_OF_IPHONE
	if(threshImg!=NULL) {
		contourFinder.findContours(*threshImg, 20*20, VISION_WIDTH*VISION_HEIGHT, 20, false);
	}

#endif
}
int cc = 0;
//--------------------------------------------------------------
void Tunnel::draw(){
	ofBackground(0,0,0); // just to confirm we have something going on
	while(history.size()>20) {
		history.erase(history.begin());
	}

	ofSetHexColor(0xFFFFFF);
	int colorIndex = Settings::getInstance()->settings["fgColor"];



	for(int i = 0; i < history.size(); i++) {
		ofColor c;
		if(colorIndex==20) {
			float h = ofMap(i, history.size()-40, history.size(), 0, 255, true);
			h = (history.size()-i)*15;
			c.setHsb(h, 255, 255);
		} else {
			c.setHex(ColorPicker::colors[colorIndex]);
			c.setBrightness(ofMap(i, 0, 12, 0, 200, true));
		}
		ofSetColor(c);
		brushedLine.drawLines(history[i], true);
	}

#ifndef TARGET_OF_IPHONE
	silhouettes.clear();
	Silhouette s;

	vector<ofVec2f> points, hull;
	for(int i = 0; i < contourFinder.blobs.size(); i++) {


		for(int j = 0; j < contourFinder.blobs[i].pts.size(); j++) {
			ofVec2f point;
			point.x = contourFinder.blobs[i].pts[j].x*WIDTH/VISION_WIDTH;
			point.y = contourFinder.blobs[i].pts[j].y*HEIGHT/VISION_HEIGHT;
			points.push_back(point);
		}
	}

	tricks::math::calcConvexHull(points, hull);

	ofVec2f *p = new ofVec2f[hull.size()];
	for(int j = 0; j < hull.size(); j++) {
		p[j] = hull[j];
	}

	if(colorIndex==20) {
		ofSetColor(255, 0, 0);
	} else {
		ofSetHexColor(ColorPicker::colors[colorIndex]);
	}
	s.setSize(BRUSHED_LINE_SIZE);
	s.draw(p, hull.size());
	delete [] p;
	cc++;
	if(cc%10==0)
		history.push_back(hull);

	/*if(colorImg!=NULL) {
		ofEnableAlphaBlending();
		glColor4f(1, 1, 1, 0.1);
		glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR);
		colorImg->draw(0, 0, WIDTH, HEIGHT);
		ofEnableAlphaBlending();
	}*/
#else


	for(int i = 0; i < silhouettes.size(); i++) {
		ofSetColor(255, 0, 0);
		silhouettes[i].draw();
		if(silhouettes[i].dead()) {
			silhouettes.erase(silhouettes.begin()+i);
			i--;
		} else {
			cc++;
			if(cc%4==0)
				history.push_back(silhouettes[i].getSnapshot());
		}
	}
#endif
}

bool Tunnel::touchDown(float x, float y, int touchId) {
#ifdef TARGET_OF_IPHONE
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchDown(x,y,touchId)) {
			return true;
		}
	}
	silhouettes.push_back(Silhouette());
	silhouettes.back().setSize(BRUSHED_LINE_SIZE);
	silhouettes.back().touchDown(x, y, touchId);
	touches[touchId] = ofVec2f(x, y);
#endif
	return true;
}

bool Tunnel::touchUp(float x, float y, int touchId) {
#ifdef TARGET_OF_IPHONE
	touches.erase(touchId);
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchUp(touchId)) {

			return true;
		}
	}
#endif
	return true;
}

bool Tunnel::touchMoved(float x, float y, int touchId) {
#ifdef TARGET_OF_IPHONE
	touches[touchId].x = x;
	touches[touchId].y = y;
	for(int i = 0; i < silhouettes.size(); i++) {
		if(silhouettes[i].touchMoved(x, y, touchId)) {
			return true;
		}
	}
#endif
	return true;
}

