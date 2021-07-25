#include "Game.Thingies.h"
#include "Game.Paddle.h"
#include "Common.RNG.h"
#include "Game.Score.h"
#include "Common.Audio.h"
namespace game::Thingies
{
	const std::string SFX_HIT_CHOCOLATE = "hit-chocolate";
	const std::string SFX_MISS_CHOCOLATE = "miss-chocolate";

	const double X_VELOCITY_MINIMUM = -8.0;
	const double X_VELOCITY_MAXIMUM = 8.0;
	const double MINIMUM_X = 0.0;
	const double MAXIMUM_X = (double)game::Paddle::FIELD_WIDTH;

	const double ICON_WIDTH = 16.0;
	const double ICON_HEIGHT = 16.0;

	const double PADDLE_HEIGHT = 16.0;

	const double MAXIMUM_Y = 360.0;
	const double MINIMUM_Y = 0.0;
	const double MINIMUM_PADDLE_Y = MAXIMUM_Y - PADDLE_HEIGHT;
	const double MINIMUM_PADDLE_HIT_Y = MINIMUM_PADDLE_Y - ICON_HEIGHT / 2.0;
	const double MAXIMUM_PADDLE_Y = MAXIMUM_Y;
	const double MAXIMUM_PADDLE_HIT_Y = MAXIMUM_PADDLE_Y + ICON_HEIGHT / 2.0;
	const double SPAWN_Y = MINIMUM_Y - ICON_HEIGHT / 2.0;
	const double MISS_Y = MAXIMUM_Y + ICON_HEIGHT / 2.0;
	const double Y_VELOCITY_INITIAL = 32.0;
	const double Y_VELOCITY_INCREMENT = 0.5;
	static double y_velocity;
	const double Y_VELOCITY_MULTIPLIER_MINIMUM = 1.0;
	const double Y_VELOCITY_MULTIPLIER_MAXIMUM = 3.0;

	const double TIME_INTERVAL = 1.0;
	static double timeLeft;

	static std::list<Thingie> thingies;

	const std::list<Thingie>& All()
	{
		return thingies;
	}

	static void ResetTimer()
	{
		timeLeft = TIME_INTERVAL;
	}

	void Reset(const game::Difficulty&)
	{
		y_velocity = Y_VELOCITY_INITIAL;
		thingies.clear();
		ResetTimer();
	}

	static void SpawnThingie()
	{
		game::Thingie thingie =
		{
			game::ThingieType::CHOCOLATE,
			{common::RNG::FromRange(0.0, (double)game::Paddle::FIELD_WIDTH),SPAWN_Y},
			{common::RNG::FromRange(X_VELOCITY_MINIMUM, X_VELOCITY_MAXIMUM), y_velocity * common::RNG::FromRange(Y_VELOCITY_MULTIPLIER_MINIMUM, Y_VELOCITY_MULTIPLIER_MAXIMUM)}
		};
		y_velocity += Y_VELOCITY_INCREMENT;
		thingies.push_back(thingie);
	}

	static void UpdateTimer(double delta)
	{
		timeLeft -= delta;
		if (timeLeft <= 0.0)
		{
			ResetTimer();
			SpawnThingie();
		}
	}
	static bool IsHittingPaddle(const game::Thingie& thingie)
	{
		if (thingie.position.GetY() >= MINIMUM_PADDLE_HIT_Y && thingie.position.GetY() <= MAXIMUM_PADDLE_HIT_Y)
		{
			double minimumPaddleHitX = (double)game::Paddle::ReadPaddlePosition() - ICON_WIDTH / 2.0;
			double maximumPaddleHitX = (double)game::Paddle::ReadPaddlePosition() + (double)game::Paddle::ReadPaddleWidth() + ICON_WIDTH / 2.0;
			return thingie.position.GetX() >= minimumPaddleHitX && thingie.position.GetX() <= maximumPaddleHitX;
		}
		return false;
	}

	static void IncrementScore()
	{
		game::Score::Write(game::Score::Read() + 1);
	}

	static void CollectThingie(const game::Thingie& thingie)
	{
		switch (thingie.thingieType)
		{
		case game::ThingieType::CHOCOLATE:
			common::audio::Sfx::Play(SFX_HIT_CHOCOLATE);
			IncrementScore();
			break;
		}
	}

	static void UpdateThingies(double delta)
	{
		for (auto& thingie : thingies)
		{
			thingie.position = thingie.position + thingie.velocity * delta;
			if (IsHittingPaddle(thingie))
			{
				CollectThingie(thingie);
			}
		}
	}

	static bool IsMiss(const game::Thingie& thingie)
	{
		return (thingie.position.GetY() > MISS_Y);
	}

	static bool NeedsCulling(const game::Thingie& thingie)
	{
		return (
			IsHittingPaddle(thingie) ||
			IsMiss(thingie) ||
			(thingie.position.GetX() < MINIMUM_X - ICON_WIDTH / 2.0) ||
			(thingie.position.GetX() >= MAXIMUM_X + ICON_WIDTH / 2.0));
	}

	static void CullThingies()
	{
		thingies.remove_if(NeedsCulling);
	}

	static void ProcessMisses()
	{
		bool shrinkPaddle = false;
		for (auto& thingie : thingies)
		{
			if (IsMiss(thingie))
			{
				switch (thingie.thingieType)
				{
				case game::ThingieType::CHOCOLATE:
					shrinkPaddle = true;
					break;
				}
			}
		}
		if (shrinkPaddle)
		{
			common::audio::Sfx::Play(SFX_MISS_CHOCOLATE);
			game::Paddle::DecreasePaddleSize();
		}
	}

	void Update(double delta)
	{
		UpdateTimer(delta);
		UpdateThingies(delta);
		ProcessMisses();
		CullThingies();
	}
}