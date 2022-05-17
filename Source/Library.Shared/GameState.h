#pragma once
#include "Vector.h"
#include "Scope.h"
#include "EventQueue.h"
namespace GameEngine
{
	class GameState
	{
	public:
		void CreatePending();
		void RemovePending();
		 const EventQueue& GetQueue() const;
		 EventQueue& GetQueue();
	private:
		 EventQueue _eventQueue;
	};


}