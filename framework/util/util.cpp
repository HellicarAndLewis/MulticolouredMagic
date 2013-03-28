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

#include "util.h"
#include "ofMain.h"
#include <sys/stat.h>

using namespace std;



string padZeros(int t) {
	if(t<10) return ofToString(t);
	else return "0"+ofToString(t);
}
string dateTimeString() {
	return padZeros(ofGetDay())
	+ "." + padZeros(ofGetMonth()) + "." + padZeros(ofGetYear()) + " "
	+ padZeros(ofGetHours()) +"-"+padZeros(ofGetMinutes()) +"-"+
	padZeros(ofGetSeconds());
}
void setDataPathRootToAppContents(string appName) {
// do nothing if we're in windows.
#ifndef _WIN32
	char path[512];
	getcwd(path, 512);
	string dataRoot = path;
	if(dataRoot.find(".app/Contents")==-1) {
		dataRoot += "/" + appName + ".app/Contents/MacOS";
	}
	dataRoot += "/../data/";
	ofSetDataPathRoot(dataRoot);
#endif
}

string getHomeDirectory() {
	FILE *fp = popen("who am I", "r");
	if(fp!=NULL) {
//		printf("popen made it\n");
		char name[512];
		string username;
		ofSleepMillis(100);
		if(fgets(name, 512, fp)) {
//			printf("fgets\n");
			username = name;
			if(username.find(' ')!=-1) {
				username = username.substr(0, username.find(' '));
				string home = "/Users/"+username;
//				printf("%s\n", home.c_str());
				return home;
			}

		}
		pclose(fp);
	} else {
		printf("Couldn't find user's name, going with default\n");
	}
	return "";
}

string getDesktopPath() {
	return getHomeDirectory() + "/Desktop";
}


string getPreferencesDirectory(string appName) {
#ifndef _WIN32

	//getHomeDirectory();
	//if(1) return "/Users/marek/Library/Preferences/Reactickles Magic";
	string prefsDir = getHomeDirectory() + "/Library/Preferences/"+appName;
//	printf("Here: %s\n", prefsDir.c_str());
	struct stat stFileInfo;

	// Attempt to get the file attributes
	if(stat(prefsDir.c_str(),&stFileInfo)!=0) {

		if(mkdir(prefsDir.c_str(), 0777)==0) {
//			printf("Prefs: %s\n", prefsDir.c_str());
			return prefsDir;
		} else {
			printf("Failed to create preferences directory: %s\n", prefsDir.c_str());
			return "";
		}
	} else {
		return prefsDir;
	}
#else
    return "";
#endif
}
