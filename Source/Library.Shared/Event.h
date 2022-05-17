#pragma once
#include "IEventPublisher.h"

namespace GameEngine
{
	class IEventSubscriber;
	template<typename MessageType>
	/// <summary>
	/// A class that inherits from publisher. Events carry a templated data “payload” – the message of the event – and can be delivered immediately, or queued for future delivery. 
	/// </summary>
	/// <typeparam name="MessageType"></typeparam>
	class Event final : public IEventPublisher
	{
		RTTI_DECLARATIONS(Event);
	public:
		Event(const MessageType& message);
		Event(const Event& rhs) = default;
		Event& operator=(const Event& rhs) = default;
		Event(Event&& rhs) = default;
		Event& operator= (Event&& rhs) = default;
		/// <summary>
		/// Given the address of an EventSubscriber, add it to the list of subscribers for this event type.
		/// </summary>
		/// <param name="subscriber">The subscriber to subscribe to for this event</param>
		static void Subscribe(IEventSubscriber& subscriber);
		/// <summary>
		/// Given the address of an EventSubscriber, remove it from the list of subscribers for this event type
		/// </summary>
		/// <param name="subscriberToRemove">The subscriber to unsubscribe to for this event</param>
		static void UnSubscribe(IEventSubscriber& subscriberToRemove);
		/// <summary>
		/// Unsubscribe all subscribers to this event type.
		/// </summary>
		static void UnSubscribeAll();
		/// <summary>
		/// returns message object
		/// </summary>
		/// <returns>A const reference to the payload</returns>
		const MessageType& Message()const;
		
		/// <summary>
		/// A cleanup method to clear and shrink the vector
		/// </summary>
		static void Cleanup();

		/// <summary>
		/// Returns the size of the vector
		/// </summary>
		/// <returns>The size of the vector</returns>
		static std::size_t  Size();

		static void AddPending();
		static void RemovePending();
	private:
		inline static Vector<std::reference_wrapper<IEventSubscriber>> _pendingSubscriberList;
		inline static Vector<std::reference_wrapper<IEventSubscriber>> _pendingRemoveList;
		MessageType _payLoad;
		inline static Vector <std::reference_wrapper<IEventSubscriber>> _subscriberList;
		inline static bool _isUpdating{false};
	};


}
#include "Event.inl" 