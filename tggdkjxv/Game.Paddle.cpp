#include "Game.Paddle.h"
#include <map>
namespace game::Paddle
{
	const game::PaddleSize PADDLE_SIZE_INITIAL = game::PaddleSize::NORMAL;
	const int POSITION_INITIAL = 0;
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

	static std::optional<game::PaddleSize> paddleSize;
	static int paddlePosition;

	int ReadPaddleWidth()
	{
		if (paddleSize.has_value())
		{
			return paddleWidths.find(paddleSize.value())->second;
		}
		return 0;
	}

	void WritePaddleSize(const std::optional<game::PaddleSize>& size)
	{
		paddleSize = size;
	}

	std::optional<game::PaddleSize> ReadPaddleSize()
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

	std::optional<std::string> ReadSpriteName()
	{
		if (paddleSize.has_value())
		{
			return paddleSprites.find(paddleSize.value())->second;
		}
		return std::nullopt;
	}

	void DecreasePaddleSize()
	{
		std::optional<game::PaddleSize> size = std::nullopt;
		if (paddleSize)
		{
			switch (paddleSize.value())
			{
			case PaddleSize::NORMAL:
				size = PaddleSize::SMALL;
				break;
			case PaddleSize::SMALL:
				size = PaddleSize::SMALLER;
				break;
			case PaddleSize::SMALLER:
				size = PaddleSize::SMALLEST;
				break;
			}
		}
		WritePaddleSize(size);
	}

	void IncreasePaddleSize()
	{
		std::optional<game::PaddleSize> size = std::nullopt;
		if (paddleSize)
		{
			switch (paddleSize.value())
			{
			case PaddleSize::SMALLEST:
				size = PaddleSize::SMALLER;
				break;
			case PaddleSize::SMALLER:
				size = PaddleSize::SMALL;
				break;
			case PaddleSize::SMALL:
			case PaddleSize::NORMAL:
				size = PaddleSize::NORMAL;
				break;
			}
		}
		WritePaddleSize(size);
	}

	void Reset(const game::Difficulty&)
	{
		WritePaddleSize(PADDLE_SIZE_INITIAL);
		WritePaddlePosition(POSITION_INITIAL);
	}
}