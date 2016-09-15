//
//  MagicScene.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/10/16.
//
//

#ifndef MagicScene_hpp
#define MagicScene_hpp


#include "cocos2d.h"
#include "CounterScene.hpp"
#include "MagicResult.hpp"

class MagicScene : public CounterScene
{
private:
    
    MagicResult * _magicResult;
    void takeDeltaTimeTick(float dt);

    
public:
    
    
    MagicScene(CounterInfo * info, MagicResult * result);
    ~MagicScene();
    
};

#endif /* MagicScene_hpp */
