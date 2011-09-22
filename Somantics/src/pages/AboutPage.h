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
	void setup() {
		aboutImage.setup(ofVec2f(10, 10), IMAGE_ROOT + "about.png");
		aboutContent.setup(ofVec2f(0,0), IMAGE_ROOT + "aboutContent.png");
		twitterButton.setup("twitter",ofVec2f(898, 420), IMAGE_ROOT+"twitter.png");
		flickrButton.setup("flickr", ofVec2f(), "");
		flickrButton.x = 26;
		flickrButton.y = 680;
		flickrButton.width = 550;
		flickrButton.height = 30;
		videoButton.setup("video", ofVec2f(780, 227), IMAGE_ROOT + "video.png");
		if(IPAD) {
			bgImage = ImageCache::getImage("img/bgIPad.png");
		} else if(HI_RES) {
			bgImage = ImageCache::getImage("img/bgIPhone4.png");
		} else {
			bgImage = ImageCache::getImage("img/bgIPhone.png");
		}

		logo.setup(ofVec2f(WIDTH/2 - 150, 35), IMAGE_ROOT + "logo.png");
		add(logo);
		add(aboutContent);
		add(videoButton);
		add(twitterButton);
		add(flickrButton);
		videoButton.setListener(this);
		twitterButton.setListener(this);
		flickrButton.setListener(this);
	}
	
	void start() {

	}
  void buttonPressed(string buttonName) {
	  if(buttonName=="video") {
		  launchUrl("http://vimeo.com/user7368023");
	  } else if(buttonName=="flickr") {
		  launchUrl("http://www.flickr.com/photos/64092097@N04");
	  } else if(buttonName=="twitter") {
		  launchUrl("http://twitter.com/somantics");
	  }
  }
	
	void draw() {
		ofSetHexColor(0xFFFFFF);
		bgImage->draw(0, 0,  WIDTH, HEIGHT);
		Container::draw();
		
	}
	ImageObject aboutImage;
	ImageObject logo;
	ImageObject aboutContent;
	
	SimpleButton videoButton;
	SimpleButton twitterButton;
	SimpleButton flickrButton;
	
	ofImage *bgImage;
};