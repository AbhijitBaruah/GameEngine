#include "pch.h"
#include "Foo.h"
#include "ToStringOverload.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(FooTests)
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
		TEST_METHOD(Constructor)
		{
			Foo f(20);
			Assert::AreEqual(f.Data(), 20);
		}

		TEST_METHOD(CopyConstructor)
		{
			Foo f(20);
			Foo f1 = f;
			Assert::AreEqual(f1, f);
			Assert::AreNotSame(f, f1);
			Assert::AreNotSame(f.Data(), f1.Data());
		}

		TEST_METHOD(Data)
		{
			Foo f(20);
			Assert::AreEqual(f.Data(), 20);
			std::int32_t& data = f.Data();
			data = 30;
			Assert::AreEqual(f.Data(), 30);
			const Foo& fconst = f;
			Assert::AreEqual(fconst.Data(), 30);
		
		}
		
		TEST_METHOD(EqualOperator)
		{
			Foo f(20);
			Foo f1(20);
			Assert::AreNotSame(f1, f);
			Assert::IsTrue(f == f);
			Assert::IsTrue(f1 == f);
			f1.Data() = 30;
			Assert::IsTrue(f1 != f);
			f = f1;
			Assert::IsTrue(f1 == f);
		}
		
	private:
		static _CrtMemState _startMemState;

	};
	_CrtMemState FooTests::_startMemState;
}




