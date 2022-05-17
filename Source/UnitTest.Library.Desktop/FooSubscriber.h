#pragma once
#include "IEventSubscriber.h"
#include "IEventPublisher.h"
namespace GameEngine
{
	class FooSubscriber :public IEventSubscriber
	{
		void Notify(const IEventPublisher&) override;
	};

}
