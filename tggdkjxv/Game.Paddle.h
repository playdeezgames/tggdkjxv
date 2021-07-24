#pragma once
#include "Game.Difficulty.h"
#include "Game.PaddleSize.h"
namespace game::Paddle
{
	void Reset(const game::Difficulty&);

	void WritePaddleSize(const game::PaddleSize&);
	game::PaddleSize ReadPaddleSize();

	void WritePaddlePosition(int);
	int ReadPaddlePosition();
}
