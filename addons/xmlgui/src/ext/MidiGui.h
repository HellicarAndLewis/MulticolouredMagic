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
 *  MidiGui.h, created by Marek Bereza on 15/11/2012.
 */


#include "ofxMidi.h"
#include "ofxXmlSettings.h"
namespace xmlgui {
	class MidiGui: public ofxMidiListener {
	public:
		~MidiGui() {
			midiIn.closePort();
		}
		void setup() {

			midiLearn = false;
			learnControl = NULL;

			midiIn.openPort();
			midiIn.addListener(this);
		}
		
		void saveSnapshot(ofxXmlSettings &snapshot) {
			snapshot.addTag("snapshot");
			
			// maybe have an independent midi mapping here
			snapshot.pushTag("snapshot");

			int pos = 0;
			
			for(int i = 0; i < gui->getNumChildren(); i++) {
				xmlgui::Control *c = gui->getChild(i);
				if(c->type!="title") {
					printf("%s = %s\n",c->id.c_str(), c->valueToString().c_str());
					snapshot.addTag("control");
					snapshot.addAttribute("control", "id", c->id, pos);
					snapshot.addAttribute("control", "value", c->valueToString(), pos);
					pos++;
				}
			}
		}
		
		void loadSnapshot(ofxXmlSettings &snapshot) {
			snapshot.pushTag("snapshot");
			int numControls = snapshot.getNumTags("control");
			for(int i = 0; i < numControls; i++) {
				string id = snapshot.getAttribute("control", "id", "", i);
				string value = snapshot.getAttribute("control", "value", "", i);
				xmlgui::Control *c = gui->getControlById(id);
				if(c!=NULL) {
					
					// if we're a continuous control, we want to pass
					// to the setControlValue() function so we can slide the slider
					// rather than snap to the setting.
					if(c->type=="slider" || c->type=="panner") {
						setControlValue(c, ofToFloat(value));
					} else {
						c->valueFromString(value);
						xmlgui::Event e(c, xmlgui::Event::TOUCH_UP);
						c->parent->notifyChange(&e);
					}
				}
			}
		}
		
		
		void update() {
		}
		
		void setGui(xmlgui::Container *gui) {
			this->gui = gui;
			load(string("mapping-") + gui->name + ".xml");
		}



		void setMidiLearn(bool on) {
			midiLearn = on;
		}

		void setLearnControl(xmlgui::Control *ctrl) {
			if(ctrl==NULL) {
				learnControl = NULL;
				return;
			}

			// otherwise...
			learnControl = ctrl;
		}

		void newMidiMessage(ofxMidiEventArgs& eventArgs) {
			if(eventArgs.status==MIDI_CONTROL_CHANGE) {

				int ccNum = eventArgs.byteOne;

				if(midiLearn) { // learn the control
					if(learnControl!=NULL) {

						midiMapping[ccNum] = learnControl->id;
						printf("Assigned %s to midi controller %d\n", learnControl->id.c_str(), eventArgs.byteOne);
						save(string("mapping-") + gui->name + ".xml");
					}
				}
				// affect the control
				// look it up first
				if(midiMapping.find(ccNum)!=midiMapping.end()) {
					xmlgui::Control *c = gui->getControlById(midiMapping[ccNum]);

					if(c->type=="slider") {
						Slider *s = (Slider*)c;
						setControlValue(s, ofMap(eventArgs.byteTwo, 0, 127, s->min, s->max));
//						xmlgui::Event e(s, xmlgui::Event::TOUCH_UP);
//						s->parent->notifyChange(&e);
					}
					else if(c->type=="panner") {
						Panner *s = (Panner*)c;
						
						setControlValue(s, ofMap(eventArgs.byteTwo, 0, 127, s->min, s->max));
										

					}
				}
			}

//			printf("%d %d %d\n", eventArgs.status, eventArgs.byteOne, eventArgs.byteTwo);
		}


		map<int, string> midiMapping;

		
		void setControlValue(xmlgui::Control *s, float value) {
			s->setValue(value);
			xmlgui::Event e(s, xmlgui::Event::TOUCH_UP);
			s->parent->notifyChange(&e);
		}
		
										
		void save(string where) {
			ofxXmlSettings xml;
			xml.addTag("mapping");
			xml.pushTag("mapping");
			map<int,string>::iterator  it;
			int which = 0;
			for(it = midiMapping.begin(); it !=midiMapping.end(); it++) {
				xml.addTag("map");
				xml.addAttribute("map", "cc", (*it).first, which);
				xml.addAttribute("map", "guiId", (*it).second, which);
				which++;
			}

			xml.saveFile(where);
			printf("Saved xml\n");
		}

		void load(string where) {
			midiMapping.clear();
			ofxXmlSettings xml;
			xml.loadFile(where);
			xml.pushTag("mapping");
			int numMappings = xml.getNumTags("map");
			for(int i = 0; i < numMappings; i++) {

				int cc = xml.getAttribute("map", "cc", 0, i);
				string guiId = xml.getAttribute("map", "guiId", "", i);
				midiMapping[cc] = guiId;
			}


		}
		ofxMidiIn *getMidiIn() {
			return &midiIn;
		}
	private:
		xmlgui::Container *gui;
		xmlgui::Control *learnControl;
		ofxMidiIn midiIn;
		bool midiLearn;
	};
}
