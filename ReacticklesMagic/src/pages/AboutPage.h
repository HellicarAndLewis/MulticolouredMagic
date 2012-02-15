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
#include "ImageObject.h"
#include "SimpleButton.h"
// ugh
#ifdef TARGET_OF_IPHONE
#include "iPhoneUtils.h"
#else
#define launchUrl ofLaunchBrowser
#endif

class AboutPage: public Reactickle, public SimpleButtonListener {
public:
	void start() ;
	void draw();
	void buttonPressed(string name) ;
	
	ImageObject bgImage;
	ImageObject aboutImage;
	ImageObject logo;
	ImageObject aboutContent;
	

	SimpleButton reacticklesLink;
	SimpleButton videoButton;
	SimpleButton twitterButton;
	SimpleButton flickrButton;
	SimpleButton vimeoButton;

	
};
