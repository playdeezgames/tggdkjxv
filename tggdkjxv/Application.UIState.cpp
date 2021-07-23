#include "Application.UIState.h"
#include "Application.Sounds.h"
#include "Game.h"
#include "Game.Achievements.h"
#include <stack>
namespace application::UIState
{
	static ::UIState uiState = ::UIState::SPLASH;
	static std::stack<::UIState> stateStack;

	void Write(const ::UIState& state)
	{
		uiState = state;
	}

	std::function<void()> GoTo(const ::UIState& state)
	{
		return [state]()
		{
			Write(state);
		};
	}


	const ::UIState& Read()
	{
		return uiState;
	}

	void Push(const ::UIState& state)
	{
		stateStack.push(uiState);
		Write(state);
	}

	void Pop()
	{
		uiState = stateStack.top();
		stateStack.pop();
	}

	std::function<void()> PushTo(const ::UIState& state)
	{
		return [state]() {
			Push(state);
		};
	}

	std::optional<std::string> EnterGame()
	{
		game::AutoSave();
		//application::UIState::Write(::UIState::IN_PLAY_AT_SEA);
		return std::nullopt;
	}
}