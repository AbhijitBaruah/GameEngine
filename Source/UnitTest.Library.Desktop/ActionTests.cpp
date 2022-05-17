#include "pch.h"
#include "Foo.h"
#include "ToStringOverload.h"
#include "Factory.h"
#include "Avatar.h"
#include "ActionIncrement.h"
#include "ActionCreateAction.h"
#include "ActionRemoveAction.h"
#include "ActionList.h"
#include "GameState.h"
#include "ActionListIf.h"
#include "ActionExpression.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ActionTests)
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

		TEST_METHOD(ActionIncrementRTTI)
		{
			ActionIncrement action;

			RTTI* rtti = &action;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(ActionIncrement::TypeIdClass()));
			Assert::IsTrue(rtti->Is(Action::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(ActionIncrement::TypeIdClass(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			ActionIncrement* a = rtti->As<ActionIncrement>();
			Assert::IsNotNull(a);
			Assert::AreEqual(&action, a);
		}

		TEST_METHOD(ActionCreateActionRTTI)
		{
			ActionCreateAction action;

			RTTI* rtti = &action;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(ActionCreateAction::TypeIdClass()));
			Assert::IsTrue(rtti->Is(Action::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(ActionCreateAction::TypeIdClass(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			ActionCreateAction* a = rtti->As<ActionCreateAction>();
			Assert::IsNotNull(a);
			Assert::AreEqual(&action, a);
		}

		TEST_METHOD(ActionDestroyActionRTTI)
		{
			ActionRemoveAction action;

			RTTI* rtti = &action;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(ActionRemoveAction::TypeIdClass()));
			Assert::IsTrue(rtti->Is(Action::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(ActionRemoveAction::TypeIdClass(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);
		}

		TEST_METHOD(ActionListRTTI)
		{
			ActionList actionList;

			RTTI* rtti = &actionList;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(ActionList::TypeIdClass()));
			Assert::IsTrue(rtti->Is(Attributed::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(ActionList::TypeIdClass(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			ActionList* a = rtti->As<ActionList>();
			Assert::IsNotNull(a);
			Assert::AreEqual(&actionList, a);
		}

		TEST_METHOD(ActionListIfRTTI)
		{
			ActionListIf actionList;

			RTTI* rtti = &actionList;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(ActionListIf::TypeIdClass()));
			Assert::IsTrue(rtti->Is(ActionList::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(ActionListIf::TypeIdClass(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			ActionListIf* a = rtti->As<ActionListIf>();
			Assert::IsNotNull(a);
			Assert::AreEqual(&actionList, a);
		}

		TEST_METHOD(CloneToStringAndEquals)
		{
			{
				ActionListIf testObj;
				ActionList actionList;
				actionList.SetName("ActionListTest");
				ActionList* cloneList = actionList.Clone();
				Assert::IsTrue(actionList.Equals(cloneList));
				Assert::IsFalse(actionList.Equals(&testObj));
				Assert::AreEqual(std::string("ActionList"), actionList.ToString());
				delete cloneList;
			}
			{
				ActionList testObj;
				ActionListIf actionList;
				actionList.SetName("ActionListTest");
				actionList.Find("Condition")->Set(0);
				ActionListIf* cloneList = actionList.Clone();
				Assert::IsTrue(actionList.Equals(cloneList));
				Assert::IsFalse(actionList.Equals(&testObj));
				Assert::AreEqual(std::string("ActionListIF"), actionList.ToString());
				delete cloneList;
			}
			{

				ActionList testObj;
				ActionCreateAction actionList;
				actionList.SetName("ActionListTest");
				ActionCreateAction* cloneList = actionList.Clone();
				Assert::IsTrue(actionList.Equals(cloneList));
				Assert::IsFalse(actionList.Equals(&testObj));
				Assert::AreEqual(std::string("ActionCreateAction"), actionList.ToString());
				delete cloneList;
			}
			{

				ActionList testObj;
				ActionRemoveAction actionList;
				actionList.SetName("ActionListTest");
				ActionRemoveAction* cloneList = actionList.Clone();
				Assert::IsTrue(actionList.Equals(cloneList));
				Assert::IsFalse(actionList.Equals(&testObj));
				Assert::AreEqual(std::string("ActionRemoveAction"), actionList.ToString());
				delete cloneList;
			}

			{

				ActionList testObj;
				ActionIncrement actionList;
				actionList.SetName("ActionListTest");
				ActionIncrement* cloneList = actionList.Clone();
				Assert::IsTrue(actionList.Equals(cloneList));
				Assert::IsFalse(actionList.Equals(&testObj));
				Assert::AreEqual(std::string("ActionIncrement"), actionList.ToString());
				delete cloneList;
			}
		}
		TEST_METHOD(AllActions)
		{

			std::string filename = "../../../../../source/UnitTest.Library.Desktop/ActionJSON1.json";
			GameObject* rootScope = new GameObject;
			ScopeFactory scopeFactory;
			GameObjectFactory GameObjectFactory;
			AvatarFactory AvatarFactory;
			ActionIncrementFactory actionIncrementFactory;
			ActionCreateActionFactory acraction;
			ActionListIfFactory alifaction;
			TableParserHelper::SharedData sharedData(rootScope);
			TableParserHelper scopeParser;
			JsonParseCoordinator parseManager(sharedData);
			parseManager.AddHelper(scopeParser);
			parseManager.ParseFromFile(filename);
			GameTime g;
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Name")->Get<std::string>().c_str(), "avatar_1");
			Assert::IsNotNull(rootScope->Find("Children")->Get<Scope*>(0)->As<Avatar>());
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Power")->Get<float>(), 0.f);
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Size(), (std::size_t)1);
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Get<Scope*>()->Find("Name")->Get<std::string>().c_str(), "Action_If_1");
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Get<Scope*>()->Find("Actions")->Size(), (std::size_t)1);
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Get<Scope*>()->Find("Actions")->Get<Scope*>()->Find("Name")->Get<std::string>().c_str(), "ACA_1");
			rootScope->Update(g);
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Get<Scope*>()->Find("Actions")->Size(), (std::size_t)1);
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Get<Scope*>()->Find("Actions")->Get<Scope*>()->Find("Name")->Get<std::string>().c_str(), "ACA_1");
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Power")->Get<float>(), 0.f);
			GameState gs;
			gs.CreatePending();
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Size(), (std::size_t)2);
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Get<Scope*>(1)->Find("Name")->Get<std::string>().c_str(), "AInc_1");
			Assert::IsNotNull(rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Get<Scope*>(1)->As<ActionIncrement>());
			Datum& actIncTarget = *rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Get<Scope*>(1)->Find("Target");
			Datum& actIncStep = *rootScope->Find("Children")->Get<Scope*>(0)->Find("Actions")->Get<Scope*>(1)->Find("Step");
			actIncTarget.Set("Power");
			actIncStep.Set(100.f);
			rootScope->Update(g);
			Assert::AreEqual(rootScope->Find("Children")->Get<Scope*>(0)->Find("Power")->Get<float>(), 100.f);
			gs.CreatePending();

		}
		TEST_METHOD(ActionRemoveActionTest)
		{
			std::string filename = "../../../../../source/UnitTest.Library.Desktop/ActionJSON.json";
			GameTime g;
			GameObject* rootScope = new GameObject;
			GameObjectFactory GameObjectFactory;
			ActionCreateActionFactory acaf;
			TableParserHelper::SharedData sharedData(rootScope);
			TableParserHelper scopeParser;
			ActionListIfFactory aclif;
			JsonParseCoordinator parseManager(sharedData);
			ActionIncrementFactory actionIncrementFactory;
			ActionRemoveActionFactory acf;
			GameState gs;
			parseManager.AddHelper(scopeParser);
			parseManager.ParseFromFile(filename);
			Assert::AreEqual(rootScope->Find("Actions")->Get<Scope*>(0)->Find("Name")->Get<std::string>().c_str(), "ALif_1");
			Assert::AreEqual(rootScope->Find("Actions")->Get<Scope*>(1)->Find("Name")->Get<std::string>().c_str(), "ActRem_1");
			Assert::AreEqual(rootScope->Find("Health")->Get<std::int32_t>(), 100);
			rootScope->Update(g);
			Assert::AreEqual(rootScope->Find("Health")->Get<std::int32_t>(), 105);
			Assert::AreEqual((std::size_t)2, rootScope->Find("Actions")->Size());
			auto& nameDatum = *rootScope->Find("Actions")->Get<Scope*>(0)->Find("Name");
			Assert::AreEqual(nameDatum.Get<std::string>().c_str(), "ALif_1");
			Assert::AreEqual(rootScope->Find("Actions")->Get<Scope*>(1)->Find("Name")->Get<std::string>().c_str(), "ActRem_1");
			gs.RemovePending();
			Assert::AreEqual((std::size_t)1, rootScope->Find("Actions")->Size());
			Assert::AreEqual(rootScope->Find("Actions")->Get<Scope*>(0)->Find("Name")->Get<std::string>().c_str(), "ActRem_1");
			rootScope->Update(g);
			Assert::AreEqual(rootScope->Find("Health")->Get<std::int32_t>(), 105);

		}

		TEST_METHOD(ActionListTest)
		{
			std::string filename = "../../../../../source/UnitTest.Library.Desktop/ActionJSON2.json";
			GameTime g;
			GameObject* rootScope = new GameObject;
			GameObjectFactory GameObjectFactory;
			ActionListFactory acflist;
			TableParserHelper::SharedData sharedData(rootScope);
			TableParserHelper scopeParser;
			JsonParseCoordinator parseManager(sharedData);
			ActionIncrementFactory actionIncrementFactory;
			parseManager.AddHelper(scopeParser);
			parseManager.ParseFromFile(filename);
			Assert::AreEqual(rootScope->Find("Actions")->Get<Scope*>(0)->Find("Name")->Get<std::string>().c_str(), "AList_1");
			Assert::AreEqual(rootScope->Find("Power")->Get<float>(), 10.f);
			rootScope->Update(g);
			Assert::AreEqual(rootScope->Find("Power")->Get<float>(), 0.f);
		}

		TEST_METHOD(CreateAction)
		{
			{
				ActionIncrementFactory fac;
				ActionList list;
				Assert::AreEqual(list.Actions().Size(), (std::size_t)0);
				std::string className = "ActionIncrement";
				std::string instanceName = "AInc_1";
				list.CreateAction(className, instanceName);
				Assert::AreEqual(list.Actions().Size(), (std::size_t)1);
			}
			{
				GameObject obj;
				ActionIncrementFactory fac;
				Assert::AreEqual(obj.Actions().Size(), (std::size_t)0);
				std::string className = "ActionIncrement";
				std::string instanceName = "AInc_1";
				obj.CreateAction(className, instanceName);
				Assert::AreEqual(obj.Actions().Size(), (std::size_t)1);

			}



		}

		TEST_METHOD(ActionExpression)
		{
			std::string filename = "../../../../../source/UnitTest.Library.Desktop/ActionJSON3.json";
			ActionExpressionFactory factory;
			GameTime g;
			GameObject* rootScope = new GameObject;
			GameObjectFactory GameObjectFactory;
			TableParserHelper::SharedData sharedData(rootScope);
			TableParserHelper scopeParser;
			JsonParseCoordinator parseManager(sharedData);
			parseManager.AddHelper(scopeParser);
			parseManager.ParseFromFile(filename);
			Assert::AreEqual("AExpr", rootScope->Find("Actions")->Get<Scope*>()->Find("Name")->Get<std::string>().c_str());
			rootScope->Update(g);
			Assert::AreEqual("90.000000", rootScope->Find("Actions")->Get<Scope*>()->Find("Expression")->Get<std::string>().c_str());

		}
	private:
		static _CrtMemState _startMemState;


	};
	_CrtMemState ActionTests::_startMemState;
}
