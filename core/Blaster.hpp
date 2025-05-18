#ifndef BLASTER_HPP
#define BLASTER_HPP

#include "../core/GameObject.hpp"
#include "../core/Bullet.hpp"
#include "../core/Pool.hpp"

class Blaster : public GameObject{
private:
    Pool<Bullet> bullets {16};
    const f64 shotInterval = 50;
    f64 elapsedTime = 0;
    bool isShooting = false;

public:
    Blaster() = default; 
    ~Blaster() override = default;

    void Clear();
    void Update(f64 delta, const Map& map) override;
    void Render(SDL_Renderer* ren, const Map& map, const std::tuple<u8, u8, u8>& color) const override;

    inline void Shoot(){ isShooting = true; };
    inline void StopShooting(){ isShooting = false; };
    inline std::vector<Bullet>& GetBullets() { return bullets.GetPool(); };
};

#endif
