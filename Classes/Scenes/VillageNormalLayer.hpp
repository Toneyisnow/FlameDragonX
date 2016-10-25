//
//  VillageNormalLayer.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/24/16.
//
//

#ifndef VillageNormalLayer_hpp
#define VillageNormalLayer_hpp

#include "cocos2d.h"
#include "VillageLayer.hpp"
#include "ConfirmMessage.hpp"
#include "VillageLabel.hpp"

class VillageNormalLayer : public VillageLayer
{
    
private:
    
    ConfirmMessage * _confirmExitMessage;
    int _cursorPositionIndex;
    ScaledSprite * _cursor;
    FDAnimate * _cursorAnimate;
    
    VillageLabel * _villageLabel;
    int _tickCount;
    
    int getVillageImageId();
    Vec2 getCursorPosition(int positionIndex);
    void setCursorPositionIndex(int positionIndex);
    bool clickedOnPosition(Vec2 clickedPos, Vec2 position);

    void enterShop();
    void promptExit();
    void confirmExit(int returnValue);
    
    
public:
    
    virtual bool init() override;
    CREATE_FUNC(VillageNormalLayer);
    ~VillageNormalLayer();
    
    
    virtual void loadWithRecord(ChapterRecord * record) override;
    
    bool onClicked(Touch* touch, Event* event);
    void takeDeltaTimeTck(float dt);
    
};

#endif /* VillageNormalLayer_hpp */
