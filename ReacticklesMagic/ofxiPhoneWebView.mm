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
		webView	= [[UIWebView alloc] initWithFrame:CGRectMake(-128, 128, ofGetWidth(), ofGetHeight())];
		((UIWebView*)webView).delegate	= NULL;
	}
	
	((UIWebView*)webView).transform = CGAffineTransformMakeRotation (PI/2);
	[ofxiPhoneGetUIWindow() addSubview:(UIWebView*)webView];
	[webView loadRequest:[NSURLRequest requestWithURL:[NSURL fileURLWithPath:[[NSBundle mainBundle] pathForResource:@"about" ofType:@"html"]isDirectory:NO]]];
}