#ifndef BULLET_HPP
#define BULLET_HPP

#include "../core/GameObject.hpp"

class Bullet : public GameObject{
public:
    Bullet(){ Deactivate(); };
    ~Bullet() = default;

    void Update(f64 delta, const Map& map)override;
    void Render(SDL_Renderer* ren, const Map& map, const std::tuple<u8, u8, u8>& color) const override;
};

#endif
