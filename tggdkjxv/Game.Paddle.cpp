#include "Game.Paddle.h"
namespace game::Paddle
{
	const game::PaddleSize PADDLE_SIZE_INITIAL = game::PaddleSize::NORMAL;
	const int POSITION_INITIAL = 0;
	static PaddleSize paddleSize;
	static int paddlePosition;

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

	void Reset(const game::Difficulty&)
	{
		WritePaddleSize(PADDLE_SIZE_INITIAL);
		WritePaddlePosition(POSITION_INITIAL);
	}
}