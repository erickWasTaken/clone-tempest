#include "../core/Blaster.hpp"
#include "../utils/Vector2.hpp"

void Blaster::Clear(){
	laneNum = 0;
	lateralProgression = 0;
	movementDirection = NONE;
	isShooting = false;
}

void Blaster::Update(f64 delta, const Map& map){
	if(!active)
		return;

	Move(delta, map);
}

void Blaster::Render(SDL_Renderer* ren, const Map& map, const std::tuple<u8, u8, u8>& color)const{
	const Lane& lane = map.GetLane(laneNum);
	auto exterior = lane.GetExterior();

	Vector2 unit = exterior.first.vecTo(exterior.second).orthogonalVector().Unit();
	Vector2 innerLeft = exterior.first.WeightedMidPointTo(exterior.second, .1);
	Vector2 innerRight = exterior.first.WeightedMidPointTo(exterior.second, .9);

	auto height = map.GetAvgLaneWidth() * .3;
	auto weight = lateralProgression;

	if(lateralProgression > .9)
		weight = .9;
	else if(lateralProgression < .1)
		weight = .1;

	// vector from the first towards the second with length equal to weight + vector outwards the origin with half of height as length
	Vector2 innerTop = exterior.first.WeightedMidPointTo(exterior.second, weight) + (unit * (-height / 2));
	// the same first vector + vector outwards the origin with all the height value as length
	Vector2 outerTop = exterior.first.WeightedMidPointTo(exterior.second, weight) + (unit * (-height));

	Vector2 clawLeft = exterior.first.WeightedMidPointTo(exterior.second, .4) + (unit * (height / 2));
	Vector2 clawRight = exterior.first.WeightedMidPointTo(exterior.second, .6) + (unit * (height / 2));

	SDL_SetRenderDrawColor(
		ren,
		std::get<0>(color),
		std::get<1>(color),
		std::get<2>(color),
		255
	);

	SDL_RenderDrawLineF(
		ren,
		exterior.first.getX(),
		exterior.first.getY(),
		clawLeft.getX(),
		clawLeft.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		exterior.second.getX(),
		exterior.second.getY(),
		clawRight.getX(),
		clawRight.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		exterior.first.getX(),
		exterior.first.getY(),
		outerTop.getX(),
		outerTop.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		exterior.second.getX(),
		exterior.second.getY(),
		outerTop.getX(),
		outerTop.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		innerLeft.getX(), 
		innerLeft.getY(),
		innerTop.getX(),
		innerTop.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		innerRight.getX(),
		innerRight.getY(),
		innerTop.getX(),
		innerTop.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		clawLeft.getX(),
		clawLeft.getY(),
		innerLeft.getX(),
		innerLeft.getY()
	);

	SDL_RenderDrawLineF(
		ren, 
		clawRight.getX(),
		clawRight.getY(),
		innerRight.getX(),
		innerRight.getY()
	);
}
