#include "Data.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include "../utils/types.hpp"

Data::Data() : exterior(N_FIGURES, std::vector<Vector2>(N_BANDS_PER_FIGURE)), origin(N_FIGURES){
	std::ifstream file{ DATA_PATH, std::ios::in };
	f32 buf;

	if(!file.is_open())
		std::cout << DATA_PATH << std::endl;

	for(u8 i = 0; i < N_FIGURES; i++){
		file >> buf;
		isContinuous.emplace_back(buf);
	}

	for(u8 i = 0; i < N_FIGURES; i++){
		file >> buf;
		focal.emplace_back(buf);
		// std::cout << buf << std::endl;
	}

	for(u8 i = 0; i < N_FIGURES; i++){
		file >> buf;
		origin[i].setX(buf * (1 - .25) + 188);
	}for(u8 i = 0; i < N_FIGURES; i++){
		file >> buf;
		origin[i].setY(buf * (1 - .25) - 86);
		// std::cout << buf << std::endl;
	}

	for(u8 i = 0; i < N_FIGURES; i++){
		for(u8 j = 0; j < N_BANDS_PER_FIGURE; j++){
			file >> buf;
			exterior[i][j].setX(buf * (1 - .25) + 188);
		}
	}for(u8 i = 0; i < N_FIGURES; i++){
		for(u8 j = 0; j < N_BANDS_PER_FIGURE; j++){
			file >> buf;
			exterior[i][j].setY(buf * (1 - .25) - 86);
		}
	}

	assert(isContinuous.size() == N_FIGURES && focal.size() == N_FIGURES && origin.size() == N_FIGURES && exterior.size() == N_FIGURES);
}
