//
//  DetailBar.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/13/16.
//
//

#include "DetailBar.hpp"
#include "CommonHelper.hpp"

DetailBar::DetailBar(Creature * creature)
{
    _creature = creature;
    _baseSprite = ScaledSprite::create("Others/CreatureDetail.png");
    
    // Name and Occupation
    std::string nameOccupation = StringUtils::format("%s  %s", creature->getDefinition()->name.c_str(), creature->getDefinition()->getOccupationName().c_str());
    Label * nameOccupationLabel = Label::createWithTTF(nameOccupation.c_str(), "fonts/mini_black.ttf", 16);
    nameOccupationLabel->setAnchorPoint(Vec2(0, 0));
    _baseSprite->addLabel(nameOccupationLabel, Vec2(5, 62));
    
    Sprite * hpBar = Sprite::create("Others/CreatureDetailBarHp.png");
    hpBar->setAnchorPoint(Vec2(0, 0));
    hpBar->setScaleX((float)creature->creatureData()->hpCurrent / creature->creatureData()->hpMax);
    _baseSprite->addChild(hpBar, Vec2(105, 55));
    
    if (creature->creatureData()->mpCurrent > 0 && creature->creatureData()->mpMax > 0) {
        Sprite * mpBar = Sprite::create("Others/CreatureDetailBarMp.png");
        mpBar->setAnchorPoint(Vec2(0, 0));
        mpBar->setScaleX((float)creature->creatureData()->mpCurrent / creature->creatureData()->mpMax);
        _baseSprite->addChild(mpBar, Vec2(105, 35));
    }
    
    int numberFontSize = 10;
    int hpmpFontSize = 8;
    int column[] = { 30, 70 };
    int row[] = { 55, 44, 33, 22, 11 };
    
    // Show HP and HP Max
    Label * hpLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->hpCurrent, 3), "fonts/mini_black.ttf", hpmpFontSize);
    Label * hpMaxLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->hpMax, 3), "fonts/mini_black.ttf", hpmpFontSize);
    _baseSprite->addLabel(hpLabel, Vec2(180, 47));
    _baseSprite->addLabel(hpMaxLabel, Vec2(210, 47));
    
    // Show MP and MP Max
    Label * mpLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->mpCurrent, 3), "fonts/mini_black.ttf", hpmpFontSize);
    Label * mpMaxLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->mpMax, 3), "fonts/mini_black.ttf", hpmpFontSize);
    _baseSprite->addLabel(mpLabel, Vec2(180, 27));
    _baseSprite->addLabel(mpMaxLabel, Vec2(210, 27));
    
    // DX
    Label * dxLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->dx, 2), "fonts/mini_black.ttf", numberFontSize);
    _baseSprite->addLabel(dxLabel, Vec2(column[0], row[2]));
    
    // HIT
    Label * hitLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->calculatedHit(), 2), "fonts/mini_black.ttf", numberFontSize);
    _baseSprite->addLabel(hitLabel, Vec2(column[0], row[3]));
    
    // EV
    Label * evLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->calculatedEv(), 2), "fonts/mini_black.ttf", numberFontSize);
    _baseSprite->addLabel(evLabel, Vec2(column[0], row[4]));
    
    
    // LV
    Label * lvLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->level, 2), "fonts/mini_black.ttf", numberFontSize);
    _baseSprite->addLabel(lvLabel, Vec2(column[1], row[0]));
    
    // EX
    Label * exLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->ex, 2), "fonts/mini_black.ttf", numberFontSize);
    _baseSprite->addLabel(exLabel, Vec2(column[1], row[1]));
    
    // MV
    Label * mvLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->mv, 2), "fonts/mini_black.ttf", numberFontSize);
    _baseSprite->addLabel(mvLabel, Vec2(column[1], row[2]));
    
    // AP
    Label * apLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->calculatedAp(), 2), "fonts/mini_black.ttf", numberFontSize);
    _baseSprite->addLabel(apLabel, Vec2(column[1], row[3]));
    
    // DP
    Label * dpLabel = Label::createWithTTF(CommonHelper::IntegerToStringWithMaxValue(creature->creatureData()->calculatedDp(), 2), "fonts/mini_black.ttf", numberFontSize);
    _baseSprite->addLabel(dpLabel, Vec2(column[1], row[4]));
    
    
    // Status
}


ScaledSprite * DetailBar::getSprite()
{
    return _baseSprite;
}
