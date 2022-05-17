#pragma once
#include "Event.h"

namespace GameEngine
{
	template<typename MessageType>
	RTTI::IdType Event<MessageType>::TypeIdClass() { return _typeId; }
	template<typename MessageType>
	RTTI::IdType Event<MessageType>::TypeIdInstance() const { return TypeIdClass(); }
	template<typename MessageType>
	bool Event<MessageType>::Is(RTTI::IdType id) const { return (id == _typeId ? true : IEventPublisher::Is(id)); }
	template<typename MessageType>
	const RTTI::IdType Event<MessageType>::_typeId = reinterpret_cast<RTTI::IdType>(&Event<MessageType>::_typeId);
	template<typename MessageType>

	inline Event<MessageType>::Event(const MessageType& message) : IEventPublisher(_subscriberList, _isUpdating), _payLoad{ message }
	{
	}

	template<typename MessageType>
	inline void Event<MessageType>::Subscribe(IEventSubscriber& subscriber)
	{
		if (!_isUpdating)
		{
			_subscriberList.PushBack(subscriber);
		}
		else
		{
			_pendingSubscriberList.PushBack(subscriber);
		}
	}

	template<typename MessageType>
	inline void Event<MessageType>::UnSubscribe(IEventSubscriber& subscriberToRemove)
	{
		if (!_isUpdating)
		{
			for (std::size_t i = 0; i < _subscriberList.Size(); ++i)
			{
				if (&_subscriberList[i].get() == &subscriberToRemove)
				{
					_subscriberList.RemoveAt(i);
				}
			}
		}
		else
		{
			_pendingRemoveList.PushBack(subscriberToRemove);
		}

	}

	template<typename MessageType>
	inline void Event<MessageType>::UnSubscribeAll()
	{
		if (!_isUpdating)
		{
			_subscriberList.Clear();
		}
	}

	template<typename MessageType>
	inline const MessageType& Event<MessageType>::Message()  const { return _payLoad; }



	template<typename MessageType>
	inline void Event<MessageType>::Cleanup()
	{
		_subscriberList.Clear();
		_subscriberList.ShrinkToFit();
	}

	template<typename MessageType>
	std::size_t  Event<MessageType>::Size()
	{
		return _subscriberList.Size();
	}

	template<typename MessageType>
	inline void Event<MessageType>::AddPending()
	{
		for (std::size_t i = 0; i < _pendingSubscriberList.Size(); ++i)
		{
			_subscriberList.PushBack(_pendingSubscriberList[i]);
		}
		_pendingSubscriberList.Clear();
		_pendingSubscriberList.ShrinkToFit();
	}

	template<typename MessageType>
	inline void Event<MessageType>::RemovePending()
	{
		for (std::size_t i = 0; i < _pendingRemoveList.Size(); ++i)
		{
			UnSubscribe(_pendingRemoveList[i]);
		}
		_pendingRemoveList.Clear();
		_pendingRemoveList.ShrinkToFit();
	}
}





