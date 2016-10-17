//
//  AIFactory.cpp
//  FlameDragonX
//
//  Created by SuiYi on 10/17/16.
//
//

#include "AIFactory.hpp"
#include "AIAggressiveDelegate.hpp"
#include "BattleScene.hpp"

AIDelegate * AIFactory::generateAI(AICreature * aiCreature, BattleScene * scene)
{
    AIDelegate * delegate = nullptr;
    
    switch (aiCreature->getAIType()) {
        case AIType_Aggressive:
            delegate = new AIAggressiveDelegate(aiCreature, scene);
            break;
            
        default:
            break;
    }
    
    if (delegate != nullptr)
    {
        delegate->autorelease();
    }
    
    return delegate;
}
