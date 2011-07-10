/**
 * ImageCache.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 26/04/2011.
 *
 */

#include "ofMain.h"

// if this is defined then ImageCache returns NULL when it can't find a picture
// - may make things crash inexplicably on iPad - so turn it off when you're debugging
//#define IMAGECACHE_STRICT

namespace ImageCache {
	ofImage *getImage(string path);
};