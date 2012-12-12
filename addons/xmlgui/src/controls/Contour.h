/*
 *  GuiADSR.h
 *  Gui
 *
 *  Created by Marek Bereza on 27/04/2010.
 *
 */

#pragma once

#include "LabeledControl.h"


class xPoint: public ofPoint {

public:
	bool selected;
	xPoint(float _x, float _y, bool _selected) { x = _x; y = _y; selected = _selected; }
	bool operator<(const xPoint &rhs) const { return x < rhs.x; }
};

class Contour: public LabeledControl {
public:

	int bgColor;
	ofImage *bgImg, *pointImg, *pointDownImg;
	string bgImgUrl, pointImgUrl, pointDownImgUrl;
	float pointRadius;
	int pointCount;
	int movingPoint;
	int numPoints;
	bool endsMovable;
	int pointColor;

	Contour(): LabeledControl() {
		movingPoint = -1;
		bgColor = 0x505050;
		pointColor = 0xFF0000;
		height = 40;
		width = 70;
		endsMovable = false;

		pointRadius = 5;
		value = new float[12];

		// this one is fixed
		faval(value, 0) = 0.0;
		faval(value, 1) = 0.0;

		faval(value, 2) = 0.2;
		faval(value, 3) = 0.2;

		faval(value, 4) = 0.3;
		faval(value, 5) = 0.3;


		faval(value, 6) = 0.4;
		faval(value, 7) = 0.4;

		faval(value, 8) = 0.4;
		faval(value, 9) = 0.4;

		faval(value, 10) = 1.0;
		faval(value, 11) = 0.0;

		numPoints = pointCount = 6;


		pointDownImg = pointImg = bgImg = NULL;
		pointDownImgUrl = pointImgUrl = bgImgUrl = "";
	}

	void load() {
		bgImg = xmlgui::Resources::getImage(bgImgUrl);
		pointImg = xmlgui::Resources::getImage(pointImgUrl);
		pointDownImg = xmlgui::Resources::getImage(pointDownImgUrl);

		if(bgImg!=NULL) {
			scalable = false;
			width = bgImg->getWidth();
			height = bgImg->getHeight();
		}

		if(pointImg!=NULL) pointImg->setAnchorPercent(0.5, 0.5);
		if(pointDownImg!=NULL) pointDownImg->setAnchorPercent(0.5, 0.5);

		// if there's a new number of points, then
		// change the size of the array to match
		if(numPoints!=pointCount) {
			float *newPoints = new float[numPoints*2];
			for(int i = 0; i < numPoints; i++) {
				if(i<pointCount) {
					newPoints[i*2] = faval(value, i*2);
					newPoints[i*2+1] = faval(value, i*2+1);
				} else {
					newPoints[i*2] = 1;
					newPoints[i*2+1] = 0;
				}
			}
			pointCount = numPoints;
			delete [] (float*)(value);
			value = newPoints;
			// make sure the last point is at the end, at the bottom
			newPoints[(pointCount-1)*2] = 1;
			newPoints[(pointCount-1)*2+1] = 0;
		}


	}

	void draw() {

		if(bgImg!=NULL) {
			ofSetHexColor(0xFFFFFF);
			bgImg->draw(x, y);
		} else {
			setRGBA(bgColor);
			ofFill();
			ofRect(x, y, width, height);
		}

		if(pointCount>0) {
			ofSetHexColor(0xFFFFFF);
			float lastX = x + width*(faval(value, 0));
			float lastY = y + height*(1-faval(value, 1));
			for(int i = 1; i < pointCount; i++) {
				float xx = x + width*(faval(value, i*2));
				float yy = y + height*(1-faval(value, i*2 + 1));
				ofLine(xx, yy, lastX, lastY);
				lastX = xx;
				lastY = yy;
			}



			int start = 1;
			int end = pointCount-1;

			if(endsMovable) {
				start = 0;
				end = pointCount;
			}

			for(int i = start; i < end; i++) {
				float xx = x + width*(faval(value, i*2));
				float yy = y + height*(1-faval(value, i*2 + 1));

				if(i==movingPoint) {
					if(pointDownImg!=NULL) {
						pointDownImg->draw(xx, yy);
					} else {
						ofSetHexColor(0xFFFFFF);
						ofCircle(xx, yy, pointRadius);

					}
				} else {
					if(pointImg!=NULL) {
						pointImg->draw(xx, yy);
					} else {
						setRGBA(pointColor);
						ofCircle(xx, yy, pointRadius);
					}
				}

			}
		}

		ofSetColor(255, 255, 255);
		drawLabel(x+3, y+14);
	}



	bool touchDown(int _x, int _y, int button) {

		float radSqr = pointRadius*pointRadius;

		int start = 1;
		int end = pointCount-1;

		if(endsMovable) {
			start = 0;
			end = pointCount;
		}

		for(int i = start; i < end; i++) {
			float pX = x + width*(faval(value, i*2));
			float pY = y + height*(1-faval(value, i*2+1));
			if((pX-_x)*(pX-_x) + (pY-_y)*(pY-_y)<radSqr) {
				movingPoint = i;
				return true;
			}
		}
		return true;
	}

	bool touchMoved(int _x, int _y, int button) {
		if(movingPoint!=-1) {

			if(!(endsMovable && (movingPoint==0||movingPoint==pointCount-1))) faval(value, movingPoint*2) = (_x-x)/width;
			faval(value, movingPoint*2+1) = 1-(_y-y)/height;
			vector<xPoint> sortedPoints;
			for(int i = 0; i < pointCount; i++) {
				sortedPoints.push_back(xPoint(faval(value, i*2), faval(value, i*2+1), i==movingPoint));
			}
			sort(sortedPoints.begin(), sortedPoints.end());
			for(int i = 0; i < pointCount; i++) {
				faval(value, i*2) = sortedPoints[i].x;
				faval(value, i*2+1) = sortedPoints[i].y;
				if(sortedPoints[i].selected) movingPoint = i;
			}
		}
		return true;
	}
	bool touchUp(int _x, int _y, int button) {
		movingPoint = -1;
		return false;
	}

	virtual void getParameterInfo(vector<ParameterInfo> &params) {
		LabeledControl::getParameterInfo(params);
		params.push_back(ParameterInfo("BG Color", "bgColor", "colourpicker", &bgColor));
		params.push_back(ParameterInfo("Point Color", "pointColor", "colourpicker", &pointColor));
		params.push_back(ParameterInfo("BG Image", "bgImgUrl", "file", &bgImgUrl));
		params.push_back(ParameterInfo("Point Image", "pointImgUrl", "file", &pointImgUrl));
		params.push_back(ParameterInfo("Point Down Image", "pointDownImgUrl", "file", &pointDownImgUrl));
		params.push_back(ParameterInfo("Hit Radius", "hitRadius", "floatfield", &pointRadius));
		params.push_back(ParameterInfo("# of points", "numPoints", "intfield", &numPoints));
		params.push_back(ParameterInfo("Ends Movable", "endsMovable", "toggle", &endsMovable));
	}

	string valueToString() {
		string s = "";
		for(int i = 0; i < pointCount; i++) {
			s += ofToString(faval(value, i*2)) + "," + ofToString(faval(value, i*2 + 1));
			if(i+1<pointCount) s += ",";
		}
		return s;

	}
	void valueFromString(string inp) {
		vector<string> vals = ofSplitString(inp, ",");
		if(vals.size()%2==0 && vals.size()>0) {
			pointCount = vals.size()/2;
			if(value!=NULL) {
				delete [] (float*)value;
			}
			value = new float[pointCount*2];

			for(int i = 0; i < vals.size(); i++) {
				faval(value, i) = atof(vals[i].c_str());
			}
		}

	}
};
