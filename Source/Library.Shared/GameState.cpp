#include "pch.h"
#include "GameState.h"

#include "Scope.h"
#include"ActionCreateAction.h"
#include "ActionRemoveAction.h"
namespace GameEngine
{
	
	void GameEngine::GameState::CreatePending()
	{
		for (auto& [parentScope, actionToBeAdopted] : GameEngine::ActionCreateAction::_pendingListToAdd)
		{

			parentScope->Adopt(*actionToBeAdopted, "Actions");
		}

		GameEngine::ActionCreateAction::_pendingListToAdd.Clear();
		GameEngine::ActionCreateAction::_pendingListToAdd.ShrinkToFit();
	}

	void GameState::RemovePending()
	{
		for (auto& [datumToRemove, index] : GameEngine::ActionRemoveAction::_pendingListToRemove)
		{
			delete datumToRemove->Get<Scope*>(index);
		}
		GameEngine::ActionRemoveAction::_pendingListToRemove.Clear();
		GameEngine::ActionRemoveAction::_pendingListToRemove.ShrinkToFit();
	}

	const EventQueue& GameState::GetQueue() const
	{
		return _eventQueue;
	}

	EventQueue& GameState::GetQueue()
	{
		return _eventQueue;
	}

}