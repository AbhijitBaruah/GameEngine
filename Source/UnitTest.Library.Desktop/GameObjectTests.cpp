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
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(GameObjectTests)
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



		TEST_METHOD(RTTITest)
		{
			{
				GameObject obj;
				RTTI* rtti = &obj;
				Assert::IsFalse(rtti->Is(AttributedFoo::TypeIdClass()));
				Assert::IsTrue(rtti->Is(Attributed::TypeIdClass()));
				Assert::IsTrue(rtti->Is(Scope::TypeIdClass()));
				Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
				Assert::AreEqual(GameObject::TypeIdClass(), rtti->TypeIdInstance());
				GameObject* f = rtti->As<GameObject>();
				Assert::IsNotNull(f);
				Assert::AreEqual(&obj, f);
				Attributed* fAsAttributed = rtti->As<Attributed>();
				Assert::IsNotNull(fAsAttributed);
				Assert::AreEqual(static_cast<Attributed*>(&obj), fAsAttributed);
			}
			{
				Avatar obj;
				RTTI* rtti = &obj;
				Assert::IsFalse(rtti->Is(AttributedFoo::TypeIdClass()));
				Assert::IsTrue(rtti->Is(Attributed::TypeIdClass()));
				Assert::IsTrue(rtti->Is(Scope::TypeIdClass()));
				Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
				Assert::IsTrue(rtti->Is(GameObject::TypeIdClass()));
				Assert::AreEqual(Avatar::TypeIdClass(), rtti->TypeIdInstance());
				Avatar* f = rtti->As<Avatar>();
				Assert::IsNotNull(f);
				Assert::AreEqual(&obj, f);
				Attributed* fAsAttributed = rtti->As<Attributed>();
				Assert::IsNotNull(fAsAttributed);
				Assert::AreEqual(static_cast<Attributed*>(&obj), fAsAttributed);
			}


		}

		TEST_METHOD(GameObjectJson)
		{

			std::string filename = "../../../../../source/UnitTest.Library.Desktop/TestJson5.json";
			GameObject* rootScope = new GameObject;
			GameObjectFactory GameObjectFactory;
			TableParserHelper::SharedData sharedData(rootScope);
			ScopeFactory scopeFactory;
			TableParserHelper scopeParser;
			JsonParseCoordinator parseManager(sharedData);
			parseManager.AddHelper(scopeParser);
			AvatarFactory AvatarFactory;
			parseManager.ParseFromFile(filename);
			Assert::AreEqual("root_scene", sharedData._root->Find("Name")->Get<std::string>(0).c_str());
			Assert::IsNotNull(sharedData._root->As<GameObject>());
			Assert::AreEqual(sharedData._root->As<GameObject>(), rootScope);
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(0)->Find("Name")->Get<std::string>(0).c_str(), "c1_0");
			Assert::IsNotNull(sharedData._root->Find("Children")->Get<Scope*>(0)->As<Avatar>());
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(0)->Find("Children")->Get<Scope*>(0)->Find("Name")->Get<std::string>(0).c_str(), "c1_1");
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Name")->Get<std::string>(0).c_str(), "c2_0");
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(0)->Find("Name")->Get<std::string>(0).c_str(), "c2_1");
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("Name")->Get<std::string>(0).c_str(), "c2_2");
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(0)->Find("Name")->Get<std::string>(0).c_str(), "c2_2_0");
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("NOTCHILDREN")->Get<Scope*>(0)->Find("Name")->Get<std::string>(0).c_str(), "nc2_2_0");
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("NOTCHILDREN")->Get<Scope*>(1)->Find("Name")->Get<std::string>(0).c_str(), "nc2_2_1");
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("NOTCHILDREN")->Get<Scope*>(2)->Find("Name")->Get<std::string>(0).c_str(), "nc2_2_2");

		}

		TEST_METHOD(GameObjectUpdate)
		{
			std::string filename = "../../../../../source/UnitTest.Library.Desktop/TestJson5.json";
			GameObject* rootScope = new GameObject;
			GameObjectFactory GameObjectFactory;
			TableParserHelper::SharedData sharedData(rootScope);
			ScopeFactory scopeFactory;
			TableParserHelper scopeParser;
			JsonParseCoordinator parseManager(sharedData);
			parseManager.AddHelper(scopeParser);
			AvatarFactory AvatarFactory;
			parseManager.ParseFromFile(filename);
			Assert::IsNotNull(sharedData._root->As<GameObject>());
			auto& rootGameObj = *sharedData._root->As<GameObject>();
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(0)->Find("Health")->Get<std::int32_t>(0), 10);
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("Health")->Get<std::int32_t>(0), 100);
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(0)->Find("Health")->Get<std::int32_t>(0), 50);
			GameTime g;
			rootGameObj.Update(g);
			Assert::AreEqual(9, sharedData._root->Find("Children")->Get<Scope*>(0)->Find("Health")->Get<std::int32_t>(0));
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("Health")->Get<std::int32_t>(0), 99);
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(0)->Find("Health")->Get<std::int32_t>(0), 49);
			rootGameObj.Update(g);
			Assert::AreEqual(8, sharedData._root->Find("Children")->Get<Scope*>(0)->Find("Health")->Get<std::int32_t>(0));
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("Health")->Get<std::int32_t>(0), 98);
			Assert::AreEqual(sharedData._root->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(1)->Find("Children")->Get<Scope*>(0)->Find("Health")->Get<std::int32_t>(0), 48);
		}

		TEST_METHOD(CloneTest)
		{
			GameObject gameObject;
			GameObject& cloneGO = *(gameObject.Clone());
			Assert::IsTrue(gameObject.Equals(&cloneGO));
			Assert::IsTrue(cloneGO.Is(GameObject::TypeIdClass()));
			delete& cloneGO;

			Avatar avatar;
			Avatar& cloneA = *(avatar.Clone());
			Assert::IsTrue(avatar.Equals(&cloneA));
			Assert::IsTrue(avatar.Is(Avatar::TypeIdClass()));
			delete& cloneA;
		}


		/*TEST_METHOD(Blah)
		{
			std::string filename = "../../../../../source/UnitTest.Library.Desktop/ActionJSON.json";
			GameObject* rootScope = new GameObject;
			GameObjectFactory GameObjectFactory;
			ActionIncrementFactory actionIncrementFactory;
			TableParserHelper::SharedData sharedData(rootScope);
			ScopeFactory scopeFactory;
			TableParserHelper scopeParser;
			JsonParseCoordinator parseManager(sharedData);
			parseManager.AddHelper(scopeParser);
			AvatarFactory AvatarFactory;
			parseManager.ParseFromFile(filename);
			Assert::IsNotNull(sharedData._root->Find("health"));
			Assert::AreEqual(100, sharedData._root->Find("health")->Get<std::int32_t>());
			GameTime g;
			rootScope->Update(g);
			Assert::AreEqual(101, sharedData._root->Find("health")->Get<std::int32_t>());
		}*/
		/*TEST_METHOD(BlahBlah)
		{
			std::string filename = "../../../../../source/UnitTest.Library.Desktop/ActionJSON.json";
			GameTime g;
			GameObject* rootScope = new GameObject;
			GameState gs;
			GameObjectFactory GameObjectFactory;
			ActionCreateActionFactory acaf;
			TableParserHelper::SharedData sharedData(rootScope);
			TableParserHelper scopeParser;
			JsonParseCoordinator parseManager(sharedData);
			ActionIncrementFactory actionIncrementFactory;
			parseManager.AddHelper(scopeParser);
			parseManager.ParseFromFile(filename);
			Assert::AreEqual((std::size_t)1, rootScope->Find("Actions")->Size());
			rootScope->Update(g);
			Assert::AreEqual((std::size_t)1, rootScope->Find("Actions")->Size());
			gs.CreatePending();
			Assert::AreEqual((std::size_t)2, rootScope->Find("Actions")->Size());
			Assert::AreEqual("AI_1", rootScope->Find("Actions")->Get<Scope*>(1)->Find("Name")->Get<std::string>().c_str());

		}*/

		//TEST_METHOD(BlahBlahBlah)
		//{
		//	std::string filename = "../../../../../source/UnitTest.Library.Desktop/ActionJSON.json";
		//	GameTime g;
		//	GameObject* rootScope = new GameObject;
		//	//GameState gs;
		//	GameObjectFactory GameObjectFactory;
		//	ActionCreateActionFactory acaf;
		//	TableParserHelper::SharedData sharedData(rootScope);
		//	TableParserHelper scopeParser;
		//	ActionListIfFactory aclif;
		//	JsonParseCoordinator parseManager(sharedData);
		//	ActionIncrementFactory actionIncrementFactory;
		//	parseManager.AddHelper(scopeParser);
		//	parseManager.ParseFromFile(filename);
		//	Assert::AreEqual(rootScope->Find("Actions")->Get<Scope*>(0)->Find("Name")->Get<std::string>().c_str(), "AListIf_1");
		//	Assert::AreEqual(rootScope->Find("Health")->Get<std::int32_t>(),100);
		//	rootScope->Update(g);
		//	Assert::AreEqual(rootScope->Find("Health")->Get<std::int32_t>(), 105);
		//	Assert::AreEqual((std::size_t)1, rootScope->Find("Actions")->Size());
		//   Datum& conditionDatum = *rootScope->Find("Actions")->Get<Scope*>(0)->Find("Condition");
		//   conditionDatum.Set(1);
		//	rootScope->Update(g);
		//	Assert::AreEqual(rootScope->Find("Health")->Get<std::int32_t>(), 100);
		//}

		TEST_METHOD(BlahBlahBlahBlah)
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
		}
	private:
		static _CrtMemState _startMemState;


	};
	_CrtMemState GameObjectTests::_startMemState;
}




