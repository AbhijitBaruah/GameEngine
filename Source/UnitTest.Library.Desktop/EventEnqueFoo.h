#pragma once
#include "GameState.h"
namespace GameEngine
{
	class EventEnqueFoo
	{
	public:
		EventEnqueFoo(GameState* gameState);
		GameState& gameState();
	private:
		GameState* _gameState;
		
	};

}
