#pragma once
#include "RTTI.h"
#include "Vector.h"
#include <memory>
namespace GameEngine
{
	class IEventSubscriber;
	/// <summary>
	/// Abstract base class that loops through the list of subscribers and notifies every single one of the subscribers
	/// </summary>
	class IEventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(IEventPublisher);
	public:
		/// <summary>
		/// Loops through each of its subscriber and calls their notify method
		/// </summary>
		void Deliver();
	protected:
		IEventPublisher() = delete;
		IEventPublisher(const IEventPublisher&) = default;
		IEventPublisher& operator=(const IEventPublisher&) = default;
		IEventPublisher(IEventPublisher && rhs)noexcept = default;
		IEventPublisher& operator=(IEventPublisher && rhs) noexcept = default;
		virtual ~IEventPublisher() override;
		IEventPublisher(Vector<std::reference_wrapper<IEventSubscriber>>&,bool& isUpdating);
		

	private:
		Vector<std::reference_wrapper<IEventSubscriber>>& _subscriberList;
		bool& _isUpdating;

				
	};

}
