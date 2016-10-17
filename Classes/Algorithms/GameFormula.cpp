//
//  GameFormula.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/11/16.
//
//

#include "GameFormula.hpp"
#include "BattleField.hpp"
#include "FDRandom.hpp"
#include "AttackItemDefinition.hpp"

FightResult * GameFormula::dealWithFight(BattleField * field, Creature * subject, Creature * target)
{
    FightResult * result = new FightResult(subject, target);
    
    CounterResult * attack1 = singleAttack(field, subject, target);
    result->setAttackInfo1(attack1);
    
    int exp1 = calculateExperience(subject, target, attack1);
    int exp2 = 0;
    int backexp1 = 0;
    int backexp2 = 0;
    
    if (target->creatureData()->hpCurrent > 0)
    {
        bool isDoubleHit = FDRandom::hitWithRate(GameFormula::commonDoubleAttackRate());
        if (isDoubleHit) {
            CounterResult * attack2 = singleAttack(field, subject, target);
            result->setAttackInfo2(attack2);
            exp2 = calculateExperience(subject, target, attack2);
        }
        
        if (target->creatureData()->hpCurrent > 0)
        {
            subject->setLastGainedExperience(exp1 + exp2);
        }
        else
        {
            subject->setLastGainedExperience(exp2);
        }
    }
    else
    {
        subject->setLastGainedExperience(exp1);
    }
    
    // Fight back
    bool canFightBack = (target->creatureData()->getAttackItem() != nullptr
                         && field->getObjectDistance(subject, target) == 1);
    if (canFightBack && target->creatureData()->hpCurrent > 0)
    {
        CounterResult * back1 = singleAttack(field, target, subject);
        result->setFightBackInfo1(back1);
        backexp1 = calculateExperience(target, subject, back1);
        
        bool isDoubleHit = FDRandom::hitWithRate(GameFormula::commonDoubleAttackRate());
        if (isDoubleHit) {
            CounterResult * back2 = singleAttack(field, target, subject);
            result->setFightBackInfo2(back2);
            backexp2 = calculateExperience(target, subject, back2);
            
            if (subject->creatureData()->hpCurrent > 0)
            {
                target->setLastGainedExperience(exp1 + exp2);
            }
            else
            {
                target->setLastGainedExperience(exp2);
            }
        }
        else
        {
            target->setLastGainedExperience(exp1);
        }
    }
    
    
    result->autorelease();
    return result;
}

MagicResult * GameFormula::dealWithMagic(BattleField * field, Creature * subject, Vector<Creature * > targets, int magicId)
{
    MagicResult * result = new MagicResult(subject, magicId, targets);
    result->autorelease();
    
    return result;
}

CounterResult * GameFormula::singleAttack(BattleField * field, Creature * subject, Creature * target)
{
    CounterResult * result = new CounterResult();
    
    bool isHit = FDRandom::hitWithRate(subject->creatureData()->calculatedHit() - target->creatureData()->calculatedEv());
    bool isCritical = FDRandom::hitWithRate(GameFormula::commonCriticalAttackRate());
    
    int reducedHp;
    if (isHit)
    {
        Vec2 creaturePos = field->getObjectPosition(subject);
        Ground * ground = field->groundAt(creaturePos.x, creaturePos.y);
        int adjustedAp = subject->creatureData()->calculatedAp() * (100 + ground->getAttackPoint()) / 100;
        
        Vec2 targetPos = field->getObjectPosition(target);
        Ground * groundTarget = field->groundAt(targetPos.x, targetPos.y);
        int adjustedDp = target->creatureData()->calculatedDp() * (100 + groundTarget->getDefendPoint()) / 100;
        
        int attackMax = adjustedAp - adjustedDp;
        int attackMin = 0.9 * attackMax;
        
        reducedHp = FDRandom::valueFromRange(attackMin, attackMax);
        reducedHp = max (0, reducedHp);
        
        if (isCritical) {
            reducedHp *= 2;
        }
        
        // Poisoned
        AttackItemDefinition * weapon = subject->creatureData()->getAttackItem();
        if (weapon != nullptr)
        {
            bool isPoisoned = FDRandom::hitWithRate(weapon->getPoisonRate());
            if (isPoisoned)
            {
                target->creatureData()->statusPoisoned = 1;
            }
        }
    }
    else
    {
        reducedHp = 0;
    }
    
    result->hpBefore = target->creatureData()->hpCurrent;
    result->hpAfter = result->hpBefore - reducedHp;
    target->updateHp(-reducedHp);
    
    result->autorelease();
    
    return result;
}

int GameFormula::calculateExperience(Creature * subject, Creature * target, CounterResult * counterResult)
{
    if (subject == nullptr || target == nullptr || counterResult == nullptr)
    {
        return 0;
    }

    if (subject->getType() != CreatureType_Friend)
    {
        return 0;
    }
    
    int calculatedHp = 0;
    
    if (target->creatureData()->hpCurrent <= 0)
    {
        calculatedHp = target->creatureData()->hpMax;
    }
    else
    {
        calculatedHp = abs(counterResult->hpBefore - target->creatureData()->hpCurrent);
    }
    
    int exp = 0;
    int targetLevel = GameFormula::getCalculatedLevel(target);
    int creatureLevel = GameFormula::getCalculatedLevel(subject);
    
    if (target->getType() == CreatureType_Enemy) {
        
        // Attack, Magic, etc.
        exp = calculatedHp * targetLevel * target->getDefinition()->initialEX / (float)creatureLevel / (float) target->creatureData()->hpMax;
    }
    else
    {
        // Recover Magic
        exp = calculatedHp * 100 * targetLevel * 0.7  / (float) creatureLevel / (float)target->creatureData()->hpMax;
    }
    
    return (int)exp;
}


int GameFormula::commonDoubleAttackRate()
{
    return 5;
}

int GameFormula::commonCriticalAttackRate()
{
    return 5;
}

int GameFormula::getCalculatedLevel(Creature * creature)
{
    int occupation = creature->getDefinition()->occupation;
    switch (occupation) {
        case 112:
        case 113:
        case 122:
        case 123:
        case 132:
        case 133:
        case 142:
        case 143:
        case 152:
        case 153:
        case 155:
        case 156:
        case 162:
        case 163:
        case 171:
        case 999:
            if (creature->getType() == CreatureType_Friend) {
                return creature->creatureData()->level + 30;
            } else {
                return creature->creatureData()->level + 15;
            }
            
        default:
            return creature->creatureData()->level;
    }
}

