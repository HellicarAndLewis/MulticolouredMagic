/*
 *  shaderBlur.h
 *  openFrameworks
 *
 *  Created by theo on 17/10/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxShader.h" 
#include "ofxFBOTexture.h"

class shaderZoom{

	public:
		void setup(int fboW, int fboH);
		
		void beginRender();
		void endRender();
		
		void setZoomParams(float xPos, float yPos, float radius, float minVal, float maxVal);
		void draw(float x, float y, float w, float h, bool useShader);
				
		ofxShader shader;

		ofxFBOTexture fbo;
		
		ofPoint pos;
		float zoomRadius;
		float zoomMinVal;
		float zoomMaxVal;

};