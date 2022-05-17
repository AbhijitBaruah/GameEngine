#include "pch.h"
#include "JsonParseCoordinator.h"
#include "JsonIntegerParseHelper.h"
#include <string.h>
#include "ToStringOverload.h"
#include "TableParserHelper.h"
#include "AttributedFoo.h"
#include "Scope.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(TableJsonParseTests)
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

		TEST_METHOD(TableParserseHelperRTTI)
		{
			TableParserHelper helper;

			RTTI* rtti = &helper;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(IJsonParseHelper::TypeIdClass()));
			Assert::IsTrue(rtti->Is(TableParserHelper::TypeIdClass()));
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(TableParserHelper::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(TableParserHelper::TypeIdClass(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			TableParserHelper* h = rtti->As<TableParserHelper>();
			Assert::IsNotNull(h);
			Assert::AreEqual(&helper, h);
		}

		TEST_METHOD(TableParseHelperSharedDataRTTI)
		{
			TableParserHelper::SharedData sharedData;

			RTTI* rtti = &sharedData;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(TableParserHelper::SharedData::TypeIdClass()));
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(TableParserHelper::SharedData::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(TableParserHelper::SharedData::TypeIdClass(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			TableParserHelper::SharedData* h = rtti->As<TableParserHelper::SharedData>();
			Assert::IsNotNull(h);
			Assert::AreEqual(&sharedData, h);
		}

		TEST_METHOD(Constructor)
		{
			TableParserHelper::SharedData sharedData;
			JsonParseCoordinator parseCoordinator(sharedData);
			Assert::IsFalse(parseCoordinator.IsClone());
			Assert::AreEqual(size_t(0), parseCoordinator.GetParseHelpers().Size());
			Assert::AreEqual(&sharedData, parseCoordinator.GetSharedData()->As<TableParserHelper::SharedData>());

			TableParserHelper testParseHelper;
			parseCoordinator.AddHelper(testParseHelper);
			Assert::AreEqual(size_t(1), parseCoordinator.GetParseHelpers().Size());

			Assert::AreEqual(&sharedData, parseCoordinator.GetSharedData()->As<TableParserHelper::SharedData>());
			Assert::AreEqual(&parseCoordinator, sharedData.GetJsonParseCoordinator());

			TableParserHelper::SharedData anotherSharedData;
			parseCoordinator.SetSharedData(&anotherSharedData);
			Assert::AreEqual(&anotherSharedData, parseCoordinator.GetSharedData()->As<TableParserHelper::SharedData>());
		}


		TEST_METHOD(AllTypesOfParsing)
		{
			{
				ScopeFactory scopeFactory;
				std::string filename = "../../../../../source/UnitTest.Library.Desktop/TestJson1.json";
				TableParserHelper::SharedData sharedData;
				JsonParseCoordinator parseCoordinator(sharedData);
				Assert::AreEqual(size_t(0), parseCoordinator.GetParseHelpers().Size());
				Assert::AreEqual(&sharedData, parseCoordinator.GetSharedData()->As<TableParserHelper::SharedData>());
				TableParserHelper testParseHelper;
				Assert::IsTrue(testParseHelper.isInitialized);
				parseCoordinator.AddHelper(testParseHelper);
				Assert::AreEqual(size_t(1), parseCoordinator.GetParseHelpers().Size());
				Assert::AreEqual(std::size_t(0), sharedData.Depth());
				Assert::IsNull(sharedData._root->Find("Name"));
				Assert::IsNull(sharedData._root->Find("Health"));
				Assert::IsNull(sharedData._root->Find("Damage")); \
				Assert::IsNull(sharedData._root->Find("Direction"));
				Assert::IsNull(sharedData._root->Find("Transform"));
				Assert::IsNull(sharedData._root->Find("Address"));
				Assert::IsNull(sharedData._root->Find("Aliases"));
				parseCoordinator.ParseFromFile(filename);
				Assert::AreEqual(std::size_t(0), sharedData.Depth());
				Assert::IsNotNull(sharedData._root->Find("Name"));
				Assert::IsNotNull(sharedData._root->Find("Health"));
				Assert::IsNotNull(sharedData._root->Find("Damage"));
				Assert::IsNotNull(sharedData._root->Find("Direction"));
				Assert::IsNotNull(sharedData._root->Find("Transform"));
				Assert::IsNotNull(sharedData._root->Find("Address"));
				Assert::IsNotNull(sharedData._root->Find("Aliases"));
				Assert::AreEqual(sharedData._root->Find("Name")->Get<std::string>(0).c_str(), "Test");
				Assert::AreEqual(sharedData._root->Find("Health")->Get<std::int32_t>(0), (std::int32_t)100);
				Assert::AreEqual(sharedData._root->Find("Aliases")->Get<std::string>(0).c_str(), "Bob");
				Assert::AreEqual(sharedData._root->Find("Aliases")->Get<std::string>(1).c_str(), "Jim");
				Assert::AreEqual(sharedData._root->Find("Aliases")->Get<std::string>(2).c_str(), "Fred");
				Assert::AreEqual(sharedData._root->Find("Damage")->Get<float>(0), (float)100.0);
				glm::vec4 dirVec4{ 1,0,0,1 };
				Assert::AreEqual(sharedData._root->Find("Direction")->Get<glm::vec4>(0), dirVec4);
				glm::mat4 transformmat4{ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
				Assert::AreEqual(sharedData._root->Find("Transform")->Get<glm::mat4>(0), transformmat4);
				Assert::AreEqual(sharedData._root->Find("Address")->Get<Scope*>(0)->Find("City")->Get<std::string>(0).c_str(), "Orlando");
				Assert::AreEqual(sharedData._root->Find("Address")->Get<Scope*>(0)->Find("Street")->Get<std::string>(0).c_str(), "123 Anystreet St.");
				Assert::AreEqual(sharedData._root->Find("Address")->Get<Scope*>(0)->Find("Postal Code")->Get<Scope*>(0)->Find("Zip Code")->Get<std::int32_t>(), (std::int32_t)12345);
				Assert::AreEqual(sharedData._root->Find("Address")->Get<Scope*>(0)->Find("Postal Code")->Get<Scope*>(0)->Find("Zip Code+4")->Get<std::int32_t>(), (std::int32_t)6789);
			}
			{
				// A JSON file that has an array of scopes
				ScopeFactory scopeFactory;
				std::string filename = "../../../../../source/UnitTest.Library.Desktop/TestJson.json";
				TableParserHelper::SharedData sharedData;
				JsonParseCoordinator parseCoordinator(sharedData);
				Assert::AreEqual(size_t(0), parseCoordinator.GetParseHelpers().Size());
				Assert::AreEqual(&sharedData, parseCoordinator.GetSharedData()->As<TableParserHelper::SharedData>());
				TableParserHelper testParseHelper;
				Assert::IsTrue(testParseHelper.isInitialized);
				parseCoordinator.AddHelper(testParseHelper);
				Assert::AreEqual(size_t(1), parseCoordinator.GetParseHelpers().Size());
				Assert::AreEqual(std::size_t(0), sharedData.Depth());
				parseCoordinator.ParseFromFile(filename);
				Assert::IsNotNull(sharedData._root->Find("AHealth"));
				Assert::IsNotNull(sharedData._root->Find("BTransform"));
				Assert::IsNotNull(sharedData._root->Find("CWeapon"));
				Assert::AreEqual(sharedData._root->Find("CWeapon")->Get<Scope*>()->Find("BRanged")->Get<Scope*>()->Find("AShotgun")->Get<Scope*>(0)->Find("Aid")->Get<std::int32_t>(0), (std::int32_t)5);
				Assert::AreEqual(sharedData._root->Find("CWeapon")->Get<Scope*>()->Find("BRanged")->Get<Scope*>()->Find("AShotgun")->Get<Scope*>(0)->Find("Aid")->Get<std::int32_t>(1), (std::int32_t)6);
				Assert::AreEqual(sharedData._root->Find("CWeapon")->Get<Scope*>()->Find("BRanged")->Get<Scope*>()->Find("AShotgun")->Get<Scope*>(0)->Find("Aid")->Get<std::int32_t>(2), (std::int32_t)9);
				Assert::AreEqual(sharedData._root->Find("CWeapon")->Get<Scope*>()->Find("BRanged")->Get<Scope*>()->Find("AShotgun")->Get<Scope*>(1)->Find("Aid")->Get<std::int32_t>(0), (std::int32_t)4);
				Assert::AreEqual(sharedData._root->Find("CWeapon")->Get<Scope*>()->Find("BRanged")->Get<Scope*>()->Find("AShotgun")->Get<Scope*>(1)->Find("Aid")->Get<std::int32_t>(1), (std::int32_t)1);
				Assert::AreEqual(sharedData._root->Find("CWeapon")->Get<Scope*>()->Find("BRanged")->Get<Scope*>()->Find("AShotgun")->Get<Scope*>(1)->Find("Aid")->Get<std::int32_t>(2), (std::int32_t)7);

			}


		}
		


	private:
		static _CrtMemState _startMemState;

	};
	_CrtMemState TableJsonParseTests::_startMemState;
}




