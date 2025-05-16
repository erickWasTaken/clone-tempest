#ifndef GO_HPP
#define GO_HPP

#include "../utils/types.hpp"
#include "../core/Map.hpp"
#include <SDL2/SDL.h>

enum eDirection{
    NONE,
    LEFT,
    RIGHT,
    FORWARD,
    BACKWARD
};

class GameObject{
protected:
    bool active = true;

    u8 laneNum = 0;
    f32 frontProgression = 0;
    f32 lateralProgression = 0;
    f32 frontVelocity = .0005;
    f32 lateralVelocity = .02;
    enum eDirection movementDirection = NONE;

    virtual void Move(f64 delta, const Map& map);

public:
    GameObject() = default;
    virtual ~GameObject() = default;

    void Activate(
        u8 landNum,
        f32 frontProgression,
        f32 lateralProgression,
        f32 frontVelocity,
        f32 lateralVelocity,
        eDirection movingDirection
    );

    virtual void Update(f64 delta, const Map& map) = 0;
    virtual void Render(SDL_Renderer* ren, const Map& map, const std::tuple<u8, u8, u8>& color) const = 0;
    inline virtual void Hit(){ Deactivate(); }; 

    inline void SetMovementDirection(eDirection direction){
        movementDirection = direction;
    };
    
    inline bool IsActive(){ return active; };
    bool IsColliding(const GameObject& go) const;
    inline void Deactivate(){ active = false; };
    inline u8 getLaneNum(){ return laneNum; };
};

#endif
