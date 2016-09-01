//
//  GlobalActivity.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/1/16.
//
//

#include "GlobalActivity.hpp"
#include "BattleScene.hpp"

GlobalActivity::GlobalActivity(BattleScene * game)
: FieldActivity(game->getBattleField())
{
    this->_game = game;
}
