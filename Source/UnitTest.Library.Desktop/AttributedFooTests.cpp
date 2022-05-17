#include "pch.h"
#include "AttributedFoo.h"
#include "Foo.h"
#include "ToStringOverload.h"
#include "AttributedBar.h"
#include "ChildAttributedFoo.h"
#include "FooFailClass.h"
#include "RTTI.h"
#include "Attribute.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AttributedFooTests)
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
			AttributedFoo a1;
			Assert::IsFalse(a1.IsEmpty());
			Assert::IsTrue(a1.IsAttribute("this"));
			Assert::IsTrue(a1.IsAttribute("ExternalInteger"));
			Assert::IsTrue(a1.IsAttribute("ExternalFloat"));
			Assert::IsTrue(a1.IsAttribute("ExternalString"));
			Assert::IsTrue(a1.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(a1.IsAttribute("ExternalVector"));
			Assert::IsTrue(a1.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalMatrixArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalInteger"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalFloat"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalString"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalMatrix"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalVector"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalIntegerArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalMatrixArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalStringArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("Table"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("TableArray"));
			Assert::ExpectException<std::runtime_error>([] {AttributedBar a1; });
		}

		TEST_METHOD(ExternalSetData)
		{
			AttributedFoo a1;
			Assert::AreSame(a1.Find("ExternalInteger")->Get<std::int32_t>(0), a1.ExternalInteger);
			std::int32_t a = 10;
			a1.Find("ExternalInteger")->Set(a);
			Assert::AreEqual(a1.Find("ExternalInteger")->Get<std::int32_t>(0), a);
			Assert::AreEqual(a1.ExternalInteger, a);
		
		}
		TEST_METHOD(ChildAttributedFooTest)
		{
			ChildAttributedFoo a1;
			Assert::IsFalse(a1.IsEmpty());
			Assert::IsTrue(a1.IsAttribute("this"));

			Assert::IsTrue(a1.IsAttribute("ExternalInteger"));
			Assert::IsTrue(a1.IsAttribute("ExternalFloat"));
			Assert::IsTrue(a1.IsAttribute("ExternalString"));
			Assert::IsTrue(a1.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(a1.IsAttribute("ExternalVector"));
			Assert::IsTrue(a1.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalMatrixArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalStringArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalInteger"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalFloat"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalString"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalMatrix"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalVector"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalIntegerArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalMatrixArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalStringArray"));
			Assert::IsTrue(a1.IsAttribute("externalChildInt"));
			Assert::IsTrue(a1.IsPrescribedAttribute("externalChildInt"));

			Assert::ExpectException<std::runtime_error>([] {FooFailClass f1; });
		}
		TEST_METHOD(CopyConstructor)
		{
			AttributedFoo a1;
			Assert::IsFalse(a1.IsEmpty());
			AttributedFoo a2 = a1;
			Assert::IsFalse(a2.IsEmpty());
			Assert::IsTrue(a1.Find("ExternalInteger") != nullptr);
			Assert::IsTrue(a2.Find("ExternalInteger") != nullptr);
			Assert::IsTrue(a1 == a2);
			Datum& d = *(a1.Find("ExternalInteger"));
			d.Set(10, 0);
			Assert::IsFalse(a1 == a2);
		}
		TEST_METHOD(MoveConstructor)
		{
			AttributedFoo a1;
			Assert::IsFalse(a1.IsEmpty());
			AttributedFoo a2 = std::move(a1);
			Assert::IsFalse(a2.IsEmpty());
#pragma warning(push)
#pragma warning(disable:26800)
			Assert::IsTrue(a1.IsEmpty());
#pragma  warning(pop)
			Assert::IsTrue(a2.Find("ExternalInteger") != nullptr);
			Datum& d = *a2.Find("ExternalInteger");
			d.Set(10, 0);
			Assert::IsTrue(a2.Find("ExternalInteger")->Get<std::int32_t>(0)==10);
	
		}
		TEST_METHOD(AssignmentOperator)
		{
			AttributedFoo a1;
			AttributedFoo a2;
			Assert::IsFalse(a1.IsEmpty());
			a2 = a1;
			Assert::IsFalse(a2.IsEmpty());
			Assert::IsTrue(a1.Find("ExternalInteger") != nullptr);
			Assert::IsTrue(a2.Find("ExternalInteger") != nullptr);
			Assert::IsTrue(a1 == a2);
			Datum& d = *(a1.Find("ExternalInteger"));
			d.Set(10, 0);
			Assert::IsFalse(a1 == a2);
		}

		TEST_METHOD(MoveAssignment)
		{
			AttributedFoo a1;
			AttributedFoo a2;
			Assert::IsFalse(a1.IsEmpty());
			a2 = std::move(a1);
			Assert::IsFalse(a2.IsEmpty());
#pragma warning(push)
#pragma warning(disable:26800)
			Assert::IsTrue(a1.IsEmpty());
#pragma  warning(pop)
			Assert::IsTrue(a2.Find("ExternalInteger") != nullptr);
			Datum& d = *a2.Find("ExternalInteger");
			d.Set(10, 0);
			Assert::IsTrue(a2.Find("ExternalInteger")->Get<std::int32_t>(0) == 10);
		}

		TEST_METHOD(AppendAuxillary)
		{
			AttributedFoo a1;
			Assert::ExpectException<std::runtime_error>([&a1] {a1.AppendAuxillary("ExternalInteger"); });
			a1.AppendAuxillary("Gameobj");
			Assert::IsTrue(a1.IsAttribute("Gameobj"));
			Assert::IsFalse(a1.IsPrescribedAttribute("Gameobj"));
			Assert::IsTrue(a1.IsAuxillaryAttribute("Gameobj"));
		}

		TEST_METHOD(IsAttribute)
		{
			AttributedFoo a1;
			Assert::IsTrue(a1.IsAttribute("ExternalInteger"));
			Assert::IsTrue(a1.IsAttribute("ExternalFloat"));
			Assert::IsTrue(a1.IsAttribute("ExternalString"));
			Assert::IsTrue(a1.IsAttribute("ExternalMatrix"));
			Assert::IsTrue(a1.IsAttribute("ExternalVector"));
			Assert::IsTrue(a1.IsAttribute("ExternalIntegerArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalFloatArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalMatrixArray")); 
			Assert::IsTrue(a1.IsAttribute("ExternalVectorArray"));
			Assert::IsTrue(a1.IsAttribute("ExternalStringArray"));
			Assert::IsFalse(a1.IsAttribute("A"));
			a1.AppendAuxillary("A");
			Assert::IsTrue(a1.IsAttribute("A"));
		}

		TEST_METHOD(IsPrescribedAttribute)
		{
			AttributedFoo a1;
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalInteger"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalFloat"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalString"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalMatrix"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalVector"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalIntegerArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalFloatArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalMatrixArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalVectorArray"));
			Assert::IsTrue(a1.IsPrescribedAttribute("ExternalStringArray"));
			Assert::IsFalse(a1.IsPrescribedAttribute("A"));
			a1.AppendAuxillary("A");
			Assert::IsFalse(a1.IsPrescribedAttribute("A"));
		}

		TEST_METHOD(IsAuxillaryAttribute)
		{
			AttributedFoo a1;
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalInteger"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalFloat"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalString"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalMatrix"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalVector"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalIntegerArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalFloatArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalMatrixArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalVectorArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("ExternalStringArray"));
			Assert::IsFalse(a1.IsAuxillaryAttribute("A"));
			a1.AppendAuxillary("A");
			Assert::IsTrue(a1.IsAuxillaryAttribute("A"));
		}
	private:
		static _CrtMemState _startMemState;

	};
	_CrtMemState AttributedFooTests::_startMemState;
}