#pragma once
#include "GameTime.h"
#include "Vector.h"
#include "IEventPublisher.h"
namespace GameEngine
{
	struct EventQueueInfo
	{
		EventQueueInfo(std::shared_ptr<IEventPublisher> event, std::chrono::high_resolution_clock::time_point timeEnqueued, std::chrono::milliseconds delay) : _event{ event }, _enqueueTime{ timeEnqueued }, _delay{delay} {}
		std::shared_ptr<IEventPublisher> _event;
		std::chrono::high_resolution_clock::time_point _enqueueTime;
		std::chrono::milliseconds _delay{0};
	};
	class EventQueue final
	{
	public: 
		void Enqueue(std::shared_ptr<IEventPublisher> publisher, const GameTime& gameTime, std::chrono::milliseconds = std::chrono::milliseconds::zero());
		void Update(const GameTime& gameTime);
		void Clear();
		bool isEmpty()const;
		std::size_t Size() const;
	private:
		Vector<EventQueueInfo> _eventQueue;
		Vector<EventQueueInfo> _pendingQueue;
		bool _isUpdating{ false };
		bool _shoudlClear{ false };

	};

}
