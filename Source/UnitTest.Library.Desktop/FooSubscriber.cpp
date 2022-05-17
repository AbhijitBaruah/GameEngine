#include "pch.h"
#include "FooSubscriber.h"
#include "Foo.h"
void GameEngine::FooSubscriber::Notify(const IEventPublisher& publisher) 
{
	
	const Foo* foo = publisher.As<Foo>();
	if (foo != nullptr)
	{

	}
}
