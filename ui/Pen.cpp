#include "Pen.hpp"

void Pen::DrawEdge(
	SDL_Renderer* ren,
	const f32 x1,
	const f32 y1,
	const f32 x2,
	const f32 y2,
	const i32 xoffset,
	const i32 yoffset,
	const std::tuple<u8, u8, u8>& color
){
	SDL_SetRenderDrawColor(
		ren,
		std::get<0>(color),
		std::get<1>(color),
		std::get<2>(color),
		255
	);

	SDL_RenderDrawLineF(
		ren,
		x1 + xoffset, 
		-y1 + yoffset, 
		x2 + xoffset, 
		-y2 + yoffset
	);
}

void Pen::DrawString(
	SDL_Renderer* ren,
	i32 xpos,
	i32 ypos,
	std::string const& s,
	const std::tuple<u8, u8, u8>& color
){
	for(auto& ch : s){
		xpos += Pen::DrawCharacter(ren, ch, xpos, ypos, 1, color) + Pen::spaceSize;
	}
}

i32 Pen::DrawCharacter(
	SDL_Renderer* ren,
	const u8 ch,
	const i32 xoffset,
	const i32 yoffset,
	const f32 multiplier,
	const std::tuple<u8, u8, u8>& color
){
	i32 charIndex = ASCIIindex(ch);
	if(charIndex < 0 || charIndex >= 95){
		// charIndex = unknownCharIndex;
		return charIndex;
	}

	i32 i = 2;
	while(( i + 3 ) < 112){
		if(Pen::hersheyTable[charIndex][i] == -1 || Pen::hersheyTable[charIndex][i + 2] == -1){
			i += 2;
		}else{
			DrawEdge(
				ren,
				multiplier * Pen::hersheyTable[charIndex][i],
				multiplier * Pen::hersheyTable[charIndex][i + 1],
				multiplier * Pen::hersheyTable[charIndex][i + 2],
				multiplier * Pen::hersheyTable[charIndex][i + 3],
				xoffset,
				yoffset,
				color
			);
			i += 2;
		}
	}

	return multiplier * Pen::hersheyTable[charIndex][1];
}

i32 Pen::ASCIIindex(u8 ch){
	return static_cast<i32>(ch - 32);
}
