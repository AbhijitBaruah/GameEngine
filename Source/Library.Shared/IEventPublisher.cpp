#include "pch.h"
#include "IEventPublisher.h"
#include "IEventSubscriber.h"

namespace GameEngine
{
	RTTI_DEFINITIONS(IEventPublisher,RTTI)


		IEventPublisher::~IEventPublisher()
	{
	}
	void IEventPublisher::Deliver() 
	{
		_isUpdating = true;
		for (auto subscriber : _subscriberList)
		{
			subscriber.get().Notify(*this);
		}
		_isUpdating = false;

		
	
	}
	IEventPublisher::IEventPublisher(Vector<std::reference_wrapper<IEventSubscriber>>& subscriberList,bool& isUpdating):_subscriberList{subscriberList},_isUpdating{isUpdating}
	{
	}
}