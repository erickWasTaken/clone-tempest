#ifndef MAP_HPP
#define MAP_HPP

#include <SDL2/SDL.h>
#include "../utils/Vector2.hpp"
#include "../utils/types.hpp"
#include <vector>
#include "Lane.hpp"
#include <cassert>

class Map{
private:
    bool isContinuous;
    f32 focal;
    Vector2 origin;
    std::vector<Lane> lanes;
    u8 selectedLane = 0;
    f32 avgLaneWidth = 0;

    void MakeLanes(const std::vector<Vector2>& exterior_);

public:
    Map() = default;
    Map(const std::vector<Vector2>& exterior_, bool isContinuous_, f32 focal_, Vector2 origin_);
    ~Map() = default;

    void Render(SDL_Renderer* renderer_, const std::tuple<u8, u8, u8>& color_, const std::tuple<u8, u8, u8>& accentColor_) const;

    void Load(const std::vector<Vector2>& exterior_, bool isContinuous_, f32 focal_, Vector2 origin_);

    inline void Select(u8 laneNum_){
        assert(laneNum_ < lanes.size());
        selectedLane = laneNum_;
    }

    u8 GetLeftLaneNum(u8 laneNum_)const;
    u8 GetRightLaneNum(u8 laneNum_)const;

    inline const Lane& GetLane(u8 laneNum)const{
        assert(laneNum < lanes.size());
        return lanes[laneNum];
    }
    inline f32 GetAvgLaneWidth() const{ return avgLaneWidth; };
};

#endif
