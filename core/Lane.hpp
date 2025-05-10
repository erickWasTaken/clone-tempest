#ifndef LANE_HPP
#define LANE_HPP

#include <SDL2/SDL.h>
#include "../utils/Vector2.hpp"
#include "../utils/types.hpp"

class Lane{
private:
    //Variables - Lanes
    Vector2 extA, extB, intA, intB;
    Vector2 extCenter, intCenter;
    Vector2 axis;
    Vector2 unitVector;

public:
    Lane() = default;
    Lane(Vector2 extA_, Vector2 extB_, Vector2 origin_, f32 focal_);
    ~Lane() = default;

    inline std::pair<Vector2, Vector2> GetExterior() const{
        return {extA, extB};
    }

    void Render(SDL_Renderer* renderer, const std::tuple<u8, u8, u8> color) const;
};

#endif
