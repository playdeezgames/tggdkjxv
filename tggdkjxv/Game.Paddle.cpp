#include "Game.Paddle.h"
#include <map>
namespace game::Paddle
{
	const game::PaddleSize PADDLE_SIZE_INITIAL = game::PaddleSize::NORMAL;
	const int POSITION_INITIAL = 0;
	const int FIELD_WIDTH = 640;
	const std::map<game::PaddleSize, int> paddleWidths =
	{
		{game::PaddleSize::NORMAL, 64 },
		{game::PaddleSize::SMALL, 48 },
		{game::PaddleSize::SMALLER, 32 },
		{game::PaddleSize::SMALLEST, 16 }
	};
	const std::map<game::PaddleSize, std::string> paddleSprites =
	{
		{game::PaddleSize::NORMAL, "Paddle64" },
		{game::PaddleSize::SMALL, "Paddle48" },
		{game::PaddleSize::SMALLER, "Paddle32" },
		{game::PaddleSize::SMALLEST, "Paddle16" }
	};

	static PaddleSize paddleSize;
	static int paddlePosition;

	static int ReadPaddleWidth()
	{
		return paddleWidths.find(paddleSize)->second;
	}

	void WritePaddleSize(const game::PaddleSize& size)
	{
		paddleSize = size;
	}

	game::PaddleSize ReadPaddleSize()
	{
		return paddleSize;
	}

	void WritePaddlePosition(int position)
	{
		paddlePosition = position;
	}

	int ReadPaddlePosition()
	{
		return paddlePosition;
	}

	void CenterPaddlePosition(int position)
	{
		int minimum = ReadPaddleWidth() / 2;
		int maximum = FIELD_WIDTH - minimum;
		position =
			(position < minimum) ? (minimum) :
			(position > maximum) ? (maximum) :
			(position);
		WritePaddlePosition(position - minimum);
	}

	std::string ReadSpriteName()
	{
		return paddleSprites.find(ReadPaddleSize())->second;
	}

	void Reset(const game::Difficulty&)
	{
		WritePaddleSize(PADDLE_SIZE_INITIAL);
		WritePaddlePosition(POSITION_INITIAL);
	}
}