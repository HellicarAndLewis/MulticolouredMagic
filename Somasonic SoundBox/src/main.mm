#include "ofMain.h"
#include "testApp.h"
#include "constants.h"



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
	APP_NAME = "Somasonic Harp"; // rename me!
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
#ifdef TARGET_OF_IPHONE
	ofSetupOpenGL(WIDTH, HEIGHT, OF_FULLSCREEN);			// <-------- setup the GL context
#else
	ofSetupOpenGL(WIDTH, HEIGHT, OF_WINDOW);			// <-------- setup the GL context
#endif
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	printf("Test app creating\n");
	ofRunApp( new testApp());
	printf("Test app created\n");	
}
