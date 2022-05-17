#include "pch.h"
#include "Foo.h"
#include "ToStringOverload.h"
#include "IEventSubscriber.h"
#include "IEventPublisher.h"
#include "Event.h"
#include "EventQueue.h"
#include "Avatar.h"
#include "EventEnqueFoo.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EventTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}
		struct  FooSubscriber final :public IEventSubscriber
		{
			void Notify(const IEventPublisher& publisher) override
			{
				const Event<Foo>* foo = publisher.As<Event<Foo>>();
				if (foo != nullptr)
				{
					foo->Message();
					wasFound = true;
					Data = 10;
				}
			}

			bool wasFound = false;
			int Data = 0;
		};
		struct EventClearSubsriber final : IEventSubscriber
		{
			std::size_t _count = 0;
			void Notify(const IEventPublisher& publisher)override
			{
				++_count;
				const Event<EventEnqueFoo>* e = publisher.As<Event<EventEnqueFoo>>();
				if (e != nullptr)
				{
					EventEnqueFoo message = e->Message();
					EventQueue& queue = message.gameState().GetQueue();

					queue.Clear();
				}
			}
		};
		struct EventQueueSubsriber final : IEventSubscriber
		{
			std::size_t _count = 0;
			void Notify(const IEventPublisher& publisher)override
			{
				++_count;
				const Event<EventEnqueFoo>* e = publisher.As<Event<EventEnqueFoo>>();

				if (e != nullptr)
				{
					EventEnqueFoo message = e->Message();
					EventQueue& queue = message.gameState().GetQueue();
					std::shared_ptr<Event<EventEnqueFoo>> newEvent = std::make_shared<Event<EventEnqueFoo>>(message);
					GameTime gameTime;
					queue.Enqueue(newEvent, gameTime);
				}
			}
		};

		
		struct SubAdd final :IEventSubscriber
		{
			std::size_t _count = 0;
			void Notify(const IEventPublisher& publisher)override
			{
				++_count;
				const Event<EventEnqueFoo>* e = publisher.As<Event<EventEnqueFoo>>();

				if (e != nullptr)
				{
					Event<EventEnqueFoo>::Subscribe(*this);
				}
			}

		};


		struct SubRemove final :IEventSubscriber
		{
			std::size_t _count = 0;
			void Notify(const IEventPublisher& publisher)override
			{
				++_count;
				const Event<EventEnqueFoo>* e = publisher.As<Event<EventEnqueFoo>>();

				if (e != nullptr)
				{
					Event<EventEnqueFoo>::UnSubscribe(*this);
				}
			}

		};

		struct  AvatarSubscriber final : IEventSubscriber
		{
			void Notify(const IEventPublisher& publisher) override
			{
				const Event<Avatar>* foo = publisher.As<Event<Avatar>>();
				if (foo != nullptr)
				{

					wasFound = true;
					Data = 10;
				}
			}

			bool wasFound = false;
			int Data = 0;
		};

		TEST_METHOD(RTTITest)
		{
			Foo foo{ 1 };
			Event<Foo> event(foo);

			RTTI* rtti = &event;
			Assert::IsTrue(rtti->Is(Event<Foo>::TypeIdClass()));
			Assert::IsTrue(rtti->Is(IEventPublisher::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));

			Event<Foo>* e = rtti->As<Event<Foo>>();
			Assert::IsNotNull(e);
			Assert::AreEqual(&event, e);

			IEventPublisher* ep = rtti->As<IEventPublisher>();
			Assert::IsNotNull(ep);
			Assert::AreEqual(&event, static_cast<Event<Foo>*>(ep));
			Assert::IsTrue(rtti->Is(ep->TypeIdInstance()));

			
			Event<Foo>::UnSubscribeAll();
			

		}

		TEST_METHOD(EventPublisherRTTI)
		{
			Foo foo{ 1 };
			Event<Foo> event(foo);
			IEventPublisher* eventP = static_cast<IEventPublisher*>(&event);

			RTTI* rtti = eventP;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(IEventPublisher::TypeIdClass()));
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(IEventPublisher::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(eventP->TypeIdInstance(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			IEventPublisher* a = rtti->As<IEventPublisher>();
			Assert::IsNotNull(a);
			Assert::AreEqual(eventP, a);
		
		}
		TEST_METHOD(EventEnqueue)
		{

			GameTime time;
			Foo foo;
			Avatar a;
			FooSubscriber fooSubscriber;
			AvatarSubscriber avatarSubscriber;
			GameState gs;
			std::shared_ptr<Event<Foo>> e = std::make_shared<Event<Foo>>(foo);
			std::shared_ptr<Event<Avatar>> ea = std::make_shared<Event<Avatar>>(a);
			Assert::AreEqual(e->Message(), foo);
			Assert::AreEqual(ea->Message(), a);
			Assert::AreEqual(std::size_t(0), gs.GetQueue().Size());
			gs.GetQueue().Enqueue(e, time);
			gs.GetQueue().Enqueue(ea, time);
			Assert::AreEqual(std::size_t(2), gs.GetQueue().Size());
			Event<Foo>::Subscribe(fooSubscriber);
			Event<Avatar>::Subscribe(avatarSubscriber);
			Event<Avatar>::Subscribe(fooSubscriber);
			time.SetCurrentTime(high_resolution_clock::time_point(1s));
			Assert::IsFalse(fooSubscriber.wasFound);
			Assert::IsFalse(avatarSubscriber.wasFound);
			gs.GetQueue().Update(time);
			Assert::IsTrue(fooSubscriber.wasFound);
			Assert::IsTrue(avatarSubscriber.wasFound);
			fooSubscriber.wasFound = false;
			avatarSubscriber.wasFound = false;
			time.SetCurrentTime(high_resolution_clock::time_point());
			gs.GetQueue().Enqueue(e, time, 1s);
			gs.GetQueue().Enqueue(ea, time, 500ms);
			gs.GetQueue().Clear();
			Assert::IsTrue(gs.GetQueue().isEmpty());
			gs.GetQueue().Enqueue(e, time, 1s);
			gs.GetQueue().Enqueue(ea, time, 500ms);
			Assert::AreEqual(std::size_t(2), gs.GetQueue().Size());
			Assert::IsFalse(fooSubscriber.wasFound);
			Assert::IsFalse(avatarSubscriber.wasFound);
			time.SetCurrentTime(high_resolution_clock::time_point(1s));
			gs.GetQueue().Update(time);
			Assert::IsFalse(fooSubscriber.wasFound);
			Assert::IsTrue(avatarSubscriber.wasFound);
			time.SetCurrentTime(high_resolution_clock::time_point(2s));
			avatarSubscriber.wasFound = false;
			gs.GetQueue().Update(time);
			Assert::IsTrue(fooSubscriber.wasFound);
			Assert::IsFalse(avatarSubscriber.wasFound);
			e->Cleanup();
			ea->Cleanup();
			Event<Foo>::UnSubscribeAll();
			Event<Avatar>::UnSubscribeAll();
			
		}

		TEST_METHOD(EventSubscriberThatEnquesEvent)
		{
			GameTime gameTime;
			GameState gameState;
			Foo f;
			EventQueueSubsriber subsrciber;
			EventEnqueFoo eventEnqueueFoo(&gameState);
			std::shared_ptr<Event<EventEnqueFoo>> eef = std::make_shared<Event<EventEnqueFoo>>(eventEnqueueFoo);
			gameState.GetQueue().Enqueue(eef, gameTime);
			Event<EventEnqueFoo>::Subscribe(subsrciber);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(1s));
			Assert::AreEqual((std::size_t)0, subsrciber._count);
			Assert::AreEqual(gameState.GetQueue().Size(), (std::size_t)1);
			gameState.GetQueue().Update(gameTime);
			Assert::AreEqual((std::size_t)1, subsrciber._count);
			Assert::AreEqual(gameState.GetQueue().Size(), (std::size_t)1);
			gameState.GetQueue().Update(gameTime);
			Assert::AreEqual((std::size_t)2, subsrciber._count);
			Assert::AreEqual(gameState.GetQueue().Size(), (std::size_t)1);
			Event<EventEnqueFoo>::UnSubscribeAll();
			eef->Cleanup();
			Event<EventEnqueFoo>::UnSubscribeAll();
		}
		TEST_METHOD(CopyTests)
		{
			
				Event<Foo> event1(Foo{});
				Event<Foo> event2(event1);
				Assert::AreNotSame(event1.Message(), event2.Message());
				Assert::AreEqual(event1.Message(), event2.Message());
		}

		TEST_METHOD(MoveTests)
		{
			Event<Foo> event1(Foo{});
			Event<Foo> event2(Foo{});
			Assert::IsFalse(&event1.Message() == &event2.Message());

		}
		TEST_METHOD(EventClearSubscriberTest)
		{
			GameTime gameTime;
			GameState gameState;
			Foo f;
			EventClearSubsriber subsrciber;
			EventEnqueFoo eventEnqueueFoo(&gameState);
			FooSubscriber fooSubscriber;
			std::shared_ptr<Event<EventEnqueFoo>> eef = std::make_shared<Event<EventEnqueFoo>>(eventEnqueueFoo);
			std::shared_ptr<Event<Foo>> e = std::make_shared<Event<Foo>>(f);
			gameState.GetQueue().Enqueue(eef, gameTime);
			gameState.GetQueue().Enqueue(e, gameTime);
			Event<EventEnqueFoo>::Subscribe(subsrciber);
			Event<Foo>::Subscribe(fooSubscriber);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(1s));
			Assert::AreEqual((std::size_t)0, subsrciber._count);
			Assert::AreEqual(gameState.GetQueue().Size(), (std::size_t)2);
			gameState.GetQueue().Update(gameTime);
			Assert::AreEqual((std::size_t)1, subsrciber._count);
			Assert::AreEqual(gameState.GetQueue().Size(), (std::size_t)0);
			gameState.GetQueue().Update(gameTime);
			Assert::AreEqual(gameState.GetQueue().Size(), (std::size_t)0);
			eef->Cleanup();
			e->Cleanup();
			Event<EventEnqueFoo>::UnSubscribeAll();
			Event<Foo>::UnSubscribeAll();
		}
		TEST_METHOD(UnsubscribeTest)
		{
			GameTime time;
			EventQueue queue;
			FooSubscriber fooSubscriber1;
			FooSubscriber fooSubscriber2;
			FooSubscriber fooSubscriber3;

			Event<Foo>::Subscribe(fooSubscriber1);
			Event<Foo>::Subscribe(fooSubscriber2);
			Event<Foo>::Subscribe(fooSubscriber3);

			Assert::AreEqual(size_t(3), Event<Foo>::Size());

			Event<Foo>::UnSubscribe(fooSubscriber1);

			Assert::AreEqual(size_t(2), Event<Foo>::Size());

			Event<Foo>::UnSubscribeAll();

			Assert::AreEqual(size_t(0), Event<Foo>::Size());

			Event<Foo>::Cleanup();
			Event<Foo>::UnSubscribeAll();
		}
		TEST_METHOD(SubscriberAdd)
		{
			GameTime gameTime;
			GameState gameState;
			SubAdd subscriber;
			EventEnqueFoo eventEnqueueFoo(&gameState);
			std::shared_ptr<Event<EventEnqueFoo>> eef = std::make_shared<Event<EventEnqueFoo>>(eventEnqueueFoo);
			gameState.GetQueue().Enqueue(eef, gameTime);
			Assert::AreEqual(Event<EventEnqueFoo>::Size(), (std::size_t)0);
			Event<EventEnqueFoo>::Subscribe(subscriber);
			Assert::AreEqual(Event<EventEnqueFoo>::Size(), (std::size_t)1);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(1s));
			Assert::AreEqual((std::size_t)0, subscriber._count);
			Assert::AreEqual(gameState.GetQueue().Size(), (std::size_t)1);
			gameState.GetQueue().Update(gameTime);
			Assert::AreEqual((std::size_t)1, subscriber._count);
			Assert::AreEqual(Event<EventEnqueFoo>::Size(), (std::size_t)1);
			Event<EventEnqueFoo>::AddPending();
			Assert::AreEqual(Event<EventEnqueFoo>::Size(), (std::size_t)2);
			gameState.GetQueue().Enqueue(eef, gameTime);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(2s));
			gameState.GetQueue().Update(gameTime);
			Assert::AreEqual((std::size_t)3, subscriber._count);
			Assert::AreEqual(Event<EventEnqueFoo>::Size(), (std::size_t)2);
			Event<EventEnqueFoo>::AddPending();
			eef->Cleanup();
			Event<EventEnqueFoo>::UnSubscribeAll();

		}

		TEST_METHOD(SubscriberRemove)
		{
			GameTime gameTime;
			GameState gameState;
			SubRemove subscriber;
			FooSubscriber f;
			EventEnqueFoo eventEnqueueFoo(&gameState);
			std::shared_ptr<Event<EventEnqueFoo>> eef = std::make_shared<Event<EventEnqueFoo>>(eventEnqueueFoo);
			gameState.GetQueue().Enqueue(eef, gameTime);
			Assert::AreEqual(Event<EventEnqueFoo>::Size(), (std::size_t)0);
			Event<EventEnqueFoo>::Subscribe(subscriber);
			Event<EventEnqueFoo>::Subscribe(f);
			Assert::AreEqual(Event<EventEnqueFoo>::Size(), (std::size_t)2);
			gameTime.SetCurrentTime(high_resolution_clock::time_point(1s));
			Assert::AreEqual((std::size_t)0, subscriber._count);
			Assert::AreEqual(gameState.GetQueue().Size(), (std::size_t)1);
			gameState.GetQueue().Update(gameTime);
			Assert::AreEqual((std::size_t)1, subscriber._count);
			Assert::AreEqual(Event<EventEnqueFoo>::Size(), (std::size_t)2);
			Event<EventEnqueFoo>::RemovePending();
			Assert::AreEqual(Event<EventEnqueFoo>::Size(), (std::size_t)1);
			eef->Cleanup();
			Event<EventEnqueFoo>::UnSubscribeAll();


		}
	private:
		static _CrtMemState _startMemState;


	};
	_CrtMemState EventTests::_startMemState;
}
