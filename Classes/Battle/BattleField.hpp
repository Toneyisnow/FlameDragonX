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
#include "Cursor.hpp"
#include "StateDispatcher.hpp"
#include "MenuCursor.hpp"

class BattleScene;

USING_NS_CC;

class BattleField : public cocos2d::Layer
{
private:
    
    const int BLOCK_SIZE = 24;
    
    int DEFAULT_DISPLAY_SCALE;
    int MIN_DISPLAY_SCALE;
    int MAX_DISPLAY_SCALE;
    
    BattleScene * _battleScene;
    
    Sprite * _groundImage;
    Sprite * _coverImage;
    
    bool _hasCoverImage;
    
    float _displayScale;
    float _displayBlockSize;
    
    Vector<Ground *> * _groundMetrix;
    
    TouchHandler * _touchHandler;
    StateDispatcher * _stateDispatcher;
    
    int _fieldWidth;
    int _fieldHeight;
    int _treasureCount;
    
    
    Cursor * _cursor;
    Vector<Creature *> * _friendList;
    Vector<Creature *> * _enemyList;
    Vector<Creature *> * _npcList;
    Vector<BattleObject *> * _battleObjectList;
    Vector<Creature *> * _deadCreatureList;
    
    // Private Methods
    
    void initData(int chapterId);
    
    void sendObjectToGround(BattleObject * obj, Vec2 position);
    
    
public:
    
    BattleField();
    BattleField(BattleScene * scene);
    ~BattleField();
    
    BattleScene * getBattleScene();
    
    void initWithChapter(int chapterId);
    
    Vec2 getFieldPositionOnScreen();
    void setFieldPositionOnScreen(float x, float y);
    Size getFieldSizeOnScreen();
    
    float getDisplayScale();
    void setDisplayScale(float scale);
    
    Size getFieldSize();
    
    Ground * groundAt(int x, int y);
    
    Creature * getCreatureAt(int x, int y);
    Creature * getCreatureById(int creatureId);
    Creature * getDeadCreatureById(int creatureId);
    Vec2 getObjectPosition(BattleObject * obj);
    void setObjectPosition(BattleObject * obj, Vec2 position);
    BattleObject * getObjectByPosition(BattleObjectType type, Vec2 position);
    
    Vector<Creature *> * getFriendList();
    Vector<Creature *> * getEnemyList();
    Vector<Creature *> * getNPCList();
    Vector<Creature *> * getDeadCreatureList();
    
    void takeTick(int synchronizedTick);
    void notifyStateDispatcher();
    
    Vec2 convertPositionToLocation(Vec2 pos);
    Vec2 convertLocationToPosition(Vec2 loc);
    Vec2 getScreenLocationByLocation(Vec2 loc);
    
    //void activityMoveCreature(Vec2 position, Vec2 target);
    //void activityMoveCreatureWithMenu(Vec2 position, Vec2 target);
    
    void addCreature(Creature * creature, Vec2 position);
    void addObject(BattleObject * obj, Vec2 position);
    void removeObject(BattleObject * obj);
    
    void onClickedAt(Vec2 location);
    
    void setCursorTo(Vec2 position);
    void moveCursorTo(Vec2 position);
    Vec2 getCursorPosition();
    void setCursorObjectTo(Ref * position);
    
    bool isInteractiveBusy();
    
    void showCreatureMenuAt(int menuId, Vec2 position, Creature * creature);
    void showSystemMenuAt(int menuId, Vec2 position);
    void closeMenu(bool withAnimation);
    void setActiveMenuCursor(MenuCursor * menuCursor);
    
    bool isPositionInScope(Vec2 position);
    
    void removeAllIndicators();
    int getObjectDistance(BattleObject * c1, BattleObject * c2);
    int getPositionDistance(Vec2 position1, Vec2 position2);
    
    bool hasAdjacentFriend(Creature * creature);
    Vector<Creature *> getCreaturesInRange(Vec2 position, int range, bool badGuy);
    Vector<Creature *> searchTargetInAttackRange(Creature * creature);
    Vector<Creature *> searchTargetInMagicRange(Creature * creature, int magicId);
    Vector<Creature *> getHostileCreatureList(CreatureType type);
    
};

#endif /* BattleField_hpp */
