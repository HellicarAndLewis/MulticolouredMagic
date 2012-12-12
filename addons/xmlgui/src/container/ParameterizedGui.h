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
 *  ParameterizedGui.h, created by Marek Bereza on 13/11/2012.
 */

#include "SimpleGui.h"
#include "Parameterized.h"

namespace xmlgui {
	class ParameterizedGui: public xmlgui::SimpleGui {
	public:
		ParameterizedGui(): xmlgui::SimpleGui() {
			choice = -1;
			lastChoice = -2;
			gui = new SimpleGui();
			list = addList("list", choice, vector<string>());
			addChild(gui);
		}
		
		
		// this is a workaround to let you listen to the gui
		// even though the superclass is a Listener. See
		// SimpleGui::ctrlChanged() and ::controlChanged()
		void ctrlChanged(xmlgui::Event *e) {
			
			if(choice!=lastChoice && choice>=0) {
				gui->clear();
				parameterizeds[choice].second->buildGui(gui);
				gui->loadSettings("settings/" + parameterizeds[choice].first + ".xml");
			}
			
			lastChoice = choice;
		}

		void addParameterized(string name, Parameterized *parameterized) {
			parameterizeds.push_back(make_pair(name, parameterized));

			parameterized->name = name;
			
			// configure it to autosave
			parameterized->buildGui(gui);
			gui->loadSettings("settings/" + name + ".xml");

			gui->clear();
			
			list->addItem(name);
		}
		
		void save(Parameterized *me) {
			xmlgui::SimpleGui g;
			me->buildGui(&g);
			string name = me->name;
			g.saveSettings("settings/"+name+".xml");
		}
		
	private:
		int choice;
		int lastChoice;
		List *list;
		vector<pair<string, Parameterized *> > parameterizeds;
		SimpleGui *gui;
	};
}