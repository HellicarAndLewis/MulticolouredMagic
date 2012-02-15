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
		printf("popen made it\n");
		char name[512];
		string username;
		ofSleepMillis(100);
		if(fgets(name, 512, fp)) {
			printf("fgets\n");
			username = name;
			if(username.find(' ')!=-1) {
				username = username.substr(0, username.find(' '));
				string home = "/Users/"+username;
				printf("%s\n", home.c_str());
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
	printf("Here: %s\n", prefsDir.c_str());
	struct stat stFileInfo;

	// Attempt to get the file attributes
	if(stat(prefsDir.c_str(),&stFileInfo)!=0) {

		if(mkdir(prefsDir.c_str(), 0777)==0) {
			printf("Prefs: %s\n", prefsDir.c_str());
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
