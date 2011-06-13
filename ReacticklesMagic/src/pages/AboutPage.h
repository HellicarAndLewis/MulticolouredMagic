/**
 * AboutPage.h
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "Reactickle.h"
#include "ImageCache.h"
#include "constants.h"

class AboutPage: public Reactickle {
public:
	void start() {
		if(IPAD) {
			bgImage = ImageCache::getImage("img/bgIPad.png");
		} else if(HI_RES) {
			bgImage = ImageCache::getImage("img/bgIPhone4.png");
		} else {
			bgImage = ImageCache::getImage("img/bgIPhone.png");
		}
		logo = ImageCache::getImage(IMAGE_ROOT + "logo.png");
		logo->setAnchorPercent(0.5, 1);
	}
	
	void draw() {
		bgImage->draw(0, 0, WIDTH, HEIGHT);
		logo->draw(WIDTH/2, 35+logo->getHeight());
	}
	
	ofImage *bgImage;
	ofImage *logo;
};