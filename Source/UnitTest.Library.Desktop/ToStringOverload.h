#pragma once
#include "CppUnitTest.h"
#include "Foo.h"
#include "Vector.h"
#include "SList.h"
#include "HashMap.h"
#include "Datum.h"
#include "glm/glm.hpp"
#include "Scope.h"
#include "AttributedFoo.h"
#include "JsonIntegerParseHelper.h"
#include "JsonParseCoordinator.h"
#include "TableParserHelper.h"
#include "GameObject.h"
#include "Avatar.h"
#include "Action.h"
#include "ActionList.h"
#include "ActionListIf.h"
#include "ActionCreateAction.h"
#include "ActionRemoveAction.h"
#include "ActionIncrement.h"
#include "Event.h"
#include "IEventPublisher.h"
using namespace GameEngine;
using namespace std::string_literals;
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {

			template <> 
			inline std::wstring ToString<GameEngine::Foo>(const GameEngine::Foo& t) 
			{
				RETURN_WIDE_STRING(t.Data());
			}
			template <typename T, typename Q>
			inline std::wstring ToString(const std::pair<T, Q>& t)
			{
				return ToString(t.second);
			}
			template <typename T>
			inline std::wstring ToString(const GameEngine::SList<T>& t)
			{
				RETURN_WIDE_STRING(t.Size());
			}

			template <>
			inline std::wstring ToString<GameEngine::SList<Foo>::Iterator>(const SList<Foo>::Iterator& t)
			{
				t;
				return L"end()"s;
			}
			template <>
			inline std::wstring ToString<GameEngine::HashMap<Foo, Foo>::Iterator>(const HashMap<Foo, Foo>::Iterator& t)
			{
				t;
				return L"end()"s;
			}
			template <>
			inline std::wstring ToString<GameEngine::HashMap<Foo, Foo>::ConstIterator>(const HashMap<Foo, Foo>::ConstIterator& t)
			{
				t;
				return L"end()"s;
			}
			template <>
			inline std::wstring ToString<GameEngine::SList<Foo>::ConstIterator>(const SList<Foo>::ConstIterator& t)
			{
				t;
				return L"end()"s;
			}
		

			template <>
			inline std::wstring ToString<GameEngine::Vector<Foo>::Iterator>(const Vector<Foo>::Iterator& t)
			{
				t;
				return L"end()"s;
			}
			template <>
			inline std::wstring ToString<GameEngine::Vector<Foo>::ConstIterator>(const Vector<Foo>::ConstIterator& t)
			{
				t;
				return L"end()"s;
			}

			template <>
			inline std::wstring ToString<enum GameEngine::DatumTypes>(const enum GameEngine::DatumTypes& t)
			{
				t;
				return L"End()"s;
			}

			template <>
			inline std::wstring ToString<struct glm::vec<4,float>>(const struct glm::vec<4,float>& t)
			{
				t;
				return L"End()"s;
			}

			template <>
			inline std::wstring ToString<struct glm::mat<4,4,float>>(const struct glm::mat<4, 4,float>&t)
			{
				t;
				return L"End()"s;
			}
			template <>
			inline std::wstring ToString<GameEngine::RTTI>(GameEngine::RTTI*  t)
			{
				t;
				return L"End()"s;
			}

			template <>
			inline std::wstring ToString<GameEngine::Scope>(GameEngine::Scope* t)
			{
				t;
				return L"End()"s;
			}
			template <>
			inline std::wstring ToString<GameEngine::Scope>(const GameEngine::Scope* t)
			{
				t;
				return L"End()"s;
			}

			template <>
			inline std::wstring ToString<GameEngine::Datum>(const GameEngine::Datum& t)
			{
				t;
				return L"End()"s;
			}

			template <>
			inline std::wstring ToString<GameEngine::AttributedFoo>(const GameEngine::AttributedFoo& t)
			{
				t;
				return L"End()"s;
			}
			template <>
			inline std::wstring ToString<GameEngine::JsonIntegerParseHelper>(GameEngine::JsonIntegerParseHelper* t)
			{
				t;
				return L"End()"s;
			}
			template <>
			inline std::wstring ToString<GameEngine::JsonIntegerParseHelper::SharedData>(GameEngine::JsonIntegerParseHelper::SharedData* t)
			{
				t;
				return L"End()"s;
			}

			template <>
			inline std::wstring ToString<GameEngine::JsonParseCoordinator>(GameEngine::JsonParseCoordinator* t)
			{
				t;
				return L"End()"s;
			}

			template <>
			inline std::wstring ToString<GameEngine::TableParserHelper>(GameEngine::TableParserHelper* t)
			{
				t;
				return L"End()"s;
			}
			template <>
			inline std::wstring ToString<GameEngine::TableParserHelper::SharedData>(GameEngine::TableParserHelper::SharedData* t)
			{
				t;
				return L"End()"s;
			}

			template<>
			inline std::wstring ToString<FooFactory>(FooFactory* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<FooFactory>(const FooFactory* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<GameObject>( GameObject* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<Attributed>(Attributed* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<Avatar>(Avatar* t)
			{
				RETURN_WIDE_STRING(t);
			}
			template<>
			inline std::wstring ToString<Avatar>( const Avatar& t)
			{
				RETURN_WIDE_STRING(t.ToString().c_str());
			}

			template<>
			inline std::wstring ToString<Action>(const Action& t)
			{
				RETURN_WIDE_STRING(t.ToString().c_str());
			}

			template<>
			inline std::wstring ToString<Action>(Action* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<Action>(const Action* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionIncrement>(const ActionIncrement& t)
			{
				RETURN_WIDE_STRING(t.ToString().c_str());
			}

			template<>
			inline std::wstring ToString<ActionIncrement>(ActionIncrement* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionIncrement>(const ActionIncrement* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionCreateAction>(const ActionCreateAction& t)
			{
				RETURN_WIDE_STRING(t.ToString().c_str());
			}

			template<>
			inline std::wstring ToString<ActionCreateAction>(ActionCreateAction* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionCreateAction>(const ActionCreateAction* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionRemoveAction>(const ActionRemoveAction& t)
			{
				RETURN_WIDE_STRING(t.ToString().c_str());
			}

			template<>
			inline std::wstring ToString<ActionRemoveAction>(ActionRemoveAction* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionRemoveAction>(const ActionRemoveAction* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionList>(const ActionList& t)
			{
				RETURN_WIDE_STRING(t.ToString().c_str());
			}

			template<>
			inline std::wstring ToString<ActionList>(ActionList* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionList>(const ActionList* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionListIf>(const ActionListIf& t)
			{
				RETURN_WIDE_STRING(t.ToString().c_str());
			}

			template<>
			inline std::wstring ToString<ActionListIf>(ActionListIf* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<ActionListIf>(const ActionListIf* t)
			{
				RETURN_WIDE_STRING(t);
			}
			template<>
			inline std::wstring ToString<Event<Foo>>(Event<Foo>* t)
			{
				RETURN_WIDE_STRING(t);
			}

			template<>
			inline std::wstring ToString<IEventPublisher>(IEventPublisher* t)
			{
				RETURN_WIDE_STRING(t);
			}
		}
	}
}