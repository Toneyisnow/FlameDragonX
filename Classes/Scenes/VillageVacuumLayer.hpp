//
//  VillageVacuumLayer.hpp
//  FlameDragonX
//
//  Created by SuiYi on 10/24/16.
//
//

#ifndef VillageVacuumLayer_hpp
#define VillageVacuumLayer_hpp

#include "cocos2d.h"
#include "VillageLayer.hpp"

class VillageVacuumLayer : public VillageLayer
{
    
    
public:
    
    virtual bool init() override;
    CREATE_FUNC(VillageVacuumLayer);
  
    virtual void loadWithRecord(ChapterRecord * record) override;
    
};

#endif /* VillageVacuumLayer_hpp */
