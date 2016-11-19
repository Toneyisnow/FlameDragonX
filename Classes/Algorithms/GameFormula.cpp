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
#include "DataStore.hpp"

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

MagicResult * GameFormula::dealWithMagic(BattleField * field, Creature * subject, Vector<Creature * > &targets, int magicId)
{
    MagicResult * result = new MagicResult(subject, magicId, targets);
    MagicDefinition * magic = DataStore::getInstance()->getMagicDefinition(magicId);

    if (magic == nullptr) {
        result->autorelease();
        return result;
    }
    
    int totalExp = 0;
    for (Creature * target : targets) {
        CounterResult * singleResult = GameFormula::singleMagic(field, subject, target, magic);
        result->appendResult(singleResult);
        
        if (magic->getType() == MagicType_Attack || magic->getType() == MagicType_Recover)
        {
            totalExp += GameFormula::calculateExperience(subject, target, singleResult);
        }
        else
        {
            totalExp += GameFormula::calculateMagicExperience(subject, target, magic);
        }
    }
    
    subject->setLastGainedExperience(totalExp);
    
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

CounterResult * GameFormula::singleMagic(BattleField * field, Creature * subject, Creature * target, MagicDefinition * magic)
{
    bool isHit = FDRandom::hitWithRate(magic->hittingRate());
    int reduceHp = 0;
    
    if (isHit)
    {
        OccupationDefinition * occupation = DataStore::getInstance()->getOccupationDefinition(target->getDefinition()->occupation);
        float defenseRate = 1.0f;
        if (occupation != nullptr) {
            defenseRate = (float)(100 - occupation->magicDefenseRate()) / 100.0;
        }
        
        switch (magic->getType()) {
            case MagicType_Attack:
                reduceHp = FDRandom::valueFromRange(magic->getQuantityRange()->getMin(), magic->getQuantityRange()->getMax() + (int)(magic->apInvolvedRate() * subject->creatureData()->ap / 100));
                reduceHp = (int)(reduceHp * defenseRate);
                reduceHp = MAX(reduceHp, 0);
                break;
                
            case MagicType_Recover:
                reduceHp = -FDRandom::valueFromRange(magic->getQuantityRange()->getMin(), magic->getQuantityRange()->getMax());
                reduceHp = MAX(reduceHp, 0);
                reduceHp = MIN(reduceHp, target->creatureData()->hpMax - target->creatureData()->hpCurrent);
                break;
                
            case MagicType_Offensive:
                magic->takeOffensiveEffect(target);
                break;
            case MagicType_Defensive:
                magic->takeDefensiveEffect(target);
                break;
                
            default:
                break;
        }
    }

    CounterResult * result = new CounterResult();
    result->hpBefore = target->creatureData()->hpCurrent;
    result->hpAfter = target->creatureData()->hpCurrent - reduceHp;
    target->updateHp(-reduceHp);
    
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

int GameFormula::calculateMagicExperience(Creature * subject, Creature * target, MagicDefinition * magic)
{
    if (subject == nullptr || target == nullptr || magic == nullptr) {
        return 0;
    }
    
    int targetLevel = GameFormula::getCalculatedLevel(target);
    int subjectLevel = GameFormula::getCalculatedLevel(subject);
    float exp = magic->baseExperience() * targetLevel / subjectLevel;
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

int GameFormula::getDefaultTransferFee()
{
    return 300;
}

int GameFormula::getMoneyNeededForRevive(CreatureRecord * record)
{
    if (record == nullptr) {
        return 0;
    }
    
    Creature * creature = new Creature(record);
    int money = 100 * GameFormula::getCalculatedLevel(creature);
    creature->release();
    
    return money;
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

void GameFormula::actionedByEnhanceAp(Creature * target)
{
    if (target == nullptr) {
        return;
    }
    
    int roundCount = FDRandom::valueFromRange(2, 4);
    target->creatureData()->statusEnhanceAp = roundCount;
}

void GameFormula::actionedByEnhanceDp(Creature * target)
{
    if (target == nullptr) {
        return;
    }
    
    int roundCount = FDRandom::valueFromRange(2, 4);
    target->creatureData()->statusEnhanceDp = roundCount;
}

void GameFormula::actionedByEnhanceDx(Creature * target)
{
    if (target == nullptr) {
        return;
    }
    
    int roundCount = FDRandom::valueFromRange(2, 4);
    target->creatureData()->statusEnhanceDx = roundCount;
}

void GameFormula::actionedByPoison(Creature * target)
{
    if (target == nullptr) {
        return;
    }
    
    int roundCount = FDRandom::valueFromRange(10, 15);
    target->creatureData()->statusPoisoned = roundCount;
}

void GameFormula::actionedByProhibited(Creature * target)
{
    if (target == nullptr) {
        return;
    }
    
    int roundCount = FDRandom::valueFromRange(2, 4);
    target->creatureData()->statusProhibited = roundCount;
}

void GameFormula::actionedByFrozen(Creature * target)
{
    if (target == nullptr) {
        return;
    }
    
    int roundCount = FDRandom::valueFromRange(2, 4);
    target->creatureData()->statusFrozen = roundCount;
}

void GameFormula::waiveTurnRecover(Creature * target)
{
    int hpRecover = FDRandom::valueFromRange(target->creatureData()->hpMax * 0.15f, target->creatureData()->hpMax * 0.25f);
    target->creatureData()->updateHp(hpRecover);
}

