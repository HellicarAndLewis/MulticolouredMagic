/**
 * Settings.h
 * Somantics
 *
 * Created by Marek Bereza on 06/06/2011.
 *
 */

class Settings {
private:
	Settings();
public:
	static Settings *getInstance() {
		static Settings *instance = NULL;
		if(instance==NULL) {
			instance = new Settings();
		}
		return instance;
	}

	void reset();
	void save();
	void load();

	map<string, float> settings;
private:
	void setDefaultValues();
};