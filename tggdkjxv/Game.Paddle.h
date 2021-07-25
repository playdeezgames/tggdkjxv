#pragma once
#include "Game.Difficulty.h"
#include "Game.PaddleSize.h"
#include <string>
#include <optional>
namespace game::Paddle
{
	void Reset(const game::Difficulty&);

	std::optional<std::string> ReadSpriteName();

	void WritePaddleSize(const std::optional<game::PaddleSize>&);
	std::optional<game::PaddleSize> ReadPaddleSize();
	void DecreasePaddleSize();
	void IncreasePaddleSize();

	void WritePaddlePosition(int);
	void CenterPaddlePosition(int);
	int ReadPaddlePosition();
	int ReadPaddleWidth();

	const int FIELD_WIDTH = 640;

}
