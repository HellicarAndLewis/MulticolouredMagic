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