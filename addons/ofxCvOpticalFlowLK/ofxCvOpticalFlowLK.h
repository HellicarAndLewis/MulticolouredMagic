//
// ofxCvOpticalFlowLK.h - a OpenCV cvOpticalFlowLK warpper for openFrameworks
//
// Copyright (C) 2008 Takashi Maekawa <takachin@generative.info> 
//     All rights reserved.
//     This is free software with ABSOLUTELY NO WARRANTY.
//
// You can redistribute it and/or modify it under the terms of 
// the GNU Lesser General Public License.
//

#pragma once

#include "ofMain.h"
#include "ofxCvConstants.h"
#include "ofxCvGrayscaleImage.h"

class ofxCvOpticalFlowLK: public ofBaseDraws
{
public:
	ofxCvOpticalFlowLK(void);
	~ofxCvOpticalFlowLK(void);
		
	void allocate(int _w, int _h);

	void calc( ofxCvGrayscaleImage & pastImage, ofxCvGrayscaleImage & currentImage, int size);

	void setCalcStep(int _cols, int _rows);
		
	void reset();
	void draw();

	float getTotalMovement();
	void draw(float x,float y) {
		glPushMatrix();
		glTranslatef(x, y, 0);
		draw();
		glPopMatrix();
	}
	
	void forceAtPos(float x, float y, float *dx, float *dy) {
		if(x<captureWidth && y<captureHeight && x>=0 && y>=0) {
			*dx = cvGetReal2D( vel_x, y, x );
			*dy = cvGetReal2D( vel_y, y, x );
		}
	}
	
	void draw(float x,float y,float w, float h) {
		glPushMatrix();
		glScalef(w/captureWidth, h/captureHeight, 1);
		draw(x, y);
		glPopMatrix();
	}
	int captureWidth;
	int captureHeight;
	
	IplImage* vel_x;
	IplImage* vel_y;
	float getWidth() { return captureWidth; }
	float getHeight() { return captureHeight; }


	static const int DEFAULT_CAPTURE_WIDTH = 320;
	static const int DEFAULT_CAPTURE_HEIGHT = 240;


	static const int DEFAULT_CAPTURE_COLS_STEP = 4;
	static const int DEFAULT_CAPTURE_ROWS_STEP = 4;

	int captureColsStep;
	int captureRowsStep;

	void blur(int flowBlur);

};
