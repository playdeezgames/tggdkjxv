#pragma once
#include <functional>
namespace game::audio::Mux
{
	enum class Theme
	{
		MAIN,
		GAME_OVER
	};
	void Play(const Theme&);
	std::function<void()> GoToTheme(const Theme&);
}

