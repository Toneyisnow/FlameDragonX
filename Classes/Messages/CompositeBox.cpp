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
    _datoPosition1 = Vec2(152, 140);
    _detailPosition0 = Vec2(154, 302);
    _detailPosition1 = Vec2(154, 140);
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
    this->addComponent(_datoBar->getSprite(), Vec2(1.0f, 0.0f), (_messageLayer != nullptr) ? _datoPosition0 : _datoPosition1);
    
    _detailBar = new DetailBar(_creature);
    this->addComponent(_detailBar->getSprite(), Vec2(0.0f, 0.0f), (_messageLayer != nullptr) ? _detailPosition0 : _detailPosition1);
    
    if (_type == MessageBoxType_Item) {
        _mainBox = new ItemBox(_creature, _operatingType);
    }
    else
    {
        _mainBox = new MagicBox(_creature, _operatingType);
    }
    
    this->addComponent(_mainBox->getSprite(), Vec2(0.5f, 1.0f), (_messageLayer != nullptr) ? _mainPosition0 : _mainPosition1);
}

void CompositeBox::removeDialog()
{
    this->removeChildFromLayer(_datoBar->getSprite());
    this->removeChildFromLayer(_detailBar->getSprite());
    this->removeChildFromLayer(_mainBox->getSprite());
    
    _datoBar->release();
    _detailBar->release();
    _mainBox->release();
}

void CompositeBox::addComponent(ScaledSprite * component, Vec2 anchorPoint, Vec2 position)
{
    component->setAnchorPoint(anchorPoint);
    component->setPosition(position);
    component->setScale(DEFAULT_MESSAGEBOX_SCALE);
    
    this->addChildToLayer(component);
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
    if (location.y > 160) {
        _returnValue = -1;
        this->closeDialog();
        return;
    }
    
    Vec2 mainBoxLocation = _mainBox->getSprite()->getPosition();
    float convertedX = (location.x - mainBoxLocation.x) / _mainBox->getSprite()->getScale() + _mainBox->getSprite()->getContentSize().width / 2;
    float convertedY = (location.y - mainBoxLocation.y) / _mainBox->getSprite()->getScale() + _mainBox->getSprite()->getContentSize().height;
    
    int result = _mainBox->handleClick(Vec2(convertedX, convertedY));
    if (result >= 0) {
        _returnValue = result;
        this->closeDialog();
    }
    
}
