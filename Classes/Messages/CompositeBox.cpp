//
//  MessageBox.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#include "CompositeBox.hpp"
#include "MessageLayer.hpp"
#include "ItemBox.hpp"
#include "MagicBox.hpp"
#include "SpriteMoveActivity.hpp"
#include "BatchActivity.hpp"

CompositeBox::CompositeBox(Creature * creature, MessageBoxType type, MessageBoxOperatingType oType)
{
    this->_creature = creature;
    this->_type = type;
    this->_operatingType = oType;
    
    _datoPosition0 = Vec2(0, 140);
    _datoPosition1 = Vec2(174, 140);
    _detailPosition0 = Vec2(176, 302);
    _detailPosition1 = Vec2(176, 140);
    _mainPosition0 = Vec2(240, 0);
    _mainPosition1 = Vec2(240, 138);
    
    _flyInflyOutDuration = 0.1f;
}

CompositeBox::~CompositeBox()
{
    
}

void CompositeBox::initDialog()
{
    _datoBar = new DatoBar(_creature->getDefinition()->animationId);
    this->addComponent(_datoBar->getSprite(), Vec2(1.0f, 0.0f), _datoPosition0);
    
    _detailBar = new DetailBar(_creature);
    this->addComponent(_detailBar->getSprite(), Vec2(0.0f, 0.0f), _detailPosition0);
    
    if (_type == MessageBoxType_Item) {
        _mainBox = new ItemBox(_creature, _operatingType);
    }
    else
    {
        _mainBox = new MagicBox(_creature, _operatingType);
    }
    
    this->addComponent(_mainBox->getSprite(), Vec2(0.5f, 1.0f), _mainPosition0);
}

void CompositeBox::removeDialog()
{
    _messageLayer->removeChild(_datoBar->getSprite());
    _messageLayer->removeChild(_detailBar->getSprite());
    _messageLayer->removeChild(_mainBox->getSprite());
    
    _datoBar->release();
    _detailBar->release();
    _mainBox->release();
}

void CompositeBox::addComponent(Sprite * component, Vec2 anchorPoint, Vec2 position)
{
    component->setAnchorPoint(anchorPoint);
    component->setPosition(position);
    component->setScale(DEFAULT_MESSAGEBOX_SCALE);
    _messageLayer->addChild(component);
}

FDActivity * CompositeBox::onEnterActivity()
{
    BatchActivity* batchActivity = new BatchActivity();
    
    auto activity1 = new SpriteMoveActivity(_datoBar->getSprite(), _datoPosition1, _flyInflyOutDuration);
    auto activity2 = new SpriteMoveActivity(_detailBar->getSprite(), _detailPosition1, _flyInflyOutDuration);
    auto activity3 = new SpriteMoveActivity(_mainBox->getSprite(), _mainPosition1, _flyInflyOutDuration);
    
    batchActivity->addActivity(activity1);
    batchActivity->addActivity(activity2);
    batchActivity->addActivity(activity3);
    
    activity1->release();
    activity2->release();
    activity3->release();
    
    return batchActivity;
}

FDActivity * CompositeBox::onExitActivity()
{
    BatchActivity* batchActivity = new BatchActivity();
    
    auto activity1 = new SpriteMoveActivity(_datoBar->getSprite(), _datoPosition0, _flyInflyOutDuration);
    auto activity2 = new SpriteMoveActivity(_detailBar->getSprite(), _detailPosition0, _flyInflyOutDuration);
    auto activity3 = new SpriteMoveActivity(_mainBox->getSprite(), _mainPosition0, _flyInflyOutDuration);
    
    batchActivity->addActivity(activity1);
    batchActivity->addActivity(activity2);
    batchActivity->addActivity(activity3);
    
    activity1->release();
    activity2->release();
    activity3->release();
    
    return batchActivity;
}

void CompositeBox::handleClick(Vec2 location)
{
    _returnValue = 0;
    this->closeDialog();
    
}