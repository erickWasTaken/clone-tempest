#include "../core/Bullet.hpp"

void Bullet::Update(f64 delta, const Map& map){
	if(!active)
		return;

	if(movementDirection == FORWARD && frontProgression == 0 || movementDirection == BACKWARD && frontProgression == 1)
		Deactivate();

	Move(delta, map);
}

void Bullet::Render(SDL_Renderer* ren, const Map& map, const std::tuple<u8, u8, u8>& color)const{
	if(!active)
		return;

	f32 depth = (1 - (1 - map.GetFocal()) * (1 - frontProgression) * (1 - frontProgression)) - map.GetFocal();
	f32 size = .1 * map.GetAvgLaneWidth() * (1 - depth);

	const Lane& lane = map.GetLane(laneNum);
	Vector2 extCenter = lane.GetExterior().first.WeightedMidPointTo(lane.GetExterior().second, .5);
	Vector2 axis = extCenter.vecTo(map.GetOrigin());
	
	Vector2 position = axis * depth;
	Vector2 orthogonal = axis.Unit().orthogonalVector();

	Vector2 left = extCenter + (orthogonal * (size / 2)) + position;
	Vector2 right = extCenter + (orthogonal * (-size / 2)) + position;
	Vector2 top = extCenter + (axis.Unit() * (size / 2)) + position;
	Vector2 bottom = extCenter + (axis.Unit() * (-size / 2)) + position;

	SDL_SetRenderDrawColor(
		ren,
		std::get<0>(color),
		std::get<1>(color),
		std::get<2>(color),
		255
	);

	SDL_RenderDrawLineF(
		ren,
		left.getX(),
		left.getY(),
		top.getX(),
		top.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		top.getX(),
		top.getY(),
		right.getX(),
		right.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		right.getX(),
		right.getY(),
		bottom.getX(),
		bottom.getY()
	);

	SDL_RenderDrawLineF(
		ren,
		bottom.getX(),
		bottom.getY(),
		left.getX(),
		left.getY()
	);
}
