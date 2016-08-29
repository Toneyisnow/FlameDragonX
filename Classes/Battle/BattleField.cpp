//
//  BattleField.cpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#include "BattleField.hpp"
#include "StringUtil.hpp"
#include "TextFileReader.hpp"
#include "AnimationLibrary.hpp"
#include "CreatureMoveActivity.hpp"
#include "BattleScene.hpp"

USING_NS_CC;

using namespace cocos2d::ui;

BattleField::BattleField()
{
    
}

BattleField::BattleField(BattleScene * scene, int chapterId)
{
    this->_battleScene = scene;
    
    this->initWithChapter(chapterId);
}

BattleField::~BattleField()
{
    
    if (_groundMetrix != nullptr)
    {
        _groundMetrix->clear();
    }
    
    if (_friendList != nullptr)
    {
        _friendList->clear();
    }
    if (_enemyList != nullptr)
    {
        _enemyList->clear();
    }
    if (_npcList != nullptr)
    {
        _npcList->clear();
    }
}

void BattleField::initWithChapter(int chapterId)
{
    std::string filename = StringUtil::format("Maps/Chapter-%02d.png", chapterId);
    _groundImage = Sprite::create(filename);
    _groundImage->setAnchorPoint(Vec2(0, 0));
    
    auto size = Director::getInstance()->getWinSize();
    auto sizein = Director::getInstance()->getWinSizeInPixels();
    
    _displayScale = 1.5f * sizein.width / size.width;
    _displayBlockSize = (float)BLOCK_SIZE * size.width / sizein.width ;
    
    _groundImage->setScale(_displayScale);
    
    this->addChild(_groundImage, 1);
    
    // Adding controls to map
    _touchHandler = new TouchHandler(this);
    
    // Init Metrix
    this->initGroundMetrix(chapterId);
    
    // Init Creatures
    this->_friendList = new Vector<Creature *>();
    this->_enemyList = new Vector<Creature *>();
    this->_npcList = new Vector<Creature *>();
    
    
    Creature * creature = new Creature(CreatureType_Friend);
    creature->initWithDefinition(1, 1);
    this->addCreature(creature, Vec2(3, 24));
    Creature * creature2 = new Creature(CreatureType_Friend);
    creature2->initWithDefinition(2, 2);
    this->addCreature(creature2, Vec2(2, 2));
    
    this->activityMoveCreature(Vec2(3, 24), Vec2(3, 2));
    this->activityMoveCreature(Vec2(3, 24), Vec2(10, 2));
    
    //// creature->setGesture(GestureStatus_WalkingLeft);
    
    /*
    Texture2D * texture = Director::getInstance()->getTextureCache()->addImage("Icons/001/Icon-001-02.png");
    sprite->setTexture(texture);
    */
    // image->get
    /*
    //Sprite * test = Sprite::create("Icons/001/Icon-001-02.png");
    Sprite * test = Sprite::create();
    test->setTexture("Icons/001/Icon-001-02.png");
    
    Vec2 location = this->convertPositionToLocation(Vec2(24, 24));
    test->setPosition(location);
    _groundImage->addChild(test, 10);
    Sprite * test2 = Sprite::create("Icons/001/Icon-001-02.png");
    Vec2 location2 = this->convertPositionToLocation(Vec2(1, 1));
    test2->setPosition(location2);
    _groundImage->addChild(test2, 10);
     */
}

Vec2 BattleField::getFieldPositionOnScreen()
{
    return _groundImage->getPosition();
}

void BattleField::setFieldPositionOnScreen(float x, float y)
{
    _groundImage->setPosition(Vec2(x, y));
}

Size BattleField::getFieldSizeOnScreen()
{
    return _groundImage->getBoundingBox().size;
}

float BattleField::getDisplayScale()
{
    return _displayScale;
}

void BattleField::initGroundMetrix(int chapterId)
{
    _groundMetrix = new Vector<Ground *>();
    
    std::string filename = StringUtil::format("Data/Maps/Chapter-%02d.dat", chapterId);
    TextFileReader * reader = new TextFileReader(filename);
    
    _fieldWidth = reader->readInt();
    _fieldHeight = reader->readInt();
    
    for (int j = 1; j <= _fieldHeight; j++) {
        for (int i = 1; i <= _fieldWidth; i++) {
            
            GroundType type = (GroundType)reader->readInt();
            Ground * ground = Ground::createGround(type);
            
            _groundMetrix->pushBack(ground);
            
            
        }
    }
    
    _treasureCount = reader->readInt();
    for(int i = 0; i < _treasureCount; i++)
    {
        
    }
    
    reader->release();
}

Ground * BattleField::groundAt(int x, int y)
{
    if (x <= 0 || y <= 0 || x > _fieldWidth || y > _fieldHeight)
    {
        return nullptr;
    }
    
    return _groundMetrix->at((y - 1) * _fieldWidth + x - 1);
}

Creature * BattleField::getCreatureAt(int x, int y)
{
    if (x <= 0 || y <= 0 || x > _fieldWidth || y > _fieldHeight)
    {
        return nullptr;
    }
    
    for(Vector<Creature *>::iterator it = _friendList->begin(); it != _friendList->end(); it++)
    {
        Creature * creature = *it;
        Vec2 position = convertLocationToPosition(creature->getSprite()->getPosition());
        if (position.x == x && position.y == y)
        {
            return creature;
        }
    }
    
    return nullptr;
}

Vec2 BattleField::convertPositionToLocation(Vec2 pos)
{
    float locX = (pos.x - 1) * _displayBlockSize + _displayBlockSize / 2;
    float locY = (_fieldHeight - pos.y) * _displayBlockSize + _displayBlockSize / 2;
    
    return Vec2(locX, locY);
}

Vec2 BattleField::convertLocationToPosition(Vec2 loc)
{
    int posX = loc.x / _displayBlockSize + 1;
    int posY = _fieldHeight - loc.y / _displayBlockSize + 1;
    
    return Vec2(posX, posY);
}

void BattleField::addCreature(Creature * creature, Vec2 position)
{
    Vec2 location = this->convertPositionToLocation(position);
    creature->getSprite()->setPosition(location);
    _groundImage->addChild(creature->getSprite(), BattleObjectOrder_Creature);
    
     switch(creature->getType())
    {
        case CreatureType_Friend:
            this->_friendList->pushBack(creature);
            break;
        case CreatureType_Enemy:
            this->_enemyList->pushBack(creature);
            break;
        case CreatureType_Npc:
            this->_npcList->pushBack(creature);
            break;
        default:
            break;
    }
}


void BattleField::activityMoveCreature(Vec2 position, Vec2 target)
{
    Creature * creature = this->getCreatureAt(position.x , position.y);
    CreatureMoveActivity * activity = new CreatureMoveActivity(this, creature, target);
    
    _battleScene->getActivityQueue()->pushBackActivity(activity);
    activity->release();
}

void BattleField::activityMoveCreatureWithMenu(Vec2 position, Vec2 target)
{
    
}

void BattleField::takeTick(int synchronizedTick)
{
    for(Vector<Creature *>::iterator it = _friendList->begin(); it != _friendList->end(); it++)
    {
        Creature * creature = *it;
        creature->takeTick(synchronizedTick);
    }
    
    for(Vector<Creature *>::iterator it = _enemyList->begin(); it != _enemyList->end(); it++)
    {
        Creature * creature = *it;
        creature->takeTick(synchronizedTick);
    }

    for(Vector<Creature *>::iterator it = _npcList->begin(); it != _npcList->end(); it++)
    {
        Creature * creature = *it;
        creature->takeTick(synchronizedTick);
    }
}
