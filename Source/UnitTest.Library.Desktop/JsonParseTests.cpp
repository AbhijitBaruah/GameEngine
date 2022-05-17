#include "pch.h"
#include "JsonParseCoordinator.h"
#include "JsonIntegerParseHelper.h"
#include <string.h>
#include "ToStringOverload.h"
#include "TableParserHelper.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(JsonParseTests)
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

		TEST_METHOD(JsonTestParseHelperRTTI)
		{
			JsonIntegerParseHelper helper;

			RTTI* rtti = &helper;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(IJsonParseHelper::TypeIdClass()));
			Assert::IsTrue(rtti->Is(JsonIntegerParseHelper::TypeIdClass()));
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(JsonIntegerParseHelper::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(JsonIntegerParseHelper::TypeIdClass(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			JsonIntegerParseHelper* h = rtti->As<JsonIntegerParseHelper>();
			Assert::IsNotNull(h);
			Assert::AreEqual(&helper, h);
		}

		TEST_METHOD(JsonTestParseHelperSharedDataRTTI)
		{
			JsonIntegerParseHelper::SharedData sharedData;

			RTTI* rtti = &sharedData;
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(JsonIntegerParseHelper::SharedData::TypeIdClass()));
			Assert::IsFalse(rtti->Is(Foo::TypeIdClass()));
			Assert::IsTrue(rtti->Is(JsonIntegerParseHelper::SharedData::TypeIdClass()));
			Assert::IsTrue(rtti->Is(rtti->TypeIdInstance()));
			Assert::AreEqual(JsonIntegerParseHelper::SharedData::TypeIdClass(), rtti->TypeIdInstance());

			Foo* f = rtti->As<Foo>();
			Assert::IsNull(f);

			JsonIntegerParseHelper::SharedData* h = rtti->As<JsonIntegerParseHelper::SharedData>();
			Assert::IsNotNull(h);
			Assert::AreEqual(&sharedData, h);
		}

		TEST_METHOD(Constructor)
		{
			JsonIntegerParseHelper::SharedData sharedData;
			JsonParseCoordinator parseCoordinator(sharedData);
			Assert::IsFalse(parseCoordinator.IsClone());
			Assert::AreEqual(size_t(0), parseCoordinator.GetParseHelpers().Size());
			Assert::AreEqual(&sharedData, parseCoordinator.GetSharedData()->As<JsonIntegerParseHelper::SharedData>());

			JsonIntegerParseHelper testParseHelper;
			parseCoordinator.AddHelper(testParseHelper);
			Assert::AreEqual(size_t(1), parseCoordinator.GetParseHelpers().Size());

			Assert::AreEqual(&sharedData, parseCoordinator.GetSharedData()->As<JsonIntegerParseHelper::SharedData>());
			Assert::AreEqual(&parseCoordinator, sharedData.GetJsonParseCoordinator());

			JsonIntegerParseHelper::SharedData anotherSharedData;
			parseCoordinator.SetSharedData(&anotherSharedData);
			Assert::AreEqual(&anotherSharedData, parseCoordinator.GetSharedData()->As<JsonIntegerParseHelper::SharedData>());
		}

		TEST_METHOD(IntegerParsing)
		{
			std::string inputString = R"({"integer":100})";
			JsonIntegerParseHelper::SharedData sharedData;
			JsonIntegerParseHelper integerParseHelper;
			Assert::IsFalse(integerParseHelper.isInitialized);
			integerParseHelper.Initialize();
			Assert::IsTrue(integerParseHelper.isInitialized);
			JsonParseCoordinator parseCoordinator(sharedData);
			parseCoordinator.AddHelper(integerParseHelper);
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetEndHandlerCount());
			Assert::AreEqual((size_t)0, sharedData.MaxDepth());
			Assert::AreEqual((size_t)0, sharedData.Depth());
			parseCoordinator.Parse(inputString);
			Assert::AreEqual((std::size_t)1, sharedData.Data.Size());
			Assert::AreEqual(100, sharedData.Data.Front());
			Assert::AreEqual((std::size_t)1, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)1, integerParseHelper.GetEndHandlerCount());
			Assert::AreEqual((size_t)0, sharedData.Depth());
			Assert::AreEqual((size_t)1, sharedData.MaxDepth());
		}
		TEST_METHOD(ParseFromFile)
		{
			std::string filename = "Test.json";
			std::string inputString = R"({
				 "integer": 100,
				"child" : {
				"integer": 200,
				"anotherChild":{
				"integer": [77, 78, 80]
						}
				  }
			})";
			std::ofstream outputFile(filename);
			Assert::IsTrue(outputFile.good());
			outputFile << inputString;
			outputFile.close();
			JsonIntegerParseHelper::SharedData sharedData;
			JsonIntegerParseHelper integerParseHelper;
			JsonParseCoordinator parseCoordinator(sharedData);
			Assert::IsFalse(integerParseHelper.isInitialized);
			integerParseHelper.Initialize();
			Assert::IsTrue(integerParseHelper.isInitialized);
			parseCoordinator.AddHelper(integerParseHelper);
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetEndHandlerCount());
			Assert::AreEqual((size_t)0, sharedData.MaxDepth());
			Assert::AreEqual((size_t)0, sharedData.Depth());
			parseCoordinator.ParseFromFile(filename);
			Assert::AreEqual((std::size_t)5, sharedData.Data.Size());
			Assert::AreEqual(77, sharedData.Data[0]);
			Assert::AreEqual(78, sharedData.Data[1]);
			Assert::AreEqual(80, sharedData.Data[2]);
			Assert::AreEqual(200, sharedData.Data[3]);
			Assert::AreEqual(100, sharedData.Data[4]);
			Assert::AreEqual((size_t)0, sharedData.Depth());
			Assert::AreEqual((size_t)3, sharedData.MaxDepth());
			Assert::AreEqual((std::size_t)5, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)5, integerParseHelper.GetEndHandlerCount());
		}
		TEST_METHOD(IntegerArrayParsing)
		{
			std::string inputString = R"({"integer":[10,20,30,40]})";
			JsonIntegerParseHelper::SharedData sharedData;
			JsonIntegerParseHelper integerParseHelper;
			JsonParseCoordinator parseCoordinator(sharedData);
			parseCoordinator.AddHelper(integerParseHelper);
			Assert::IsFalse(integerParseHelper.isInitialized);
			integerParseHelper.Initialize();
			Assert::IsTrue(integerParseHelper.isInitialized);
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetEndHandlerCount());
			Assert::AreEqual((size_t)0, sharedData.MaxDepth());
			Assert::AreEqual((size_t)0, sharedData.Depth());
			parseCoordinator.Parse(inputString);
			Assert::AreEqual((std::size_t)4, sharedData.Data.Size());
			Assert::AreEqual(10, sharedData.Data[0]);
			Assert::AreEqual(20, sharedData.Data[1]);
			Assert::AreEqual(30, sharedData.Data[2]);
			Assert::AreEqual(40, sharedData.Data[3]);
			Assert::AreEqual((std::size_t)4, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)4, integerParseHelper.GetEndHandlerCount());
			Assert::AreEqual((size_t)0, sharedData.Depth());
			Assert::AreEqual((size_t)1, sharedData.MaxDepth());
		}

		TEST_METHOD(ObjectArrayParsing)
		{
			std::string inputString = R"({
				 "integer": 100,
				"child" : {
				"integer": 200,
				"anotherChild":{
				"integer": [77, 78, 80]
						}
				  }
			})";
			JsonIntegerParseHelper::SharedData sharedData;
			JsonIntegerParseHelper integerParseHelper;
			JsonParseCoordinator parseCoordinator(sharedData);
			Assert::IsFalse(integerParseHelper.isInitialized);
			integerParseHelper.Initialize();
			Assert::IsTrue(integerParseHelper.isInitialized);
			parseCoordinator.AddHelper(integerParseHelper);
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetEndHandlerCount());
			Assert::AreEqual((size_t)0, sharedData.MaxDepth());
			Assert::AreEqual((size_t)0, sharedData.Depth());
			parseCoordinator.Parse(inputString);
			Assert::AreEqual((std::size_t)5, sharedData.Data.Size());
			Assert::AreEqual(77, sharedData.Data[0]);
			Assert::AreEqual(78, sharedData.Data[1]);
			Assert::AreEqual(80, sharedData.Data[2]);
			Assert::AreEqual(200, sharedData.Data[3]);
			Assert::AreEqual(100, sharedData.Data[4]);
			Assert::AreEqual((size_t)0, sharedData.Depth());
			Assert::AreEqual((size_t)3, sharedData.MaxDepth());
			Assert::AreEqual((std::size_t)5, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)5, integerParseHelper.GetEndHandlerCount());
		}

		TEST_METHOD(Clone)
		{
			std::string inputString = R"({"integer":[10,20,30,40]})";
			JsonIntegerParseHelper::SharedData sharedData;
			JsonIntegerParseHelper integerParseHelper;
			JsonParseCoordinator parseCoordinator(sharedData);
			Assert::IsFalse(integerParseHelper.isInitialized);
			integerParseHelper.Initialize();
			Assert::IsTrue(integerParseHelper.isInitialized);
			parseCoordinator.AddHelper(integerParseHelper);
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)0, integerParseHelper.GetEndHandlerCount());
			Assert::AreEqual((size_t)0, sharedData.MaxDepth());
			Assert::AreEqual((size_t)0, sharedData.Depth());
			parseCoordinator.Parse(inputString);
			Assert::AreEqual((std::size_t)4, sharedData.Data.Size());
			Assert::AreEqual(10, sharedData.Data[0]);
			Assert::AreEqual(20, sharedData.Data[1]);
			Assert::AreEqual(30, sharedData.Data[2]);
			Assert::AreEqual(40, sharedData.Data[3]);
			Assert::AreEqual((std::size_t)4, integerParseHelper.GetStartHandlerCount());
			Assert::AreEqual((std::size_t)4, integerParseHelper.GetEndHandlerCount());
			Assert::AreEqual((size_t)0, sharedData.Depth());
			Assert::AreEqual((size_t)1, sharedData.MaxDepth());
			JsonParseCoordinator& clonedCoordinator = *parseCoordinator.Clone();
			Assert::ExpectException<std::runtime_error>([&clonedCoordinator, &integerParseHelper] {clonedCoordinator.AddHelper(integerParseHelper); });
			auto clonedSharedData = reinterpret_cast<JsonIntegerParseHelper::SharedData*>(clonedCoordinator.GetSharedData());
			Assert::IsNotNull(clonedSharedData);
			Assert::AreEqual((size_t)0, clonedSharedData->MaxDepth());
			Assert::AreEqual((size_t)0, clonedSharedData->Depth());
			clonedCoordinator.Parse(inputString);
			Assert::AreEqual((std::size_t)4, clonedSharedData->Data.Size());
			Assert::AreEqual(10, clonedSharedData->Data[0]);
			Assert::AreEqual(20, clonedSharedData->Data[1]);
			Assert::AreEqual(30, clonedSharedData->Data[2]);
			Assert::AreEqual(40, clonedSharedData->Data[3]);
			Assert::AreEqual((size_t)1, clonedSharedData->MaxDepth());
			Assert::AreEqual((size_t)0, clonedSharedData->Depth());
			delete& clonedCoordinator;
		}

		TEST_METHOD(AddAndRemoveHelpers)
		{
			JsonIntegerParseHelper::SharedData sharedData;
			JsonIntegerParseHelper integerParseHelper;
			Assert::IsFalse(integerParseHelper.isInitialized);
			integerParseHelper.Initialize();
			Assert::IsTrue(integerParseHelper.isInitialized);
			JsonParseCoordinator parseCoordinator(sharedData);
			Assert::AreEqual((std::size_t)0, parseCoordinator.GetParseHelpers().Size());
			parseCoordinator.AddHelper(integerParseHelper);
			Assert::AreEqual((std::size_t)1, parseCoordinator.GetParseHelpers().Size());
			JsonParseCoordinator& clonedCoordinator = *parseCoordinator.Clone();
			Assert::ExpectException<std::runtime_error>([&clonedCoordinator, &integerParseHelper] {clonedCoordinator.RemoveHelper(integerParseHelper); });
			parseCoordinator.RemoveHelper(integerParseHelper);
			Assert::AreEqual((std::size_t)0, parseCoordinator.GetParseHelpers().Size());
			delete& clonedCoordinator;
		}

		TEST_METHOD(MoveConstructor)
		{

			{
				std::string inputString = R"({
				 "integer": 100,
				"child" : {
				"integer": 200,
				"anotherChild":{
				"integer": [77, 78, 80]
						}
				  }
			})";
				JsonIntegerParseHelper::SharedData sharedData;
				JsonIntegerParseHelper integerParseHelper;
				JsonParseCoordinator parseCoordinator(sharedData);
				Assert::IsFalse(integerParseHelper.isInitialized);
				integerParseHelper.Initialize();
				Assert::IsTrue(integerParseHelper.isInitialized);
				parseCoordinator.AddHelper(integerParseHelper);
				Assert::AreEqual((std::size_t)0, integerParseHelper.GetStartHandlerCount());
				Assert::AreEqual((std::size_t)0, integerParseHelper.GetEndHandlerCount());
				Assert::AreEqual((size_t)0, sharedData.MaxDepth());
				Assert::AreEqual((size_t)0, sharedData.Depth());
				parseCoordinator.Parse(inputString);
				Assert::AreEqual((std::size_t)5, sharedData.Data.Size());
				Assert::AreEqual(77, sharedData.Data[0]);
				Assert::AreEqual(78, sharedData.Data[1]);
				Assert::AreEqual(80, sharedData.Data[2]);
				Assert::AreEqual(200, sharedData.Data[3]);
				Assert::AreEqual(100, sharedData.Data[4]);
				Assert::AreEqual((size_t)0, sharedData.Depth());
				Assert::AreEqual((size_t)3, sharedData.MaxDepth());
				Assert::AreEqual((std::size_t)5, integerParseHelper.GetStartHandlerCount());
				Assert::AreEqual((std::size_t)5, integerParseHelper.GetEndHandlerCount());
				Assert::AreNotEqual((std::size_t)0, parseCoordinator.GetParseHelpers().Size());
				JsonParseCoordinator movedCoordinator = std::move(parseCoordinator);
#pragma warning(push)
#pragma warning(disable:26800)
				Assert::AreEqual((std::size_t)0, parseCoordinator.GetParseHelpers().Size());
#pragma  warning(pop)
				auto movedSharedData = reinterpret_cast<JsonIntegerParseHelper::SharedData*>(movedCoordinator.GetSharedData());
				Assert::AreEqual((std::size_t)5, movedSharedData->Data.Size());
				Assert::AreEqual(77, movedSharedData->Data[0]);
				Assert::AreEqual(78, movedSharedData->Data[1]);
				Assert::AreEqual(80, movedSharedData->Data[2]);
				Assert::AreEqual(200, movedSharedData->Data[3]);
				Assert::AreEqual(100, movedSharedData->Data[4]);
				Assert::AreEqual((size_t)0, movedSharedData->Depth());
				Assert::AreEqual((size_t)3, movedSharedData->MaxDepth());
			}
			
		}

		TEST_METHOD(MoveAssignment)
		{
			{
				std::string inputString = R"({
				 "integer": 100,
				"child" : {
				"integer": 200,
				"anotherChild":{
				"integer": [77, 78, 80]
						}
				  }
			})";
				JsonIntegerParseHelper::SharedData sharedData;
				JsonIntegerParseHelper::SharedData sharedData1;
				JsonIntegerParseHelper integerParseHelper;
				JsonIntegerParseHelper integerParseHelper1;
				JsonParseCoordinator parseCoordinator(sharedData);
				Assert::IsFalse(integerParseHelper.isInitialized);
				integerParseHelper.Initialize();
				Assert::IsTrue(integerParseHelper.isInitialized);
				parseCoordinator.AddHelper(integerParseHelper);
				Assert::AreEqual((std::size_t)0, integerParseHelper.GetStartHandlerCount());
				Assert::AreEqual((std::size_t)0, integerParseHelper.GetEndHandlerCount());
				Assert::AreEqual((size_t)0, sharedData.MaxDepth());
				Assert::AreEqual((size_t)0, sharedData.Depth());
				parseCoordinator.Parse(inputString);
				Assert::AreEqual((std::size_t)5, sharedData.Data.Size());
				Assert::AreEqual(77, sharedData.Data[0]);
				Assert::AreEqual(78, sharedData.Data[1]);
				Assert::AreEqual(80, sharedData.Data[2]);
				Assert::AreEqual(200, sharedData.Data[3]);
				Assert::AreEqual(100, sharedData.Data[4]);
				Assert::AreEqual((size_t)0, sharedData.Depth());
				Assert::AreEqual((size_t)3, sharedData.MaxDepth());
				Assert::AreEqual((std::size_t)5, integerParseHelper.GetStartHandlerCount());
				Assert::AreEqual((std::size_t)5, integerParseHelper.GetEndHandlerCount());
				Assert::AreNotEqual((std::size_t)0, parseCoordinator.GetParseHelpers().Size());
				JsonParseCoordinator movedCoordinator(sharedData1);
				movedCoordinator.AddHelper(integerParseHelper1);
				movedCoordinator.AddHelper(integerParseHelper);
				Assert::AreEqual((std::size_t)2, movedCoordinator.GetParseHelpers().Size());
				movedCoordinator= std::move(parseCoordinator);
				Assert::AreEqual((std::size_t)1, movedCoordinator.GetParseHelpers().Size());
#pragma warning(push)
#pragma warning(disable:26800)
				Assert::AreEqual((std::size_t)0, parseCoordinator.GetParseHelpers().Size());
#pragma  warning(pop)
				auto movedSharedData = reinterpret_cast<JsonIntegerParseHelper::SharedData*>(movedCoordinator.GetSharedData());
				Assert::AreEqual((std::size_t)5, movedSharedData->Data.Size());
				Assert::AreEqual(77, movedSharedData->Data[0]);
				Assert::AreEqual(78, movedSharedData->Data[1]);
				Assert::AreEqual(80, movedSharedData->Data[2]);
				Assert::AreEqual(200, movedSharedData->Data[3]);
				Assert::AreEqual(100, movedSharedData->Data[4]);
				Assert::AreEqual((size_t)0, movedSharedData->Depth());
				Assert::AreEqual((size_t)3, movedSharedData->MaxDepth());
			}
			{

				std::string inputString = R"({"integer":[10,20,30,40]})";
				std::string inputString1 = R"({"integer":[100,200,300,400]})";
				JsonIntegerParseHelper::SharedData sharedData;
				JsonIntegerParseHelper integerParseHelper;
				JsonParseCoordinator parseCoordinator(sharedData);
				Assert::IsFalse(integerParseHelper.isInitialized);
				integerParseHelper.Initialize();
				Assert::IsTrue(integerParseHelper.isInitialized);
				parseCoordinator.AddHelper(integerParseHelper);
				Assert::AreEqual((std::size_t)0, integerParseHelper.GetStartHandlerCount());
				Assert::AreEqual((std::size_t)0, integerParseHelper.GetEndHandlerCount());
				Assert::AreEqual((size_t)0, sharedData.MaxDepth());
				Assert::AreEqual((size_t)0, sharedData.Depth());
				parseCoordinator.Parse(inputString);
				Assert::AreEqual((std::size_t)4, sharedData.Data.Size());
				Assert::AreEqual(10, sharedData.Data[0]);
				Assert::AreEqual(20, sharedData.Data[1]);
				Assert::AreEqual(30, sharedData.Data[2]);
				Assert::AreEqual(40, sharedData.Data[3]);
				Assert::AreEqual((std::size_t)4, integerParseHelper.GetStartHandlerCount());
				Assert::AreEqual((std::size_t)4, integerParseHelper.GetEndHandlerCount());
				Assert::AreEqual((size_t)0, sharedData.Depth());
				Assert::AreEqual((size_t)1, sharedData.MaxDepth());
				JsonParseCoordinator& clonedCoordinator = *parseCoordinator.Clone();
				Assert::ExpectException<std::runtime_error>([&clonedCoordinator, &integerParseHelper] {clonedCoordinator.AddHelper(integerParseHelper); });
				auto clonedSharedData = reinterpret_cast<JsonIntegerParseHelper::SharedData*>(clonedCoordinator.GetSharedData());
				Assert::IsNotNull(clonedSharedData);
				Assert::AreEqual((size_t)0, clonedSharedData->MaxDepth());
				Assert::AreEqual((size_t)0, clonedSharedData->Depth());
				clonedCoordinator.Parse(inputString);
				Assert::AreEqual((std::size_t)4, clonedSharedData->Data.Size());
				Assert::AreEqual(10, clonedSharedData->Data[0]);
				Assert::AreEqual(20, clonedSharedData->Data[1]);
				Assert::AreEqual(30, clonedSharedData->Data[2]);
				Assert::AreEqual(40, clonedSharedData->Data[3]);
				Assert::AreEqual((size_t)1, clonedSharedData->MaxDepth());
				Assert::AreEqual((size_t)0, clonedSharedData->Depth());
				JsonIntegerParseHelper::SharedData sharedData1;
				JsonParseCoordinator movedCoordinator(sharedData1);
				JsonIntegerParseHelper integerParseHelper1;
				movedCoordinator.AddHelper(integerParseHelper1);
				Assert::AreEqual((std::size_t)1, movedCoordinator.GetParseHelpers().Size());
				Assert::AreEqual((std::size_t)0, integerParseHelper1.GetStartHandlerCount());
				Assert::AreEqual((std::size_t)0, integerParseHelper1.GetEndHandlerCount());
				Assert::AreEqual((size_t)0, sharedData1.MaxDepth());
				Assert::AreEqual((size_t)0, sharedData1.Depth());
				movedCoordinator.Parse(inputString1);
				Assert::AreEqual((std::size_t)4, sharedData1.Data.Size());
				Assert::AreEqual(100, sharedData1.Data[0]);
				Assert::AreEqual(200, sharedData1.Data[1]);
				Assert::AreEqual(300, sharedData1.Data[2]);
				Assert::AreEqual(400, sharedData1.Data[3]);
				Assert::AreEqual((std::size_t)4, integerParseHelper1.GetStartHandlerCount());
				Assert::AreEqual((std::size_t)4, integerParseHelper1.GetEndHandlerCount());
				Assert::AreEqual((size_t)0, sharedData1.Depth());
				Assert::AreEqual((size_t)1, sharedData1.MaxDepth());
				clonedCoordinator = std::move(movedCoordinator);
#pragma warning(push)
#pragma warning(disable:26800)
				Assert::AreEqual((std::size_t)0, movedCoordinator.GetParseHelpers().Size());
#pragma  warning(pop)
				auto clonedSharedDataNew= reinterpret_cast<JsonIntegerParseHelper::SharedData*>(clonedCoordinator.GetSharedData());
				Assert::AreEqual((std::size_t)1, clonedCoordinator.GetParseHelpers().Size());
				Assert::AreEqual((std::size_t)4, clonedSharedDataNew->Data.Size());
				Assert::AreEqual(100, clonedSharedDataNew->Data[0]);
				Assert::AreEqual(200, clonedSharedDataNew->Data[1]);
				Assert::AreEqual(300, clonedSharedDataNew->Data[2]);
				Assert::AreEqual(400, clonedSharedDataNew->Data[3]);
				Assert::AreEqual((size_t)1, clonedSharedDataNew->MaxDepth());
				Assert::AreEqual((size_t)0, clonedSharedDataNew->Depth());
				delete& clonedCoordinator;
			}

			
		}
	private:
		static _CrtMemState _startMemState;

	};
	_CrtMemState JsonParseTests::_startMemState;
}




