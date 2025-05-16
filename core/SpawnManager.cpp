#include "../core/SpawnManager.hpp"
#include "../utils/types.hpp"

SpawnManager::SpawnManager(u8 maxLaneNum, u8 level) :
	laneNumber{ 0, static_cast<u8>(maxLaneNum - 1) }{
	SetEnemyType(level);
}

void SpawnManager::Update(f64 delta, const Map& map, u8 level){
	Spawn(delta, level);

	flippers.Update(delta, map);
	elapsedTime += delta;
}

void SpawnManager::Load(u8 maxLaneNum, u8 level){
	Clear();
	laneNumber.reset();
	laneNumber.param(
		std::uniform_int_distribution<u8>::param_type(0, maxLaneNum - 1)
	);
	SetEnemyType(level);
}

void SpawnManager::Spawn(f64 delta, u8 level){
	if(elapsedTime < spawnInterval)
		return;
	elapsedTime -= spawnInterval;
	
	u8 lane_ = laneNumber(rng);
	u8 enemy_ = enemyType(rng);

	SpawnFlipper(lane_, 1, level);
}

std::vector<Flipper>::iterator SpawnManager::SpawnFlipper(
	u8 laneNum,
	f32 frontProgression,
	u8 level
){
	return flippers.Create(laneNum, frontProgression, .5, .0005, .0015, FORWARD);
}

void SpawnManager::Render(
	SDL_Renderer* ren,
	const Map& map,
	const std::tuple<u8, u8, u8>& flipperColor
){
	flippers.Render(ren, map, flipperColor);
}

void SpawnManager::Clear(){
	flippers.Clear();
	elapsedTime = 0;
}

void SpawnManager::SetEnemyType(u8 level){
	enemyType.reset();
	if(level >= 4)
		enemyType.param(
			std::uniform_int_distribution<u8>::param_type(0, 2)
		);
	else if (level >= 2)
		enemyType.param(
			std::uniform_int_distribution<u8>::param_type(0, 1)
		);
	else
		enemyType.param(
			std::uniform_int_distribution<u8>::param_type(0, 0)
		);
}
