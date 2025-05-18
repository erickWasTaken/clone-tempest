#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "../core/Data.hpp"
#include "../utils/types.hpp"
#include "../core/Map.hpp"
#include "../core/Blaster.hpp"
#include "../core/SpawnManager.hpp"
#include "../core/Bullet.hpp"

class GameScene{
private:
    Data levelData;
    Map map;
    u8 currentFigure;

    Blaster player;
    SpawnManager spawnManager;

public:
    GameScene(u8 level);
    GameScene() = delete;

    void Render(SDL_Renderer* ren);
    void ProcessEvent(const SDL_Event& event);
    void Update(f64 delta);
    inline u8 GetCurrentLevelNum(){ return currentFigure; };
};

#endif
