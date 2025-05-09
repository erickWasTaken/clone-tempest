#include "Lane.hpp"
#include <SDL2/SDL.h>
#include <iostream>

Lane::Lane(Vector2 extA_, Vector2 extB_, Vector2 origin_, f32 focal_) :
	extA{ extA_ },
	extB{ extB_ },
	intA{ origin_.WeightedMidPointTo(extA_, focal_) },
	intB{ origin_.WeightedMidPointTo(extB_, focal_) },
	extCenter{ extA_.WeightedMidPointTo(extB_, .5) },
	intCenter{ intA.WeightedMidPointTo(intB, .5) },
	axis{ extCenter.vecTo(origin_) },
	unitVector{ axis.Unit() } 
{}

void Lane::Render(SDL_Renderer* renderer, const std::tuple<u8, u8, u8> color) const{
	SDL_SetRenderDrawColor(
		renderer,
		std::get<0>(color),
		std::get<1>(color),
		std::get<2>(color),
		255
	);
	
	// std::cout << "red: " << std::get<0>(color) << "green: " << std::get<1>(color) << "blue: " << std::get<2>(color) << std::endl;

	SDL_RenderDrawLineF(renderer, extA.getX(), extA.getY(), extB.getX(), extB.getY());
	SDL_RenderDrawLineF(renderer, extB.getX(), extB.getY(), intB.getX(), intB.getY());
	SDL_RenderDrawLineF(renderer, intB.getX(), intB.getY(), intA.getX(), intA.getY());
	SDL_RenderDrawLineF(renderer, intA.getX(), intA.getY(), extA.getX(), extA.getY());
}
