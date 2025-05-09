#include "Map.hpp"

Map::Map(const std::vector<Vector2>& exterior_, bool isContinuous_, f32 focal_, Vector2 origin_) :
isContinuous{ isContinuous_ },
focal{ focal_ },
origin{ origin_ }{
	MakeLanes(exterior_);
}

void Map::MakeLanes(const std::vector<Vector2>& exterior_){
	assert(exterior_.size() > 0);
	
	lanes.clear();

	size_t i;
	for(i = 0; i < exterior_.size() - 1; i++){
		lanes.emplace_back(exterior_[i], exterior_[i + 1], origin, focal);
	}if(isContinuous){
		lanes.emplace_back(exterior_[i], exterior_[0], origin, focal);
	}
}

void Map::Load(const std::vector<Vector2>& exterior_, bool isContinuous_, f32 focal_, Vector2 origin_){
	isContinuous = isContinuous_;
	focal = focal_;
	origin = origin_;
	MakeLanes(exterior_);
}

void Map::Render(SDL_Renderer* renderer_, const std::tuple<u8, u8, u8>& color_, const std::tuple<u8, u8, u8>& accentColor_) const{
	for(auto lane : lanes){
		lane.Render(renderer_, color_);
	}
	lanes[selectedLane].Render(renderer_, accentColor_);
}

u8 Map::GetLeftLaneNum(u8 laneNum_) const{
	assert(laneNum_ < lanes.size());
	i32 leftLaneNum = laneNum_ -1;
	if(isContinuous)
		leftLaneNum %= lanes.size();
	else
		leftLaneNum = std::max(leftLaneNum, 0);
	return leftLaneNum;
}

u8 Map::GetRightLaneNum(u8 laneNum_) const{
	assert(laneNum_ < lanes.size());
	i32 rightLaneNum = laneNum_ + 1;
	if(isContinuous)
		rightLaneNum %= lanes.size();
	else
		rightLaneNum = std::min(rightLaneNum, static_cast<int>(lanes.size() -1));
	return rightLaneNum;
}
