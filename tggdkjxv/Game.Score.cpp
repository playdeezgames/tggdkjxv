#include "Game.Score.h"
namespace game::Score
{
	static int score;

	void Reset()
	{
		score = 0;
	}

	void Write(int value)
	{
		score = value;
	}

	int Read()
	{
		return score;
	}
}