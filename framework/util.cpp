#include "util.h"
#include "ofMain.h"
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


string getDesktopPath() {
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
				string desktop = "/Users/"+username+"/Desktop";
				return desktop;
			}
			
		}
		pclose(fp);
	} else {
		printf("Couldn't find user's name, going with default\n");
	}
	return "";
}
