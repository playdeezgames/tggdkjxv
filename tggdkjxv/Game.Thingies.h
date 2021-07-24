#pragma once
#include "Game.Thingie.h"
#include <list>
#include "Game.Difficulty.h"
namespace game::Thingies
{
	const std::list<Thingie>& All();
	void Reset(const game::Difficulty&);
	void Update(double);
}
