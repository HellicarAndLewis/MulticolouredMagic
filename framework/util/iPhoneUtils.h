/**     ___           ___           ___                         ___           ___     
 *     /__/\         /  /\         /  /\         _____         /  /\         /__/|    
 *    |  |::\       /  /::\       /  /::|       /  /::\       /  /::\       |  |:|    
 *    |  |:|:\     /  /:/\:\     /  /:/:|      /  /:/\:\     /  /:/\:\      |  |:|    
 *  __|__|:|\:\   /  /:/~/::\   /  /:/|:|__   /  /:/~/::\   /  /:/  \:\   __|__|:|    
 * /__/::::| \:\ /__/:/ /:/\:\ /__/:/ |:| /\ /__/:/ /:/\:| /__/:/ \__\:\ /__/::::\____
 * \  \:\~~\__\/ \  \:\/:/__\/ \__\/  |:|/:/ \  \:\/:/~/:/ \  \:\ /  /:/    ~\~~\::::/
 *  \  \:\        \  \::/          |  |:/:/   \  \::/ /:/   \  \:\  /:/      |~~|:|~~ 
 *   \  \:\        \  \:\          |  |::/     \  \:\/:/     \  \:\/:/       |  |:|   
 *    \  \:\        \  \:\         |  |:/       \  \::/       \  \::/        |  |:|   
 *     \__\/         \__\/         |__|/         \__\/         \__\/         |__|/   
 *
 *  Description: 
 *				 
 *  iPhoneUtils.h, created by Marek Bereza on 16/09/2011.
 */

#pragma once

#pragma once
#include <string>
using namespace std;
// if you want mail features, you need Reachabilty.h/m and the mail framework included.
// reachability.h comes with some example on the apple website
//#define HAS_MAIL_FEATURES
#ifdef HAS_MAIL_FEATURES
/**
 * Returns 1 if this device can send emails, 0 if it can't
 */
bool canSendEmail();

class MailListener {
public:
	virtual void mailSent() = 0;
	virtual void mailCancelled() {}
	virtual void mailSaved() {}
	virtual void mailFailed() = 0;
};

void iPhoneSendEmail(char *to, char *subject, char *body, char *attachmentPath, MailListener *listener = NULL);
bool hasInternetConnection();

#endif
string getTmpPath();
string getBundlePath();






int getFreeMemory();


string iPhoneGetDocsDir();

string getUDID();

/** Warns the user with a standard alert dialog */
void warnWithAlert(string title, string message);


void launchUrl(string url);



bool downloadFile(string url, string destination);