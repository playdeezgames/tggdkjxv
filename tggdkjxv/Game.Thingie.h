#pragma once
#include "Game.ThingieType.h"
#include "Common.XY.h"
namespace game
{
	struct Thingie
	{
		game::ThingieType thingieType;
		common::XY<double> position;
		common::XY<double> velocity;
	};
}
