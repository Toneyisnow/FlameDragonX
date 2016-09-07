//
//  PointMap.cpp
//  FlameDragonX
//
//  Created by SuiYi on 9/6/16.
//
//

#include "PointMap.hpp"


/*
template<class V>
PointMap<V>::PointMap()
{
    
}

template<class V>
PointMap<V>::~PointMap()
{
    for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
    {
        iter->second->release();
    }
    
    _data.clear();
}

template<class V>
void PointMap<V>::insert(const Vec2 position, V object)
{
    cocos2d::Map<V, V> test;
    
    
    CCASSERT(object != nullptr, "Object is nullptr!");
    object->retain();
    
    _data.insert(std::make_pair(position, object));
    
    // _data.insert(std::map<Vec2, V, VecComparer>::value_type(position, object));
    
}

template<class V>
bool PointMap<V>::containsKey(Vec2 position)
{
    auto vc = _data.find(position);
    return (vc != _data.end());
        
}

template<class V>
V PointMap<V>::at(Vec2 position)
{
    auto vc = _data.find(position);
    if (vc != _data.end())
    {
        return vc->second;
    }
}

*/