#include "../core/GameScene.hpp"
#include "../utils/types.hpp"
#include "../ui/Pen.hpp"
#include <iostream>
#include <SDL2/SDL.h>

GameScene::GameScene(u8 level) :
	currentFigure{ static_cast<u8>(level % Data::N_FIGURES) },
	map{
		levelData.getExterior()[level],
		levelData.getIsContinuous()[level],
		levelData.getFocal()[level],
		levelData.getOrigin()[level]
	}{

}

void GameScene::Update(f64 delta){
	player.Update(delta, map);
	spawnManager.Update(delta, map, GetCurrentLevelNum());
	map.Select(player.getLaneNum());

	HandleCollisions(spawnManager.GetFlippers(), 200);

	if(player.GetScore() > GetCurrentLevelScoreCap()){
		LoadNextLevel();
	} 
}

void GameScene::LoadNextLevel(){
	currentFigure = (currentFigure + 1) % Data::N_FIGURES;

	if(currentFigure == 0)
		currentCycle ++;

	map.Load(
		levelData.getExterior()[currentFigure],
		levelData.getIsContinuous()[currentFigure],
		levelData.getFocal()[currentFigure],
		levelData.getOrigin()[currentFigure]
	);

	spawnManager.Load(map.Size(), GetCurrentLevelNum());
	player.Clear();
}

void GameScene::ProcessEvent(const SDL_Event& event){
	switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_LEFT:
					player.SetMovementDirection(LEFT);
					break;
					
				case SDLK_RIGHT:
					player.SetMovementDirection(RIGHT);
					break;

				case SDLK_SPACE:
					player.Shoot();
					break;
			}
			break;

		case SDL_KEYUP:
			switch(event.key.keysym.sym){
				case SDLK_LEFT:
				case SDLK_RIGHT:
					player.SetMovementDirection(NONE);
					break;
				case SDLK_SPACE:
					player.StopShooting();
					break;
			}

		default:
			break;
	}

}

void GameScene::Render(SDL_Renderer* ren){
	map.Render(ren, {0, 0, 255}, {255, 255, 0});
	spawnManager.Render(ren,map, {255, 0, 0});
	player.Render(ren, map, {255, 255, 0});

	Pen::DrawString(
		ren,
		20,
		46,
		std::to_string(player.GetScore()),
		{255, 255, 255}
	);
}

template <class obj, typename Func>
void GameScene::HandleCollisions(std::vector<obj>& enemies, u32 score, Func& behaviour){
	for(auto& enemy : enemies){
		if(!enemy.IsActive())
			continue;

		if(enemy.IsColliding(player)){
			enemy.Deactivate();
			player.Hit();
			spawnManager.Clear();
		}

		for(auto& bullet : player.GetBullets()){
			if(!bullet.IsActive())
				continue;

			if(bullet.IsColliding(enemy)){
				bullet.Deactivate();
				enemy.Hit();
				player.AddScore(score);
				std::cout << player.GetScore() << std::endl;
				behaviour(enemy);
			}
		}
	}
}
