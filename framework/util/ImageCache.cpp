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
#ifdef IMAGECACHE_STRICT
		return NULL;
#else
		return NULL;
#endif
	}

	if(!guiResFileExists(ofToDataPath(path, true))) {
		printf("File doesn't exist %s\n", ofToDataPath(path).c_str());
#ifdef IMAGECACHE_STRICT
		return NULL;
#else
		return new ofImage();
#endif
	}

	// cache the image if it's not already loaded
	if(imageCacheImages.find(path)==imageCacheImages.end()) {
		ofImage *img = new ofImage();
		//printf("Loading %s\n", ofToDataPath(path).c_str());
		img->loadImage(path);

		imageCacheImages[path] = img;
		//printf("Loaded file from %s\n", string(basePath+path).c_str());
	}

	return imageCacheImages[path];
}
