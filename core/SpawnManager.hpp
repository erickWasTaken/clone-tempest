#ifndef SPAWN_MNG_HPP
#define SPAWN_MNG_HPP

#include "../utils/types.hpp"
#include <random>
#include "../core/Pool.hpp"
#include "../core/Flipper.hpp"
#include "../core/GameObject.hpp"

class SpawnManager{
    static const u8 maxFlippers = 15;

    static constexpr f64 spawnInterval = 2000;
    f64 elapsedTime = 0;

    std::random_device rd;
    std::default_random_engine rng{ rd() };

    std::uniform_int_distribution<u8> enemyType{ 0, 1 };
    std::uniform_int_distribution<u8> laneNumber{ 0, 14 };
    
    Pool<Flipper> flippers{ maxFlippers };

    void SetEnemyType(u8 level);

public:
    SpawnManager() = default;
    SpawnManager(u8 maxLaneNum, u8 level);
    ~SpawnManager() = default;

    void Update(f64 delta, const Map& map, u8 level);
    void Load(u8 maxLaneNum, u8 level);
    void Spawn(f64 delta, u8 level);
    std::vector<Flipper>::iterator SpawnFlipper(
        u8 laneNum,
        f32 frontProgression,
        u8 level
    );
    std::vector<Flipper>::iterator SpawnFlipper(
        u8 laneNum,
        f32 frontProgression,
        u8 level,
        eDirection direction
    );
    void Render(
        SDL_Renderer* ren, 
        const Map& map, 
        const std::tuple<u8, u8, u8>& flipperColor
    );
    void Clear();

    inline std::vector<Flipper>& GetFlippers(){ return flippers.GetPool(); };
};

#endif
