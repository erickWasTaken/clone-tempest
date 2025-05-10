#include "../core/GameObject.hpp"

void GameObject::Move(f64 delta, const Map& map){
	switch(movementDirection){
		case LEFT:
			lateralProgression = std::max(0.0, lateralProgression - delta * lateralVelocity);
			if(lateralProgression == 0 && map.GetLeftLaneNum(laneNum) != laneNum){
				laneNum = map.GetLeftLaneNum(laneNum);
				lateralProgression = 1;
			}
			break;

		case RIGHT:
			lateralProgression = std::min(1.0, lateralProgression + delta * lateralVelocity);
			if(lateralProgression == 1 && map.GetRightLaneNum(laneNum) != laneNum){
				laneNum = map.GetRightLaneNum(laneNum);
				lateralProgression = 0;
			}
			break;

		case FORWARD:
			frontProgression = std::max(0.0, frontProgression - delta * frontVelocity);
			break;

		case BACKWARD:
			frontProgression = std::min(1.0, frontProgression + delta * frontVelocity);
			break;

		default:
			break;
	}
}

void GameObject::Activate(
	u8 laneNum_,
	f32 frontProgression_,
	f32 lateralProgression_,
	f32 frontVelocity_,
	f32 lateralVelocity_,
	eDirection movingDirection_
){
	active = true;
	laneNum = laneNum_;
	frontProgression = frontProgression_;
	lateralProgression = lateralProgression_;
	frontVelocity = frontVelocity_;
	lateralVelocity = lateralVelocity_;
	movementDirection = movingDirection_;
}

bool GameObject::IsColliding(const GameObject& go) const{
	return laneNum == go.laneNum && std::abs(go.frontProgression - frontProgression) < 30 * (frontVelocity + go.frontVelocity);
}
