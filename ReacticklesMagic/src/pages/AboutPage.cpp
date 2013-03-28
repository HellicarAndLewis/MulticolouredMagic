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
 * AboutPage.mm
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "AboutPage.h"
#ifdef TARGET_OF_IPHONE
#include "ofxiPhoneExtras.h"
#endif
void AboutPage::start() {
	if(IPAD) {
		bgImage.setup(ofVec2f(), "img/bg.png");
	} else if(HI_RES) {
		bgImage.setup(ofVec2f(), "img/bgIPhone4.png");
	} else {
		bgImage.setup(ofVec2f(), "img/bgIPhone.png");
	}
	
	
	logo.setup(ofVec2f(), IMAGE_ROOT + "logo.png");
	logo.x = WIDTH/2 - logo.width/2;
	logo.y = 35;
	
	aboutContent.setup(ofVec2f(20, 50), IMAGE_ROOT + "aboutContent.png");
	videoButton.setup("video", ofVec2f(787, 241), IMAGE_ROOT + "video.png");
	videoButton.y = 201;
	videoButton.setListener(this);
	
	
	twitterButton.setup("twitter",ofVec2f(32+45+59, 32+473+16+65), IMAGE_ROOT+"twitter.png");
	vimeoButton.setup("vimeo",ofVec2f(119+32+89, 473+32+16+65), IMAGE_ROOT+"vimeo.png");
	flickrButton.setup("flickr",ofVec2f(195+32+117, 32+473+16+65), IMAGE_ROOT+"flickr.png");
	reacticklesLink.setup("reactickles", ofVec2f(), "");
	reacticklesLink.x = 99;
	reacticklesLink.y = 448+72;
	reacticklesLink.width = 112;
	reacticklesLink.height = 20;
	
	
	add(bgImage);
	add(logo);
	add(videoButton);		videoButton.setListener(this); 
	add(aboutContent);		
	add(vimeoButton);		vimeoButton.setListener(this);
	add(twitterButton);		twitterButton.setListener(this);
	add(flickrButton);		flickrButton.setListener(this);
	add(reacticklesLink);	reacticklesLink.setListener(this);
	
}
#ifdef TARGET_OF_IPHONE
void ofxiPhoneLaunchBrowser(string url) {
	
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:ofxStringToNSString(url)]];
}
#endif
void AboutPage::buttonPressed(string name) {
	if(name=="video") {
		launchUrl("http://vimeo.com/33679871");
	} else if(name=="vimeo") {
		launchUrl("http://vimeo.com/user1978699");
	} else if(name=="reactickles") {
		launchUrl("http://reactickles.org/");
	} else if(name=="flickr") {
		launchUrl("http://www.flickr.com/photos/reactickles/");
	} else if(name=="twitter") {
		launchUrl("http://twitter.com/reactickle");
	}
	

}


void AboutPage::draw() {
	Reactickle::draw();
//	ofNoFill();
//	ofSetHexColor(0xFFFFFF);
//	ofRect(reacticklesLink);
//	ofFill();
}