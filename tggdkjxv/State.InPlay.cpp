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
#include "Game.Thingies.h"
#include <format>
#include "Visuals.Texts.h"
#include "Game.Score.h"
namespace state::InPlay
{
	const std::string LAYOUT_NAME = "State.InPlay";
	const std::string AREA_PADDLE = "Paddle";
	const std::string IMAGE_PADDLE = "Paddle";
	const std::string TEXT_SCORE = "Score";
	const int ICON_COUNT = 20;
	const int PADDLE_Y = 344;

	static void HandlePaddle(const common::XY<int>& location)
	{
		game::Paddle::CenterPaddlePosition(location.GetX());
	}

	const std::map<std::string, std::function<void(const common::XY<int>&)>> areaHandlers =
	{
		{AREA_PADDLE, HandlePaddle}
	};

	static void OnMouseMotionInArea(const std::string& areaName, const common::XY<int>& location)
	{
		areaHandlers.find(areaName)->second(location);
	}

	static void UpdatePaddle()
	{
		auto spriteName = game::Paddle::ReadSpriteName();
		visuals::Images::SetVisible(LAYOUT_NAME, IMAGE_PADDLE, spriteName.has_value());
		if (spriteName)
		{
			visuals::Images::SetLocation(LAYOUT_NAME, IMAGE_PADDLE, { game::Paddle::ReadPaddlePosition(), PADDLE_Y });
			visuals::Images::SetSprite(LAYOUT_NAME, IMAGE_PADDLE, spriteName.value());
		}
	}

	static void HideAllIcons()
	{
		for (int index = 0; index < ICON_COUNT; ++index)
		{
			visuals::Images::SetVisible(LAYOUT_NAME, std::format("Icon{}",index), false);
		}
	}

	static void RefreshIcons()
	{
		int index = 0;
		for (auto& thingie : game::Thingies::All())
		{
			std::string imageId = std::format("Icon{}", index);
			visuals::Images::SetVisible(LAYOUT_NAME, imageId, true);
			common::XY<int> plot = { (int)thingie.position.GetX(), (int)thingie.position.GetY()};
			visuals::Images::SetLocation(LAYOUT_NAME, imageId, plot);

			index++;
			if (index >= ICON_COUNT)
			{
				break;
			}
		}
	}

	static void UpdateThingies(const unsigned int& ticks)
	{
		HideAllIcons();
		game::Thingies::Update((double)ticks / 1000.0);
		RefreshIcons();
		
	}

	static void OnUpdate(const unsigned int& ticks)
	{
		UpdatePaddle();
		UpdateThingies(ticks);
		visuals::Texts::SetText(LAYOUT_NAME, TEXT_SCORE, std::format("{}", game::Score::Read()));
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
