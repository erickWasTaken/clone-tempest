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
    u8 currentFigure = 0;
    u8 currentCycle = 0;

    Blaster player;
    SpawnManager spawnManager;

public:
    GameScene(u8 level);
    GameScene() = delete;

    void Render(SDL_Renderer* ren);
    void ProcessEvent(const SDL_Event& event);
    void Update(f64 delta);
    inline u8 GetCurrentLevelNum(){ return currentFigure; };

    template<class obj>
    inline void HandleCollisions(std::vector<obj>& enemies, u32 score){
        auto f = [](obj& enemy) { (void)enemy; };
        HandleCollisions(enemies, score, f);
    }

    inline static u32 GetLevelScoreCap(u8 cycle, u8 figure){
        return 1000 + (cycle + 1) * std::pow(figure + 1, 2) * 600 + cycle * Data::N_FIGURES * Data::N_FIGURES * 600;
    }

    inline u32 GetCurrentLevelScoreCap() const{
        return GetLevelScoreCap(currentCycle, currentFigure);
    }

    void LoadNextLevel();
    
    template<class obj, typename Func>
    void HandleCollisions(std::vector<obj>& enemies, u32 score, Func& behaviour);
};
#endif
