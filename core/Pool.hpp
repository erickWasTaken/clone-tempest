#ifndef POOL_HPP
#define POOL_HPP

#include <vector>
#include <algorithm>
#include "../utils/types.hpp"
#include "../core/Map.hpp"
#include "../core/GameObject.hpp"

template<typename obj>
class Pool{
private:
    std::vector<obj> pool;

    inline typename std::vector<obj>::iterator Find(){
        return std::find_if(pool.begin(), pool.end(), [](obj& go){ return !go.IsActive(); });
    }

public:
    Pool() = default;
    explicit Pool(u8 poolSize) : pool(poolSize){}
    ~Pool() = default;

    typename std::vector<obj>::iterator Create(
        u8 laneNum,
        f32 frontProgression,
        f32 lateralProgression,
        f32 frontVelocity,
        f32 lateralVelocity,
        eDirection movementDirection
    );

    void Update(f64 delta, const Map& map){
        for(auto& go : pool)
            go.Update(delta, map);
    }

    void Render(SDL_Renderer* ren, const Map& map, const std::tuple<u8, u8, u8>& color) const{
        for(auto& go : pool)
            go.Render(ren, map, color);
    }

    inline void Clear(){
        for(auto& go : pool)
            go.Deactivate();
    }

    inline std::vector<obj>& GetPool(){ return pool; };
};

template <typename obj>
typename std::vector<obj>::iterator 
Pool<obj>::Create(
    u8 laneNum,
    f32 frontProgression,
    f32 lateralProgression,
    f32 frontVelocity,
    f32 lateralVelocity,
    eDirection movementDirection
){
    auto go = Find();
    if(go != pool.end())
        (*go).Activate(
        laneNum,
        frontProgression,
        lateralProgression,
        frontVelocity,
        lateralVelocity,
        movementDirection
    );
    return go;
}

#endif
