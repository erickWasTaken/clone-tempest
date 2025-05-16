#ifndef FLIPPER_HPP
#define FLIPPER_HPP

#include "../core/GameObject.hpp"
#include "../core/Map.hpp"

class Flipper : public GameObject{
private:
    eDirection flipDirection = RIGHT;

public:
    Flipper(){ Deactivate(); };
    Flipper(const Flipper& flipper) = default;
    ~Flipper() override = default;
    
    void Render(SDL_Renderer* ren, const Map& map, const std::tuple<u8, u8, u8>& color) const override;
    void Update(f64 delta, const Map& map) override;

    inline void SetFlipDirection(eDirection dir){ flipDirection = dir; };
    inline eDirection GetFlipDirection(){ return flipDirection; };
};

#endif
