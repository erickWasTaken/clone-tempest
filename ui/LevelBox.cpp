#include "LevelBox.hpp"

LevelBox::LevelBox(u8 level, i32 x, i32 y, i32 w, i32 h) : 
	UIElement(x, y, w, h), 
	levelNum{ level }{}

LevelBox::~LevelBox(){}

void LevelBox::Update(){}

void LevelBox::Render(SDL_Renderer* ren) const{
	Render(ren, false);
}

void LevelBox::Render(SDL_Renderer* ren, bool selected) const{
	if(selected){
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderDrawRect(ren, &rect);
	}
}
