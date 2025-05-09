#include <iostream>
#include <SDL2/SDL.h>
#include "./utils/types.hpp"
#include "./core/Map.hpp"
#include "./core/Data.hpp"

//Variables - Blaster
enum eDirection{
	NONE,
	LEFT,
	RIGHT,
	FORWARD,
	BACKWARD
};

//Variables - blaster
u8 bandNum = 0;
f32 frontProgression = 0;
f32 lateralProgression = 0;
f32 frontVelocity = .0005;
f32 lateralVelocity = .02;
enum eDirection movementDirection = NONE;

bool isShooting = false;

//Variables - Map
Data levelData;
u8 currentFigure = 0;

Map map;

//Variables - Game
u16 wWidth = 960;
u16 wHeight = 540;

bool isRunning = false;

SDL_Window* win;
SDL_Renderer* ren;

//Functions - Declaration
void ProcessEvent(const SDL_Event& event);
void Shoot();
void StopShooting();
void SetMovementDirection(eDirection direction);
void Move(f64 delta, const Map& map);

//Functions - Temp
void CreateWindow();
void RenderScene();

//Functions - Definintion
void ProcessEvent(const SDL_Event& event){
	switch(event.type){
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_LEFT:
					// SetMovementDirection(LEFT);
					bandNum = map.GetLeftLaneNum(bandNum);
					map.Select(bandNum);
					break;
				case SDLK_RIGHT:
					// SetMovementDirection(RIGHT);
					bandNum = map.GetRightLaneNum(bandNum);
					map.Select(bandNum);
					std::cout << bandNum << std::endl;
					break;
				case SDLK_SPACE:
					// Shoot();
					break;
				case SDLK_ESCAPE:
					isRunning = false;
					break;
			}
			break;

		case SDL_KEYUP:
			switch(event.key.keysym.sym){
				case SDLK_LEFT:
				case SDLK_RIGHT:
					SetMovementDirection(NONE);
					break;
				case SDLK_SPACE:
					StopShooting();
					break;
			}

		default:
			break;
	}	
}

inline void Shoot(){ isShooting = true; };
inline void StopShooting(){ isShooting = false; };
void SetMovementDirection(eDirection direction){ movementDirection = direction; };

void Move(f64 delta, const Map& map){
	switch(movementDirection){
		case LEFT:
			break;
		case RIGHT:
			break;
		case FORWARD:
			break;
		case BACKWARD:
			break;
		default:
			break;
	}
}

int main(){
	std::cout << "Main.cpp launched" << std::endl;

	CreateWindow();
	map.Load(
		levelData.getExterior()[0], 
		levelData.getIsContinuous()[0], 
		levelData.getFocal()[0],
		levelData.getOrigin()[0]
	);

	f64 delta = 0;
	isRunning = true;

	while(isRunning){
		SDL_Event event;
		SDL_PollEvent(&event);
		ProcessEvent(event);
		RenderScene();
	}

	// std::cout << levelData.getExterior()[0][0].getX() << std::endl;
	return 0;
}

void RenderScene(){
	//Clear background with color: Black
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	//Draw objects to be rendered to the buffer
	map.Render(ren, {0, 255, 255}, {255, 0, 255});

	//Actually renders to the screen
	SDL_RenderPresent(ren);
}

void CreateWindow(){
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow(
		static_cast<const std::string&>("ARASHI - Tempest clone").c_str(),
		480,
		270,
		wWidth,
		wHeight,
		0
	);
	ren = SDL_CreateRenderer(win, -1, 0);
	std::cout << "renderer created" << std::endl;
}
