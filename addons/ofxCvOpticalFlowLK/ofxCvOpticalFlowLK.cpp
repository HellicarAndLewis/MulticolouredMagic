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

#include "ofxCvOpticalFlowLK.h"

ofxCvOpticalFlowLK::ofxCvOpticalFlowLK(void)
{
	captureWidth = DEFAULT_CAPTURE_WIDTH;
	captureHeight = DEFAULT_CAPTURE_HEIGHT;

	captureColsStep = DEFAULT_CAPTURE_COLS_STEP;
	captureRowsStep = DEFAULT_CAPTURE_ROWS_STEP;
}

ofxCvOpticalFlowLK::~ofxCvOpticalFlowLK(void)
{
	cvReleaseImage(&vel_x);
	cvReleaseImage(&vel_y);
}

float ofxCvOpticalFlowLK::getTotalMovement() {
	int x, y;
	float dx = 0, dy = 0;
	for ( y = 0; y < captureHeight; y+=captureRowsStep ){
		for ( x = 0; x < captureWidth; x+=captureColsStep ){
			
			dx += ABS(cvGetReal2D( vel_x, y, x ));
			dy += ABS(cvGetReal2D( vel_y, y, x ));
		}
	}
	return dx+dy;
}


void ofxCvOpticalFlowLK::allocate(int _w, int _h){
	captureWidth = _w;
	captureHeight = _h;

	vel_x = cvCreateImage( cvSize( captureWidth ,captureHeight ), IPL_DEPTH_32F, 1  );
	vel_y = cvCreateImage( cvSize( captureWidth ,captureHeight ), IPL_DEPTH_32F, 1  );
	
    cvSetZero(vel_x);
    cvSetZero(vel_y);
}

void ofxCvOpticalFlowLK::setCalcStep(int _cols, int _rows){
	captureColsStep = _cols;
	captureRowsStep = _rows;
}

void ofxCvOpticalFlowLK::calc( ofxCvGrayscaleImage & pastImage, ofxCvGrayscaleImage & currentImage, int size) {
	cvCalcOpticalFlowLK( pastImage.getCvImage(), currentImage.getCvImage(),	cvSize( size, size), vel_x, vel_y );
}

void ofxCvOpticalFlowLK::draw(void){

	ofSetHexColor(0xFF0000);
	ofNoFill();
	float speed;

	int x, y, dx, dy;
	for ( y = 0; y < captureHeight; y+=captureRowsStep ){
		for ( x = 0; x < captureWidth; x+=captureColsStep ){

			dx = (int)cvGetReal2D( vel_x, y, x );
			dy = (int)cvGetReal2D( vel_y, y, x );
			//speed = dx * dx + dy * dy;
			ofLine(x, y, x+dx, y+dy);

		}
	}
}
void ofxCvOpticalFlowLK::blur(int flowBlur) {
	// smooth it
	cvSmooth(vel_x, vel_x, CV_BLUR , flowBlur*2+1);
	cvSmooth(vel_y, vel_y, CV_BLUR , flowBlur*2+1);
}

