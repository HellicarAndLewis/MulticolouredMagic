#include <string>
std::string dateTimeString();
std::string getDesktopPath();
std::string getHomeDirectory();
std::string getPreferencesDirectory(std::string appName);

/** 
 * For packaging mac apps - you need to add the line
 * cp -r bin/data "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/"
 * to your "run script build phase"
 */
void setDataPathRootToAppContents(std::string appName);