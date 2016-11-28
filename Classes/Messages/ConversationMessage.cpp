//
//  ConversationMessage.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/19/16.
//
//

#include "ConversationMessage.hpp"
#include "MessageLayer.hpp"


/*

void HelloWorld::testFont()
{
	char * test = "12345";
	utf8::next(test, test + 6);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Dictionary *language = Dictionary::createWithContentsOfFile("ch.plist");

	String* str = (String*)language->objectForKey("004");
	std::string localizedString(str->getCString());

	String* item = (String*)language->objectForKey("005");
	
	std::string filledString = StringUtils::format(localizedString.c_str(), item->getCString());
	
	
	int wholesize = filledString.size();
	char* wholeLine = new char[wholesize + 1];
	strcpy(wholeLine, filledString.c_str());
	char * end = wholeLine + wholesize;

	int CHAR_PER_LINE = 11;
	int LINE_PER_SCREEN = 3;

	int charCount = 0;
	char* w = wholeLine;
	char* last = wholeLine;
	Vector<String *> sentenceList;
	while (w <= end)
	{
		if (w == end)
		{
			break;
		}
		
		charCount++;
		utf8::next(w, end);
		
		if (*w == '#' || charCount >= CHAR_PER_LINE || w >= end)
		{
			cocos2d::log("Split line.");

			int charsize = w - last;
			

			char * currentLine = new char[charsize + 1];
			strncpy(currentLine, last, charsize);
			currentLine[charsize] = '\0';

			std::string result(currentLine);
			sentenceList.pushBack(new String(currentLine));

			last = w;
			charCount = 0;
			if (*w == '#')
			{
				last++;
			}
		}
	}
	
	for (int i = 0; i < sentenceList.size(); i++)
	{
		String *sentence = sentenceList.at(i);
		auto label = Label::createWithTTF(sentence->getCString(), "fonts/mini_black.ttf", 24);

		label->setColor(Color3B(255, 0, 0));
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height - i * 30));

		this->addChild(label, 1);
	}

}


*/

ConversationMessage::ConversationMessage(std::string content)
: ConversationMessage(nullptr, content)
{
    
}

ConversationMessage::ConversationMessage(Creature * creature, std::string content)
{
    _creature = creature;
    _content = content;
    _upScreen = Vec2(240, 170);
    _downScreen = Vec2(240, 10);
}

void ConversationMessage::initDialog()
{
    buildBaseDialog(_downScreen);
    
}

void ConversationMessage::buildBaseDialog(Vec2 screenPosition)
{
    _messageBox = ScaledSprite::create("Others/MessageBox.png");
    _messageBox->setPosition(screenPosition);
    _messageBox->setAnchorPoint(Vec2(0.5f, 0));
    _messageBox->setScale(Constants::DEFAULT_MESSAGEBOX_SCALE);
    
    this->addChildToLayer(_messageBox);
    
    int creatureDatoId = (_creature != nullptr ? _creature->getDefinition()->animationId : 0);
    Sprite * dato = Sprite::create(StringUtils::format("Dato/Dato-%03d-1.png", creatureDatoId));
    dato->setAnchorPoint(Vec2(0, 0));
    _messageBox->addChild(dato, Vec2(3, 3));
    
    auto label = Label::createWithTTF(_content.c_str(), "fonts/mini_black.ttf", 14);
    label->setColor(Color3B(255, 255, 255));
    label->setAnchorPoint(Vec2(0, 0.5f));
    _messageBox->addLabel(label, Vec2(80, 60));

}

void ConversationMessage::removeDialog()
{
    this->removeChildFromLayer(_messageBox);
}

FDActivity * ConversationMessage::onEnterActivity()
{
    return nullptr;
}

FDActivity * ConversationMessage::onExitActivity()
{
    return nullptr;
}

void ConversationMessage::handleClick(Vec2 location)
{
    _returnValue = 0;
    
    this->closeDialog();
}
