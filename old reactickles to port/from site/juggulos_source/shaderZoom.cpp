/*
 *  shaderZoom.cpp
 *  openFrameworks
 *
 *  Created by theo on 17/10/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "shaderZoom.h"

//--------------------------------------------------------------
void shaderZoom::setup(int fboW, int fboH){	
	
	//ofBackground(255,255,255);	
	ofSetVerticalSync(true);
	
	fbo.allocate(fboW, fboH, GL_RGBA, true);
	
	shader.loadShader("zoom");

	pos.set(100, 100);
	zoomRadius = 40.0;
	zoomMinVal = 0.1;
	zoomMaxVal = 1.0;
}

//--------------------------------------------------------------
void shaderZoom::beginRender(){
	fbo.swapIn();
	
}

//--------------------------------------------------------------
void shaderZoom::endRender(){
	fbo.swapOut();
}

//--------------------------------------------------------------
void shaderZoom::setZoomParams(float xPos, float yPos, float radius, float minVal, float maxVal){
	pos.x			= xPos;
	pos.y			= yPos;
	zoomRadius		= radius;
	zoomMinVal		= minVal;
	zoomMaxVal		= maxVal;
}

//--------------------------------------------------------------
void shaderZoom::draw(float x, float y, float w, float h, bool useShader){
	

	if( useShader ){
							
		//first the horizontal shader 
		shader.setShaderActive(true);
		shader.setUniformVariable2f("circlePos", pos.x, fbo.getHeight() - pos.y);
		shader.setUniformVariable1f("circleRadius", zoomRadius);
		shader.setUniformVariable1f("minZoom", zoomMinVal);
		shader.setUniformVariable1f("maxZoom", zoomMaxVal);
		
		//ofSetColor(255, 255, 255);
		fbo.draw(0, 0);
		
		shader.setShaderActive(false);
	
	}else{
		fbo.draw(0, 0);
	}
	
}



