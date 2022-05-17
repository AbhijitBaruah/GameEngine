#pragma once
namespace GameEngine
{
	class IEventPublisher;
	/// <summary>
	/// Abstract base class for a subscriber
	/// </summary>
	class IEventSubscriber
	{
	public:
		/// <summary>
		/// Pure virtual method that allows children to override what they want to do when they are notified of an event buy a subscriber
		/// </summary>
		/// <param name=""></param>
		virtual void Notify(const IEventPublisher&)=0;
	};

}
