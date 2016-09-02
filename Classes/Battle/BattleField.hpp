//
//  BattleField.hpp
//  FlameDragonX
//
//  Created by SuiYi on 8/23/16.
//
//

#ifndef BattleField_hpp
#define BattleField_hpp

#include "cocos2d.h"
#include "TouchHandler.hpp"
#include "Ground.hpp"
#include "Creature.hpp"

class BattleScene;

USING_NS_CC;

class BattleField : public cocos2d::Layer
{
private:
    
    const int BLOCK_SIZE = 24;
    
    BattleScene * _battleScene;
    
    Sprite * _groundImage;
    
    float _displayScale;
    float _displayBlockSize;
    
    Vector<Ground *> * _groundMetrix;
    
    TouchHandler * _touchHandler;
    
    int _fieldWidth;
    int _fieldHeight;
    int _treasureCount;
    
    void initGroundMetrix(int chapterId);
    
    
    Vector<Creature *> * _friendList;
    Vector<Creature *> * _enemyList;
    Vector<Creature *> * _npcList;
    
    
    // Private Methods
    
    
    
    
public:
    
    BattleField();
    BattleField(BattleScene * scene, int chapterId);
    ~BattleField();
    
    void initWithChapter(int chapterId);
    
    Vec2 getFieldPositionOnScreen();
    void setFieldPositionOnScreen(float x, float y);
    Size getFieldSizeOnScreen();
    
    float getDisplayScale();
    
    Ground * groundAt(int x, int y);
    
    Creature * getCreatureAt(int x, int y);
    
    Vector<Creature *> * getFriendList();
    Vector<Creature *> * getEnemyList();
    Vector<Creature *> * getNPCList();
    
    void takeTick(int synchronizedTick);
    
    Vec2 convertPositionToLocation(Vec2 pos);
    Vec2 convertLocationToPosition(Vec2 loc);
    
    //void activityMoveCreature(Vec2 position, Vec2 target);
    //void activityMoveCreatureWithMenu(Vec2 position, Vec2 target);
    
    void addCreature(Creature * creature, Vec2 position);
    
};

#endif /* BattleField_hpp */
