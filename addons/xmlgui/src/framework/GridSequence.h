/*
 *  GridSequence.h
 *  Gui
 *
 *  Created by Marek Bereza on 05/05/2010.
 *
 */
#include <list>

using namespace std;
class Note {
public:
	unsigned char note;
	unsigned char step;
	unsigned char velocity;
	Note(unsigned char _note, unsigned char _step, unsigned char _velocity) {
		note = _note;
		step = _step;
		velocity = _velocity;
	}
};

class GridSequence {
private:
	list<Note> sequence;
	list<Note>::iterator iter;
public:

	GridSequence() {
	
	}
	void rewind() {
		iter = sequence.begin();
	}
	Note *nextNote() {
		if(iter==sequence.end()) return NULL;
		else return &(*(iter++));
	}
	
	/**
	 * Returns true if a note was added, false if a note was taken away.
	 */
	bool toggle(unsigned char note, unsigned char step, unsigned char velocity) {
		list<Note>::iterator it;
		for ( it=sequence.begin() ; it != sequence.end(); it++ ) {
			if((*it).note==note && (*it).step==step) {
				
				// remove note if it exists
				sequence.erase(it);
				return false;
			}
			// insert note if the this note is 
			if((*it).step>step) {
				sequence.insert(it, Note(note, step, velocity));
				return true;
			}
		}
		// add note at the end if there's no notes to insert it before
		sequence.push_back(Note(note, step, velocity));
		return true;
	}
	
	void set(unsigned char note, unsigned char step, unsigned char velocity, bool adding = true) {
		list<Note>::iterator it;
		for ( it=sequence.begin() ; it != sequence.end(); it++ ) {
			if((*it).note==note && (*it).step==step) {
				
				// remove note if it exists
				if(!adding) sequence.erase(it);
				return;
			}
			// insert note if the this note is 
			if((*it).step>step) {
				if(adding) sequence.insert(it, Note(note, step, velocity));
				return;
			}
		}
		// add note at the end if there's no notes to insert it before
		if(adding) sequence.push_back(Note(note, step, velocity));
	}
	
	
	string valueToString() { 
		string s = "";
		list<Note>::iterator it;
		for ( it=sequence.begin() ; it != sequence.end(); it++ ) {
			s += ofToString((int)(*it).note);
			s += ",";
			s += ofToString((int)(*it).step);
			s += ",";
			s += ofToString((int)(*it).velocity) + ":";
		}
		// remove last :
		if(s.size()>0) {
			s = s.erase(s.size()-1);
		}
		
		return s;
	}
	void valueFromString(string inp) { 
		vector<string> notes = ofSplitString(inp, ":");
		for(int i = 0; i < notes.size(); i++) {
			vector<string> vals = ofSplitString(notes[i], ",");
			if(vals.size()==3) {
				set(atoi(vals[0].c_str()), atoi(vals[1].c_str()), atoi(vals[2].c_str()), true);
			} else {
				printf("Problem parsing grid, has %d values instead of 3\n", vals.size());
			}
		}
	}
	
};