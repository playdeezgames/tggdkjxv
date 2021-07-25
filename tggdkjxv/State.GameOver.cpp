#include "Application.Renderer.h"
#include "Application.Command.h"
#include "Application.MouseButtonUp.h"
#include "Application.OnEnter.h"
#include "Game.Audio.Mux.h"
#include "Visuals.Texts.h"
#include "Game.Score.h"
#include <format>
#include "Common.Audio.h"
namespace state::GameOver
{
	const std::string SFX_GAME_OVER = "game-over";
	const std::string LAYOUT_NAME = "State.GameOver";
	const std::string TEXT_FINAL_SCORE = "FinalScore";

	static bool OnMouseButtonUp(const common::XY<int>& xy, unsigned char buttons)
	{
		::application::UIState::Write(::UIState::MAIN_MENU);
		return true;
	}

	void OnEnter()
	{
		common::audio::Sfx::Play(SFX_GAME_OVER);
		game::audio::Mux::Play(game::audio::Mux::Theme::GAME_OVER);
		visuals::Texts::SetText(LAYOUT_NAME, TEXT_FINAL_SCORE, std::format("Final Score: {}", game::Score::Read()));
	}

	void Start()
	{
		::application::OnEnter::AddHandler(::UIState::GAME_OVER, OnEnter);
		::application::MouseButtonUp::AddHandler(::UIState::GAME_OVER, OnMouseButtonUp);
		::application::Command::SetHandler(::UIState::GAME_OVER, ::application::UIState::GoTo(::UIState::MAIN_MENU));
		::application::Renderer::SetRenderLayout(::UIState::GAME_OVER, LAYOUT_NAME);
	}
}
