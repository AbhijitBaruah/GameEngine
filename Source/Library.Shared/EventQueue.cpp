#include "pch.h"
#include "EventQueue.h"
#include "IEventPublisher.h"
#include <algorithm>
namespace GameEngine
{
	void GameEngine::EventQueue::Enqueue(std::shared_ptr<IEventPublisher> event, const GameTime& gameTime, std::chrono::milliseconds delay)
	{
		if (!_isUpdating)
		{
			_eventQueue.PushBack(EventQueueInfo{ event,gameTime.CurrentTime(),delay });
		}
		else
		{
			_pendingQueue.PushBack(EventQueueInfo{ event,gameTime.CurrentTime(),delay });
		}
	}
	void EventQueue::Update(const GameTime& gameTime)
	{
		_isUpdating = true;
		auto it = std::partition(_eventQueue.begin(), _eventQueue.end(), [&gameTime, this](EventQueueInfo qEvent) {return  gameTime.CurrentTime() <= qEvent._enqueueTime + qEvent._delay; });
		for (Vector<EventQueueInfo>::Iterator it1 = it; it1 != _eventQueue.end(); ++it1)
		{
			(*it1)._event->Deliver();
		}
		_eventQueue.Remove(it,_eventQueue.end());
		if (_shoudlClear)
		{
			_eventQueue.Clear();
			_shoudlClear = false;
		}
		for (std::size_t i = 0; i < _pendingQueue.Size(); ++i)
		{
			_eventQueue.PushBack(_pendingQueue[i]);
		}
		_pendingQueue.Clear();
		_isUpdating = false;
	}

	void EventQueue::Clear()
	{
		_shoudlClear = true;
		if (!_isUpdating)
		{
			_eventQueue.Clear();
			_shoudlClear = false;
		}
	}

	bool EventQueue::isEmpty() const
	{
		return _eventQueue.Size() == 0;
	}

	std::size_t EventQueue::Size() const
	{
		return _eventQueue.Size();
	}

	





}
