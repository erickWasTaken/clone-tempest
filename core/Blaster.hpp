#ifndef BLASTER_HPP
#define BLASTER_HPP

#include "../core/GameObject.hpp"

class Blaster : public GameObject{
private:
    bool isShooting = false;

public:
    Blaster() = default;
    ~Blaster() override = default;

    void Clear();
    void Update(f64 delta, const Map& map) override;
    void Render(SDL_Renderer* ren, const Map& map, const std::tuple<u8, u8, u8>& color) const override;

    inline void Shoot(){ isShooting = true; };
    inline void StopShooting(){ isShooting = false; };
};

#endif
