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
		twitterButton.setup("twitter",ofVec2f(32+45, 32+473+16), IMAGE_ROOT+"twitter.png");
		vimeoButton.setup("vimeo",ofVec2f(119+32, 473+32+16), IMAGE_ROOT+"vimeo.png");
		flickrButton.setup("flickr",ofVec2f(195+32, 32+473+16), IMAGE_ROOT+"flickr.png");
		somanticsLink.setup("somantics", ofVec2f(), "");
		somanticsLink.x = 121;
		somanticsLink.y = 448;
		somanticsLink.width = 142;
		somanticsLink.height = 20;
		
		videoButton.setup("video", ofVec2f(531+224, 111+16+127), IMAGE_ROOT + "video.png");
		if(IPAD) {
			bgImage = ImageCache::getImage("img/bgIPad.png");
		} else if(HI_RES) {
			bgImage = ImageCache::getImage("img/bgIPhone4.png");
		} else {
			bgImage = ImageCache::getImage("img/bgIPhone.png");
		}

		logo.setup(ofVec2f(WIDTH/2 - 150, 35), IMAGE_ROOT + "logo.png");
		add(logo);
		add(vimeoButton);
		add(aboutContent);
		add(videoButton);
		add(twitterButton);
		add(flickrButton);
		add(somanticsLink);
		videoButton.setListener(this);
		twitterButton.setListener(this);
		flickrButton.setListener(this);
		vimeoButton.setListener(this);
		somanticsLink.setListener(this);
	}
	
	void start() {

	}
  void buttonPressed(string buttonName) {
	  if(buttonName=="video") {
		  launchUrl("http://vimeo.com/user7368023");
	  } else if(buttonName=="vimeo") {
		  launchUrl("http://vimeo.com/user7368023");
	  } else if(buttonName=="somantics") {
		  launchUrl("http://www.somantics.org/");
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
	
	SimpleButton somanticsLink;
	SimpleButton videoButton;
	SimpleButton twitterButton;
	SimpleButton flickrButton;
	SimpleButton vimeoButton;
	ofImage *bgImage;
};