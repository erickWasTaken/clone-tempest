#include "../core/Flipper.hpp"
#include "../core/Map.hpp"
#include <SDL2/SDL.h>

void Flipper::Render(SDL_Renderer* ren, const Map& map, const std::tuple<u8, u8, u8>& color) const{
	if(!active)
		return;

	const Lane& lane = map.GetLane(laneNum);

	f32 depth = 1 - (1 - map.GetFocal()) * (1 - frontProgression) * (1 - frontProgression);
	f32 height = .2 * map.GetAvgLaneWidth() * (1 - depth);

	Vector2 bottomLeft = lane.GetExterior().first.WeightedMidPointTo(map.GetOrigin(), depth);
	Vector2 bottomRight = lane.GetExterior().second.WeightedMidPointTo(map.GetOrigin(), depth);

	Vector2 negOrthogonal = bottomLeft.vecTo(bottomRight).orthogonalVector().Unit();

	Vector2 topLeft = bottomLeft + negOrthogonal * (-height);
	Vector2 topRight = bottomRight + negOrthogonal * (-height);
	Vector2 midLeft = bottomLeft.WeightedMidPointTo(bottomRight, .2) + negOrthogonal * (-height / 2);
	Vector2 midRight = bottomLeft.WeightedMidPointTo(bottomRight, .8) + negOrthogonal * (-height / 2);

	SDL_SetRenderDrawColor(
		ren, 
		std::get<0>(color),
		std::get<1>(color),
		std::get<2>(color),
		255
	);

	SDL_RenderDrawLineF(
		ren,
		bottomLeft.getX(),
		bottomLeft.getY(),
		topRight.getX(),
		topRight.getY()
	);

	SDL_RenderDrawLineF(
		ren, 
		bottomLeft.getX(),
		bottomLeft.getY(),
		midLeft.getX(),
		midLeft.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		bottomRight.getX(),
		bottomRight.getY(),
		topLeft.getX(),
		topRight.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		bottomRight.getX(),
		bottomRight.getY(),
		midRight.getX(),
		midRight.getY()
	);
}

void Flipper::Update(f64 delta, const Map& map){
	if(!active)
		return;

	switch(flipDirection){
		case LEFT:
			if(map.GetLeftLaneNum(laneNum) == laneNum)
				SetFlipDirection(RIGHT);
			break;
		case RIGHT:
			if(map.GetRightLaneNum(laneNum) == laneNum)
				SetFlipDirection(LEFT);
			break;
		default:
			break;
	}

	if(frontProgression == 0 && laneNum < map.GetSelectedLaneNum())
		SetFlipDirection(RIGHT);
	if(frontProgression == 0 && laneNum > map.GetSelectedLaneNum())
		SetFlipDirection(LEFT);

	SetMovementDirection(flipDirection);
	Move(delta, map);

	if(frontProgression != 0){
		SetMovementDirection(FORWARD);
		Move(delta, map);
	}
}
