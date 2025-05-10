#include "../utils/Timer.hpp"
#include <SDL2/SDL.h>
#include "../utils/types.hpp"

Timer::Timer(u32 maxMS_) : maxMS{ maxMS_ }{}

void Timer::Start(){
	start = SDL_GetTicks64();
}

f64 Timer::Stop(){
	stop = SDL_GetTicks64();
	return stop - start;
}

f64 Timer::Delta(){
	stop = SDL_GetTicks64();

	auto del = maxMS - (stop - start);
	SDL_Delay(del);
	return this->Stop();
}
