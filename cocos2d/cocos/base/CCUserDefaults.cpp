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
#include "base/CCUserDefaults.h"
#include "platform/CCCommon.h"
#include "platform/CCFileUtils.h"
#include "tinyxml2.h"
#include "base/base64.h"
#include "base/ccUtils.h"
#include "deprecated/CCString.h"
/// #include <string>
/// #include <utils/stringutils.h>

#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS && CC_TARGET_PLATFORM != CC_PLATFORM_MAC && CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)

// root name of xml
#define USERDEFAULT_ROOT_NAME    "userDefaultRoot"


using namespace std;

NS_CC_BEGIN

/**
* define the functions here because we don't want to
* export xmlNodePtr and other types in "CCUserDefault.h"
*/

std::map<std::string, UserDefaults*> UserDefaults::_currentInstances;

tinyxml2::XMLElement* UserDefaults::getXMLNodeForKey(const char* pKey, tinyxml2::XMLElement** rootNode, tinyxml2::XMLDocument **doc)
{
	tinyxml2::XMLElement* curNode = nullptr;

	// check the key value
	if (!pKey)
	{
		return nullptr;
	}

	do
	{
		tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
		*doc = xmlDoc;

		std::string xmlBuffer = FileUtils::getInstance()->getStringFromFile(_xmlFileFullPath);

		if (xmlBuffer.empty())
		{
			CCLOG("can not read xml file");
			break;
		}
		xmlDoc->Parse(xmlBuffer.c_str(), xmlBuffer.size());

		// get root node
		*rootNode = xmlDoc->RootElement();
		if (nullptr == *rootNode)
		{
			CCLOG("read root node error");
			break;
		}
		// find the node
		curNode = (*rootNode)->FirstChildElement();
		while (nullptr != curNode)
		{
			const char* nodeName = curNode->Value();
			if (!strcmp(nodeName, pKey))
			{
				break;
			}

			curNode = curNode->NextSiblingElement();
		}
	} while (0);

	return curNode;
}

void UserDefaults::setValueForKey(const char* pKey, const char* pValue)
{
	tinyxml2::XMLElement* rootNode;
	tinyxml2::XMLDocument* doc;
	tinyxml2::XMLElement* node;
	// check the params
	if (!pKey || !pValue)
	{
		return;
	}
	// find the node
	node = getXMLNodeForKey(pKey, &rootNode, &doc);
	// if node exist, change the content
	if (node)
	{
		if (node->FirstChild())
		{
			node->FirstChild()->SetValue(pValue);
		}
		else
		{
			tinyxml2::XMLText* content = doc->NewText(pValue);
			node->LinkEndChild(content);
		}
	}
	else
	{
		if (rootNode)
		{
			tinyxml2::XMLElement* tmpNode = doc->NewElement(pKey);//new tinyxml2::XMLElement(pKey);
			rootNode->LinkEndChild(tmpNode);
			tinyxml2::XMLText* content = doc->NewText(pValue);//new tinyxml2::XMLText(pValue);
			tmpNode->LinkEndChild(content);
		}
	}

	// save file and free doc
	if (doc)
	{
		doc->SaveFile(_xmlFileFullPath.c_str());
		delete doc;
	}
}

/**
* implements of UserDefault
*/

UserDefaults::~UserDefaults()
{
}

UserDefaults::UserDefaults(std::string instanceName)
{
	_instanceName = instanceName;
	_xmlFileFullPath = StringUtils::format("%s/%s.xml", FileUtils::getInstance()->getWritablePath().c_str(), instanceName.c_str());

	if ((!isXMLFileExist()) && (!createXMLFile()))
	{
		return;
	}
}

bool UserDefaults::getBoolForKey(const char* pKey)
{
	return getBoolForKey(pKey, false);
}

bool UserDefaults::getBoolForKey(const char* pKey, bool defaultValue)
{
	const char* value = nullptr;
	tinyxml2::XMLElement* rootNode;
	tinyxml2::XMLDocument* doc;
	tinyxml2::XMLElement* node;
	node = getXMLNodeForKey(pKey, &rootNode, &doc);
	// find the node
	if (node && node->FirstChild())
	{
		value = (const char*)(node->FirstChild()->Value());
	}

	bool ret = defaultValue;

	if (value)
	{
		ret = (!strcmp(value, "true"));
	}

	if (doc) delete doc;

	return ret;
}

int UserDefaults::getIntegerForKey(const char* pKey)
{
	return getIntegerForKey(pKey, 0);
}

int UserDefaults::getIntegerForKey(const char* pKey, int defaultValue)
{
	const char* value = nullptr;
	tinyxml2::XMLElement* rootNode;
	tinyxml2::XMLDocument* doc;
	tinyxml2::XMLElement* node;
	node = getXMLNodeForKey(pKey, &rootNode, &doc);
	// find the node
	if (node && node->FirstChild())
	{
		value = (const char*)(node->FirstChild()->Value());
	}

	int ret = defaultValue;

	if (value)
	{
		ret = atoi(value);
	}

	if (doc)
	{
		delete doc;
	}


	return ret;
}

float UserDefaults::getFloatForKey(const char* pKey)
{
	return getFloatForKey(pKey, 0.0f);
}

float UserDefaults::getFloatForKey(const char* pKey, float defaultValue)
{
	float ret = (float)getDoubleForKey(pKey, (double)defaultValue);

	return ret;
}

double  UserDefaults::getDoubleForKey(const char* pKey)
{
	return getDoubleForKey(pKey, 0.0);
}

double UserDefaults::getDoubleForKey(const char* pKey, double defaultValue)
{
	const char* value = nullptr;
	tinyxml2::XMLElement* rootNode;
	tinyxml2::XMLDocument* doc;
	tinyxml2::XMLElement* node;
	node = getXMLNodeForKey(pKey, &rootNode, &doc);
	// find the node
	if (node && node->FirstChild())
	{
		value = (const char*)(node->FirstChild()->Value());
	}

	double ret = defaultValue;

	if (value)
	{
		ret = utils::atof(value);
	}

	if (doc) delete doc;

	return ret;
}

std::string UserDefaults::getStringForKey(const char* pKey)
{
	return getStringForKey(pKey, "");
}

string UserDefaults::getStringForKey(const char* pKey, const std::string & defaultValue)
{
	const char* value = nullptr;
	tinyxml2::XMLElement* rootNode;
	tinyxml2::XMLDocument* doc;
	tinyxml2::XMLElement* node;
	node = getXMLNodeForKey(pKey, &rootNode, &doc);
	// find the node
	if (node && node->FirstChild())
	{
		value = (const char*)(node->FirstChild()->Value());
	}

	string ret = defaultValue;

	if (value)
	{
		ret = string(value);
	}

	if (doc) delete doc;

	return ret;
}

Data UserDefaults::getDataForKey(const char* pKey)
{
	return getDataForKey(pKey, Data::Null);
}

Data UserDefaults::getDataForKey(const char* pKey, const Data& defaultValue)
{
	const char* encodedData = nullptr;
	tinyxml2::XMLElement* rootNode;
	tinyxml2::XMLDocument* doc;
	tinyxml2::XMLElement* node;
	node = getXMLNodeForKey(pKey, &rootNode, &doc);
	// find the node
	if (node && node->FirstChild())
	{
		encodedData = (const char*)(node->FirstChild()->Value());
	}

	Data ret = defaultValue;

	if (encodedData)
	{
		unsigned char * decodedData = nullptr;
		int decodedDataLen = base64Decode((unsigned char*)encodedData, (unsigned int)strlen(encodedData), &decodedData);

		if (decodedData) {
			ret.fastSet(decodedData, decodedDataLen);
		}
	}

	if (doc) delete doc;

	return ret;
}


void UserDefaults::setBoolForKey(const char* pKey, bool value)
{
	// save bool value as string

	if (true == value)
	{
		setStringForKey(pKey, "true");
	}
	else
	{
		setStringForKey(pKey, "false");
	}
}

void UserDefaults::setIntegerForKey(const char* pKey, int value)
{
	// check key
	if (!pKey)
	{
		return;
	}

	// format the value
	char tmp[50];
	memset(tmp, 0, 50);
	sprintf(tmp, "%d", value);

	setValueForKey(pKey, tmp);
}

void UserDefaults::setFloatForKey(const char* pKey, float value)
{
	setDoubleForKey(pKey, value);
}

void UserDefaults::setDoubleForKey(const char* pKey, double value)
{
	// check key
	if (!pKey)
	{
		return;
	}

	// format the value
	char tmp[50];
	memset(tmp, 0, 50);
	sprintf(tmp, "%f", value);

	setValueForKey(pKey, tmp);
}

void UserDefaults::setStringForKey(const char* pKey, const std::string & value)
{
	// check key
	if (!pKey)
	{
		return;
	}

	setValueForKey(pKey, value.c_str());
}

void UserDefaults::setDataForKey(const char* pKey, const Data& value) {
	// check key
	if (!pKey)
	{
		return;
	}

	char *encodedData = 0;

	base64Encode(value.getBytes(), static_cast<unsigned int>(value.getSize()), &encodedData);

	setValueForKey(pKey, encodedData);

	if (encodedData)
		free(encodedData);
}

UserDefaults* UserDefaults::getInstance(std::string instanceName)
{
	if (_currentInstances[instanceName] == nullptr)
	{
		// only create xml file one time
		// the file exists after the program exit
		

		UserDefaults * user = new (std::nothrow) UserDefaults(instanceName);
		_currentInstances[instanceName] = user;
	}

	return _currentInstances[instanceName];
}


void UserDefaults::destroyInstance()
{
	
}

bool UserDefaults::isXMLFileExist()
{
	return FileUtils::getInstance()->isFileExist(_xmlFileFullPath);
}


// create new xml file
bool UserDefaults::createXMLFile()
{
	bool bRet = false;
	tinyxml2::XMLDocument *pDoc = new tinyxml2::XMLDocument();
	if (nullptr == pDoc)
	{
		return false;
	}
	tinyxml2::XMLDeclaration *pDeclaration = pDoc->NewDeclaration(nullptr);
	if (nullptr == pDeclaration)
	{
		return false;
	}
	pDoc->LinkEndChild(pDeclaration);
	tinyxml2::XMLElement *pRootEle = pDoc->NewElement(USERDEFAULT_ROOT_NAME);
	if (nullptr == pRootEle)
	{
		return false;
	}
	pDoc->LinkEndChild(pRootEle);
	bRet = tinyxml2::XML_SUCCESS == pDoc->SaveFile(_xmlFileFullPath.c_str());

	if (pDoc)
	{
		delete pDoc;
	}

	return bRet;
}

string UserDefaults::getXMLFilePath()
{
	return _xmlFileFullPath;
}

void UserDefaults::flush()
{
}

NS_CC_END

#endif // (CC_TARGET_PLATFORM != CC_PLATFORM_IOS && CC_PLATFORM != CC_PLATFORM_ANDROID)
