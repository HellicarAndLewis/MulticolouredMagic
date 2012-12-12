/**
 * Resources.cpp
 * emptyExample
 *
 * Created by Marek Bereza on 29/06/2011.
 *
 */

#include "Resources.h"
#include <sys/stat.h>

//#define DEFAULT_FONT "OCRAStd.ttf"
//#define DEFAULT_FONT_SIZE 12
#define DEFAULT_FONT "res/automat.ttf"
#define DEFAULT_FONT_SIZE 6


ofTrueTypeFont *xmlgui::Resources::font = NULL;
bool xmlgui::Resources::customFontNotAvailable = false;
map<string,ofImage*> xmlgui::Resources::images;

ofImage *xmlgui::Resources::getImage(string path) {


	if(path=="") return NULL;

	struct stat stFileInfo; 
	
	if(stat(ofToDataPath(path, true).c_str(),&stFileInfo)!=0) {
		printf("Can't find the file %s\n", (path).c_str());
		return NULL;
	}
	
	// cache the image if it's not already loaded
	if(images.find(path)==images.end()) {
		ofImage *img = new ofImage();
		img->loadImage(path);
		images[path] = img;
		//printf("Loaded file from %s\n", string(basePath+path).c_str());
	}

	return images[path];
}

void xmlgui::Resources::drawString(string str, int x, int y) {
	if(font==NULL && !customFontNotAvailable) {
		// try to load font
		ofFile f(DEFAULT_FONT);
		printf("Loading font\n");
		if(f.exists()) {
			printf("Cant find font\n");
			font = new ofTrueTypeFont();
			font->loadFont(DEFAULT_FONT, DEFAULT_FONT_SIZE);
		} else {
			printf("Couldn't find font at %s\n", ofToDataPath(DEFAULT_FONT, true).c_str());
			customFontNotAvailable = true;
		}
	}
	if(customFontNotAvailable) {
		ofDrawBitmapString(str, x, y);
	} else {
		font->drawString(str, x, y);
	}

}