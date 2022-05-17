#include "pch.h"
#include "EventEnqueFoo.h"

namespace GameEngine
{
	GameEngine::EventEnqueFoo::EventEnqueFoo(GameState* gameState) :_gameState{ gameState }
	{
	}
	GameState& EventEnqueFoo::gameState()
	{
		return *_gameState;
	}
}
