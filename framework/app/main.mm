
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
#include "ofMain.h"
#include "testApp.h"
#include "ReactickleApp.h"



int WIDTH = 480;
int HEIGHT = 320;
float WIDTH_SCALE = 1;
float HEIGHT_SCALE = 1;

bool RETINA = false;
bool IPAD = false;
bool HI_RES = false;
bool FAKE_GAME_MODE = false;
bool HAS_CAMERA = true;

string IMAGE_ROOT;
string APP_NAME;
//#define DEBUG_MODE


int main(){
	APP_NAME = "openFrameworks"; // rename me!
#ifdef TARGET_OF_IPHONE
	if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)]) {
		if ([[UIScreen mainScreen] scale] > 1) {
			RETINA = true;
		}
	}
	
	WIDTH = [[UIScreen mainScreen] bounds].size.width;
	HEIGHT = [[UIScreen mainScreen] bounds].size.height;
	
	if(WIDTH<HEIGHT) {
		int temp = WIDTH;
		WIDTH = HEIGHT;
		HEIGHT = temp;
	}
	
	if(!RETINA) {
		if([[UIDevice currentDevice] respondsToSelector:@selector(userInterfaceIdiom)]) {
			IPAD = [[UIDevice currentDevice]userInterfaceIdiom]==UIUserInterfaceIdiomPad;
		}
	}
	//printf("WIDTH: %d    HEIGHT: %d\n", WIDTH, HEIGHT);
	if(RETINA) {
		WIDTH *= 2;
		HEIGHT *= 2;
	}
	
	if(IPAD||RETINA) {
		IMAGE_ROOT = "images4/";
		HI_RES = true;
	} else {
		HI_RES = false;
		IMAGE_ROOT = "images/";
	}
	
	
#else 
	//WIDTH_SCALE = 2;
	//HEIGHT_SCALE = 2;
	WIDTH = 1024;
	HEIGHT = 768;
	HI_RES = true;
	RETINA = false;
	IPAD = true;
	IMAGE_ROOT = "images4/";
	//FAKE_GAME_MODE = true;
	printf("SETTED HERE!!!!!\n\n\n\n");
#endif
	
	WIDTH_SCALE = (float)WIDTH/480.f;
	HEIGHT_SCALE = (float)HEIGHT/320.f;
	
	ofSetupOpenGL(WIDTH, HEIGHT, OF_FULLSCREEN);			// <-------- setup the GL context
	
	

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());
	
}
