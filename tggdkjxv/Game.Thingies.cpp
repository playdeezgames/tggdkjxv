#include "Game.Thingies.h"
#include "Game.Paddle.h"
#include "Common.RNG.h"
namespace game::Thingies
{
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
	const double SPAWN_Y = MINIMUM_Y - ICON_HEIGHT/2.0;
	const double MISS_Y = MAXIMUM_Y + ICON_HEIGHT/2.0;
	const double Y_VELOCITY_INITIAL = 32.0;
	const double Y_VELOCITY_INCREMENT = 0.5;
	static double y_velocity;

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
			{common::RNG::FromRange(X_VELOCITY_MINIMUM, X_VELOCITY_MAXIMUM), y_velocity}
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

	static void UpdateThingies(double delta)
	{
		for (auto& thingie : thingies)
		{
			thingie.position = thingie.position + thingie.velocity * delta;
		}
	}

	static bool IsHittingPaddle(const game::Thingie& thingie)
	{
		if (thingie.position.GetY() >= MINIMUM_PADDLE_HIT_Y && thingie.position.GetY() <= MAXIMUM_PADDLE_HIT_Y)
		{
			double minimumPaddleHitX = (double)game::Paddle::ReadPaddlePosition() - ICON_WIDTH/2.0;
			double maximumPaddleHitX = (double)game::Paddle::ReadPaddlePosition() + (double)game::Paddle::ReadPaddleWidth() + ICON_WIDTH / 2.0;
			return thingie.position.GetX() >= minimumPaddleHitX && thingie.position.GetX() <= maximumPaddleHitX;
		}
		return false;
	}

	static bool NeedsCulling(const game::Thingie& thingie)
	{
		return (
			IsHittingPaddle(thingie) ||
			(thingie.position.GetY() > MISS_Y) ||
			(thingie.position.GetX() < MINIMUM_X) ||
			(thingie.position.GetX() >= MAXIMUM_X));
	}

	static void CullThingies()
	{
		thingies.remove_if(NeedsCulling);
	}

	void Update(double delta)
	{
		UpdateTimer(delta);
		UpdateThingies(delta);
		CullThingies();
	}
}