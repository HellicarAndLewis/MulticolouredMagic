/**
 * ofxiPhoneWebView.mm
 * ReacticklesMagic
 *
 * Created by Marek Bereza on 27/04/2011.
 *
 */

#include "ofxiPhoneWebView.h"
#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"

ofxiPhoneWebView::ofxiPhoneWebView() {
	webView = NULL;
}
void ofxiPhoneWebView::show() {
	if(!webView) {
		webView	= [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, ofGetWidth(), ofGetHeight())];
		((UIWebView*)webView).delegate	= NULL;
	}
	[ofxiPhoneGetUIWindow() addSubview:(UIWebView*)webView];
}