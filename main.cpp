#include <iostream>
#include <SDL2/SDL.h>
#include "./utils/types.hpp"
#include "./core/Map.hpp"
#include "./core/Data.hpp"
#include "./core/GameScene.hpp"
#include "./utils/Timer.hpp"

bool isShooting = false;

//Variables - Map
Data levelData;
u8 currentFigure = 0;

Map map;

//Variables - Game
u16 wWidth = 960;
u16 wHeight = 540;

constexpr u32 maxMS_ = 1000.f / 30.f;
Timer timer(maxMS_);
bool isRunning = false;

SDL_Window* win;
SDL_Renderer* ren;

GameScene scene(0);

//Functions - Declaration
void Shoot();
void StopShooting();

//Functions - Temp
void CreateWindow();
void RenderScene();

//Functions - Definintion

inline void Shoot(){ isShooting = true; };
inline void StopShooting(){ isShooting = false; };

int main(){
	std::cout << "Main.cpp launched" << std::endl;

	CreateWindow();

	f64 delta = 0;
	isRunning = true;

	while(isRunning){
		timer.Start();
		SDL_Event event;
		SDL_PollEvent(&event);

		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						isRunning = false;
						break;
				}
		}
		scene.ProcessEvent(event);
		scene.Update(delta);

		RenderScene();
		delta = timer.Delta();
	}

	return 0;
}

void RenderScene(){
	//Clear background with color: Black
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	//Draw objects to be rendered to the buffer
	scene.Render(ren);

	//Actually renders to the screen
	SDL_RenderPresent(ren);
}

void CreateWindow(){
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow(
		static_cast<const std::string&>("ARASHI - Tempest clone").c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		wWidth,
		wHeight,
		0
	);
	ren = SDL_CreateRenderer(win, -1, 0);
	std::cout << "renderer created" << std::endl;
}
