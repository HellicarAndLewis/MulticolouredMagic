/**
 * ImageCache.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

#include "ImageCache.h"
#include <sys/stat.h>

map<string,ofImage*> imageCacheImages;



bool guiResFileExists(string filename) { 
	struct stat stFileInfo; 
	
	// Attempt to get the file attributes 
	return stat(filename.c_str(),&stFileInfo)==0; 
}



ofImage *ImageCache::getImage(string path) {
	if(path=="") {
		printf("ImageCache::getImage() path empty!!\n");
		return NULL;
	}
	
	if(!guiResFileExists(ofToDataPath(path, true))) {
		printf("File doesn't exist %s\n", (path).c_str());
		return NULL;
	}
		
	// cache the image if it's not already loaded
	if(imageCacheImages.find(path)==imageCacheImages.end()) {
		ofImage *img = new ofImage();
		img->loadImage(path);
		imageCacheImages[path] = img;
		//printf("Loaded file from %s\n", string(basePath+path).c_str());
	}
		
	return imageCacheImages[path];
}