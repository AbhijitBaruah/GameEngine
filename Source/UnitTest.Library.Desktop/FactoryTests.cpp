#include "pch.h"
#include "Foo.h"
#include "ToStringOverload.h"
#include "Factory.h"
#include "Avatar.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(FactoryTests)
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
		TEST_METHOD(ProductCreationAndAdding)
		{
			RTTI* rtti = Factory<RTTI>::Create("Foo");
			Assert::IsNull(rtti);
			{
				FooFactory fooFctory;
				rtti = Factory<RTTI>::Create("Foo");
				Assert::IsNotNull(rtti);
				Foo* foo = rtti->As<Foo>();
				Assert::IsNotNull(foo);
				delete foo;
			}

			rtti = Factory<RTTI>::Create("Foo");
			Assert::IsNull(rtti);

			
		}

		TEST_METHOD(AddRemoveFactory)
		{
			const Factory<RTTI>* foundFactory = Factory<RTTI>::Find("Foo"s);
			Assert::IsNull(foundFactory);

			{
				const FooFactory fooFactory;
				foundFactory = Factory<RTTI>::Find("Foo"s);
				Assert::AreEqual(&fooFactory, static_cast<const FooFactory*>(foundFactory));
			}

			foundFactory = Factory<RTTI>::Find("Foo"s);
			Assert::IsNull(foundFactory);
			FooFactory f1;
			Assert::ExpectException<std::runtime_error>([] {FooFactory f1; });
		}
		TEST_METHOD(AttributedFooTest)
		{
			{
				std::string filename = "../../../../../source/UnitTest.Library.Desktop/TestJson2.json";


				TableParserHelper::SharedData sharedData;

				TableParserHelper scopeParser;

				JsonParseCoordinator parseManager(sharedData);
				parseManager.AddHelper(scopeParser);

				AttributedFooFactory fooFactory;
				ScopeFactory scopeFactory;

				parseManager.ParseFromFile(filename);

				Datum* cWeapon = sharedData._root->Find("CWeapon");
				Assert::IsNotNull(cWeapon);

				AttributedFoo* foo = cWeapon->Get<Scope*>()->As<AttributedFoo>();
				Assert::IsNotNull(foo);

				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalInteger"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalFloat"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalString"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalMatrix"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalVector"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalIntegerArray"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalFloatArray"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalMatrixArray"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalVectorArray"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalStringArray"));
				Assert::IsTrue(foo->IsAuxillaryAttribute("ASelectedWeapon"));
				Assert::IsTrue(foo->IsAuxillaryAttribute("GMelee"));
			}
			{
				std::string filename = "../../../../../source/UnitTest.Library.Desktop/TestJson3.json";


				TableParserHelper::SharedData sharedData;

				TableParserHelper scopeParser;

				JsonParseCoordinator parseManager(sharedData);
				parseManager.AddHelper(scopeParser);

				AttributedFooFactory fooFactory;
				ScopeFactory scopeFactory;

				parseManager.ParseFromFile(filename);

				Datum* cWeapon = sharedData._root->Find("CWeapon");
				Assert::IsNotNull(cWeapon);

				AttributedFoo* foo = cWeapon->Get<Scope*>()->As<AttributedFoo>();
				Assert::IsNotNull(foo);

				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalInteger"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalFloat"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalString"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalMatrix"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalVector"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalIntegerArray"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalFloatArray"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalMatrixArray"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalVectorArray"));
				Assert::IsTrue(foo->IsPrescribedAttribute("ExternalStringArray"));
				Assert::IsTrue(foo->IsAuxillaryAttribute("GMelee"));
				/*Assert::AreEqual(sharedData._root->Find("CWeapon")->Get<Scope*>()->As<AttributedFoo>()->Find("ExternalIntegerArray")->Get<std::int32_t>(0), 1);
				Assert::AreEqual(sharedData._root->Find("CWeapon")->Get<Scope*>()->As<AttributedFoo>()->Find("ExternalIntegerArray")->Get<std::int32_t>(1), 2);
				Assert::AreEqual(sharedData._root->Find("CWeapon")->Get<Scope*>()->As<AttributedFoo>()->Find("ExternalIntegerArray")->Get<std::int32_t>(2), 3);*/
			}


		}

	


		
	private:
		static _CrtMemState _startMemState;


	};
	_CrtMemState FactoryTests::_startMemState;
}




