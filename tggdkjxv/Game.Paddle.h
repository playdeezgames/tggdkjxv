#pragma once
#include "Game.Difficulty.h"
#include "Game.PaddleSize.h"
#include <string>
namespace game::Paddle
{
	void Reset(const game::Difficulty&);

	std::string ReadSpriteName();

	void WritePaddleSize(const game::PaddleSize&);
	game::PaddleSize ReadPaddleSize();

	void WritePaddlePosition(int);
	void CenterPaddlePosition(int);
	int ReadPaddlePosition();
}
