//
//  PointMap.hpp
//  FlameDragonX
//
//  Created by SuiYi on 9/6/16.
//
//

#ifndef PointMap_hpp
#define PointMap_hpp

#include "cocos2d.h"

USING_NS_CC;

class VecComparer
{
public:
    bool operator()(const Vec2& A, const Vec2& B) const
    {
        return (A.x < B.x || (A.x == B.x && A.y < B.y));
    }
};



template<class V>
class PointMap : public cocos2d::Ref
{
private:
    
    std::map<Vec2, V, VecComparer> _data;
    
public:
    
    PointMap<V>()
    {
        
    }
    
    ~PointMap()
    {
        
    }
    
    void insert(Vec2 position, V object)
    {
        CCASSERT(object != nullptr, "Object is nullptr!");
        object->retain();
        
        _data.insert(std::make_pair(position, object));
    }
    
    bool containsKey(Vec2 position)
    {
        auto vc = _data.find(position);
        return (vc != _data.end());
    }
    
    std::vector<Vec2> keys()
    {
        std::vector<Vec2> keys;
        
        if (!_data.empty())
        {
            keys.reserve(_data.size());
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                keys.push_back(iter->first);
            }
        }
        return keys;
    }
    
    V at(Vec2 position)
    {
         cocos2d::Map<V, V> t;
        
        auto vc = _data.find(position);
        if (vc != _data.end())
        {
            return vc->second;
        }
        
        return nullptr;
    }
    
    void eraseObject(Vec2 position)
    {
        auto iter = _data.find(position);
        if (iter != _data.end())
        {
            iter->second->release();
            _data.erase(iter);
        }
    }
    
};


#endif /* PointMap_hpp */
