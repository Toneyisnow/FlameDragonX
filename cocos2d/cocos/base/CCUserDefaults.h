/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __SUPPORT_CCUSERDEFAULTS_H__
#define __SUPPORT_CCUSERDEFAULTS_H__

#include "platform/CCPlatformMacros.h"
#include <string>
#include "base/CCData.h"
#include <map>

namespace tinyxml2
{
	class XMLElement;
	class XMLDocument;
}

using namespace std;

/**
* @addtogroup base
* @{
*/
NS_CC_BEGIN


/**
* UserDefault acts as a tiny database. You can save and get base type values by it.
* For example, setBoolForKey("played", true) will add a bool value true into the database.
* Its key is "played". You can get the value of the key by getBoolForKey("played").
*
* It supports the following base types:
* bool, int, float, double, string
*/
class CC_DLL UserDefaults
{
public:
	// get value methods

	/**
	* Get bool value by key, if the key doesn't exist, will return false.
	* You can set the default value, or it is false.
	* @param key The key to get value.
	* @return Bool value by `key`.
	* @js NA
	*/
	bool    getBoolForKey(const char* key);

	/**
	* Get bool value by key, if the key doesn't exist, will return passed default value.
	* @param key The key to get value.
	* @param defaultValue The default value to return if the key doesn't exist.
	* @js NA
	*/
	virtual bool getBoolForKey(const char* key, bool defaultValue);

	/**
	* Get integer value by key, if the key doesn't exist, will return 0.
	* You can set the default value, or it is 0.
	* @param key The key to get value.
	* @return Integer value of the key.
	* @js NA
	*/
	int     getIntegerForKey(const char* key);

	/**
	* Get bool value by key, if the key doesn't exist, will return passed default value.
	* @param key The key to get value.
	* @param defaultValue The default value to return if the key doesn't exist.
	* @return Integer value of the key.
	* @js NA
	*/
	virtual int getIntegerForKey(const char* key, int defaultValue);

	/**
	* Get float value by key, if the key doesn't exist, will return 0.0.
	* @param key The key to get value.
	* @return Float value of the key.
	* @js NA
	*/
	float    getFloatForKey(const char* key);

	/**
	* Get float value by key, if the key doesn't exist, will return passed default value.
	* @param key The key to get value.
	* @param defaultValue The default value to return if the key doesn't exist.
	* @return Float value of the key.
	* @js NA
	*/
	virtual float getFloatForKey(const char* key, float defaultValue);

	/**
	* Get double value by key, if the key doesn't exist, will return 0.0.
	* @param key The key to get value.
	* @return Double value of the key.
	* @js NA
	*/
	double  getDoubleForKey(const char* key);

	/**
	* Get double value by key, if the key doesn't exist, will return passed default value.
	* @param key The key to get value.
	* @param defaultValue The default value to return if the key doesn't exist.
	* @return Double value of the key.
	* @js NA
	*/
	virtual double getDoubleForKey(const char* key, double defaultValue);

	/**
	* Get string value by key, if the key doesn't exist, will return an empty string.
	* @param key The key to get value.
	* @return String value of the key.
	* @js NA
	*/
	std::string getStringForKey(const char* key);

	/**
	* Get string value by key, if the key doesn't exist, will return passed default value.
	* @param key The key to get value.
	* @param defaultValue The default value to return if the key doesn't exist.
	* @return String value of the key.
	* @js NA
	*/
	virtual std::string getStringForKey(const char* key, const std::string & defaultValue);

	/**
	* Get Data value by key, if the key doesn't exist, will return an empty Data.
	* @param key The key to get value.
	* @return Data value of the key.
	* @js NA
	*/
	Data getDataForKey(const char* key);

	/**
	* Get Data value by key, if the key doesn't exist, will return an empty Data.
	* @param key The key to get value.
	* @param defaultValue The default value to return if the key doesn't exist.
	* @return Data value of the key.
	* @js NA
	*/
	virtual Data getDataForKey(const char* key, const Data& defaultValue);

	// set value methods

	/**
	* Set bool value by key.
	* @param key The key to set.
	* @param value A bool value to set to the key.
	* @js NA
	*/
	virtual void setBoolForKey(const char* key, bool value);
	/**
	* Set integer value by key.
	* @param key The key to set.
	* @param value A integer value to set to the key.
	* @js NA
	*/
	virtual void setIntegerForKey(const char* key, int value);
	/**
	* Set float value by key.
	* @param key The key to set.
	* @param value A float value to set to the key.
	* @js NA
	*/
	virtual void setFloatForKey(const char* key, float value);
	/**
	* Set double value by key.
	* @param key The key to set.
	* @param value A double value to set to the key.
	* @js NA
	*/
	virtual void setDoubleForKey(const char* key, double value);
	/**
	* Set string value by key.
	* @param key The key to set.
	* @param value A string value to set to the key.
	* @js NA
	*/
	virtual void setStringForKey(const char* key, const std::string & value);
	/**
	* Set Data value by key.
	* @param key The key to set.
	* @param value A Data value to set to the key.
	* @js NA
	*/
	virtual void setDataForKey(const char* key, const Data& value);
	/**
	* You should invoke this function to save values set by setXXXForKey().
	* @js NA
	*/
	virtual void flush();

	static UserDefaults* getInstance(std::string instanceName);

	/**
	* @js NA
	*/
	static void destroyInstance();

	/**
	* You can inherit from platform dependent implementation of UserDefault, such as UserDefaultAndroid,
	* and use this function to set delegate, then UserDefault will invoke delegate's implementation.
	* For example, your store native data base or other format store.
	*
	* If you don't want to system default implementation after setting delegate, you can just pass nullptr
	* to this function.
	*
	* @warm It will delete previous delegate
	*/
	static void setDelegate(UserDefaults *delegate);

	std::string getXMLFilePath();
	bool isXMLFileExist();

	std::string _xmlFileFullPath;
	std::string _instanceName;

protected:
	UserDefaults(std::string instanceName);
	~UserDefaults();

private:

	bool createXMLFile();
	
	static std::map<std::string, UserDefaults*> _currentInstances;

	tinyxml2::XMLElement* getXMLNodeForKey(const char* pKey, tinyxml2::XMLElement** rootNode, tinyxml2::XMLDocument **doc);
	void setValueForKey(const char* pKey, const char* pValue);

};


NS_CC_END
// end of base group
/** @} */

#endif // __SUPPORT_CCUSERDEFAULT_H__
