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

/**
 * ImageCache.cpp
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

#include "ImageCache.h"
#include <sys/stat.h>
#include <map>
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
