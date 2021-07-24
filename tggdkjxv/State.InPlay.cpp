#include "Application.Renderer.h"
#include "Application.Command.h"
#include "Application.OnEnter.h"
#include "Game.Audio.Mux.h"
#include "Application.MouseMotion.h"
#include "Visuals.Areas.h"
#include <map>
#include "Application.Update.h"
#include "Game.Paddle.h"
#include "Visuals.Images.h"
namespace state::InPlay
{
	const std::string LAYOUT_NAME = "State.InPlay";
	const std::string AREA_PADDLE = "Paddle";
	const std::string IMAGE_PADDLE = "Paddle";
	const int PADDLE_Y = 344;

	static void HandlePaddle(const common::XY<int>& location)
	{
		game::Paddle::WritePaddlePosition(location.GetX());
	}

	const std::map<std::string, std::function<void(const common::XY<int>&)>> areaHandlers =
	{
		{AREA_PADDLE, HandlePaddle}
	};

	static void OnMouseMotionInArea(const std::string& areaName, const common::XY<int>& location)
	{
		areaHandlers.find(areaName)->second(location);
	}

	static void OnUpdate(const unsigned int& ticks)
	{
		visuals::Images::SetLocation(LAYOUT_NAME, IMAGE_PADDLE, { game::Paddle::ReadPaddlePosition(), PADDLE_Y });
	}

	void Start()
	{
		::application::OnEnter::AddHandler(::UIState::IN_PLAY, game::audio::Mux::GoToTheme(game::audio::Mux::Theme::MAIN));
		::application::Command::SetHandler(::UIState::IN_PLAY, ::application::UIState::GoTo(::UIState::MAIN_MENU));
		::application::Renderer::SetRenderLayout(::UIState::IN_PLAY, LAYOUT_NAME);
		::application::MouseMotion::AddHandler(::UIState::IN_PLAY, ::visuals::Areas::HandleMouseMotion(LAYOUT_NAME, OnMouseMotionInArea));
		::application::Update::AddHandler(::UIState::IN_PLAY, OnUpdate);
	}
}
