#include "pch.h"
#include "Scope.h"
#include "Foo.h"
#include "ToStringOverload.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ScopeTests)
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
			Scope s;
			Assert::IsNull(s.GetParent());
			Assert::IsTrue(s.IsEmpty());
			const Scope s1 = s;
			Assert::IsNull(s1.GetParent());
			Assert::IsTrue(s1.IsEmpty());
		}
		TEST_METHOD(CopyConstructor)
		{
			Scope s;
			s.Append("A");
			Datum* d = s.Find("A");
			d->SetType(DatumTypes::Integer);
			s.AppendScope("B");
			Scope s1(s);
			Assert::IsNotNull(s1.Find("A"));
			Assert::IsNotNull(s1.Find("B"));
			Assert::AreEqual(s1.Find("B")->Get<Scope*>()->GetParent(), &s1);
		}

		TEST_METHOD(CopyAssignment)
		{
			Scope s, s1;
			s1.Append("A");
			s1.AppendScope("B");
			s.Append("C");
			s.AppendScope("D");
			Assert::IsNotNull(s1.Find("A"));
			Assert::IsNull(s1.Find("C"));
			s1 = s;
			Assert::IsNull(s1.Find("A"));
			Assert::IsNotNull(s1.Find("C"));
		}
		TEST_METHOD(MoveConstructor)
		{

			{
				Scope s;
				s.Append("A");
				Datum* d = s.Find("A");
				d->SetType(DatumTypes::Integer);
				s.AppendScope("B");
				Scope s1(std::move(s));
				Assert::IsNotNull(s1.Find("A"));
				Assert::IsNotNull(s1.Find("B"));
				Assert::AreEqual(s1.Find("B")->Get<Scope*>()->GetParent(), &s1);
			}
			{
				Scope initalParent;
				Datum& d = initalParent.Append("A");
				d = 10;
				Scope& childScope = initalParent.AppendScope("B");
				childScope.Append("C");
				Assert::IsFalse(childScope.IsEmpty());
				Scope* scopeToMoveInto = new Scope(std::move(childScope));

#pragma warning(push)
#pragma warning(disable:26800)
				Assert::IsTrue(childScope.IsEmpty());
				Assert::IsNull(childScope.GetParent());
#pragma  warning(pop)
				Assert::IsNotNull(scopeToMoveInto->Find("C"));
				Assert::AreEqual(initalParent.Find("B")->Get<Scope*>()->GetParent(), &initalParent);
				delete& childScope;

			}
		}

		TEST_METHOD(Equality)
		{
			Scope s1;
			Scope s2;
			s1.Append("A");
			Datum* d = s1.Find("A");
			d->SetType(DatumTypes::Integer);
			d->PushBack(10);
			s2.Append("A");
			Datum* d1 = s2.Find("A");
			d1->SetType(DatumTypes::Integer);
			d1->PushBack(10);
			s1.AppendScope("B");
			s2.Append("C");
			s1.Append("C");
			s2.AppendScope("B");
			Assert::IsTrue(s1 == s2);
			d1->PushBack(20);
			Assert::IsTrue(s1 != s2);
			Assert::IsTrue(s1 == s1);



		}
		TEST_METHOD(MoveAssignment)
		{

			{
				Scope s;
				s.Append("A");
				Datum* d = s.Find("A");
				d->SetType(DatumTypes::Integer);
				s.AppendScope("B");
				Scope s1;
				s1 = (std::move(s));
				Assert::IsNotNull(s1.Find("A"));
				Assert::IsNotNull(s1.Find("B"));
				Assert::AreEqual(s1.Find("B")->Get<Scope*>()->GetParent(), &s1);
			}

			{
				Scope initalParent;
				Datum& d = initalParent.Append("A");
				d = 10;
				Scope& childScope = initalParent.AppendScope("B");
				childScope.Append("C");
				Assert::IsFalse(childScope.IsEmpty());
				Scope* scopeToMoveInto = new Scope();
				*scopeToMoveInto = std::move(childScope);

#pragma warning(push)
#pragma warning(disable:26800)
				Assert::IsTrue(childScope.IsEmpty());
				Assert::IsNull(childScope.GetParent());
#pragma  warning(pop)
				Assert::IsNotNull(scopeToMoveInto->Find("C"));
				Assert::AreEqual(initalParent.Find("B")->Get<Scope*>()->GetParent(), &initalParent);
				delete& childScope;

			}
			
		}
		TEST_METHOD(AppendScope)
		{
			Scope s;
			Assert::IsNull(s.GetParent());
			Scope& childScope = s.AppendScope("Gameobject");
			Assert::AreEqual(childScope.GetParent(), &s);
			Scope& anotherChildScope = s.AppendScope("Gameobject");
			Assert::AreEqual(anotherChildScope.GetParent(), &s);
			s.Append("Cube");
			Datum& childDatum = *(s.Search("Cube"));
			childDatum.SetType(DatumTypes::Integer);
			Assert::ExpectException<std::runtime_error>([&s] {s.AppendScope("Cube"); });
		}


		TEST_METHOD(Append)
		{
			Scope s;
			Assert::IsNull(s.GetParent());
			Datum& childScope = s.Append("Gameobject");
			Assert::AreEqual(childScope.Type(), DatumTypes::Unknown);
		}

		TEST_METHOD(Search)
		{
			Scope s;
			Assert::IsNull(s.GetParent());
			s.Append("GameObject");
			Scope& childScope = s.AppendScope("Child");
			childScope.Append("ChildGameObj");
			Assert::IsNotNull(childScope.Search("GameObject"));
			Assert::IsNull(childScope.Search("Abc"));
			Scope& nestedChild = childScope.AppendScope("NestedChild");
			Scope* outparam = &childScope;
			nestedChild.Search("GameObject", outparam);
			Assert::AreEqual(outparam, &s);
			const Scope& rootScope = s;
			const Scope& s1 = childScope;
			const Scope& s2 = nestedChild;
			Assert::IsNotNull(s1.Search("GameObject"));
			Assert::IsNull(s1.Search("Abc"));
			const Scope* constOutParam = &s1;
			s2.Search("GameObject", constOutParam);
			Assert::AreEqual(constOutParam, &rootScope);
		}

		TEST_METHOD(OperatorBracket)
		{
			Scope s;
			Assert::IsNull(s.GetParent());
			s["GameObject"];
			Assert::IsNotNull(s.Search("GameObject"));
			Datum& ordVector = s[0];
			Assert::AreEqual(ordVector, *(s.Search("GameObject")));
		}

		TEST_METHOD(Find)
		{
			Scope s1;
			Assert::IsNull(s1.GetParent());
			s1.Append("Abc");
			Assert::IsNotNull(s1.Find("Abc"));
			Assert::IsNull(s1.Find("a"));
			const Scope& s2 = s1;
			Assert::IsNotNull(s2.Find("Abc"));
			Assert::IsNull(s2.Find("a"));
		}

		TEST_METHOD(Adopt)
		{
			{
				Scope* s1 = new Scope();
				s1->Append("A");
				Scope* s = new Scope();
				s1->Adopt(*s, "A");
				Assert::AreEqual(s->GetParent(), s1);
				Scope& s2 = s->AppendScope("C");
				s2.Adopt(*s1, "C");
				delete s1;
			}
			{
				Scope* s1 = new Scope();
				Scope* s = new Scope();
				s1->Adopt(*s, "A");
				Assert::AreEqual(s->GetParent(), s1);
				delete s1;
			}
			{

				Scope* s1 = new Scope();
				Scope* s = new Scope();
				Scope& childScope = s->AppendScope("A");
				s1->Adopt(childScope, "A");
				delete s1;
				delete s;

			}
			{

				Scope* s1 = new Scope();
				Scope* s = new Scope();
				Scope& childScope = s->AppendScope("A");
				s1->Append("A");
				Datum* d = s1->Find("A");
				d->SetType(DatumTypes::Integer);
				childScope;
				Assert::ExpectException<std::runtime_error>([&s1, &childScope] {s1->Adopt(childScope, "A"); });
				delete s1;
				delete s;

			}
			{
				Scope* s1 = new Scope();
				s1->Adopt(*s1, "A");
				Scope& s2 = s1->AppendScope("B");
				s1->Adopt(s2, "C");
				Assert::AreEqual(s2.GetParent(), s1);
				delete s1;
			}


		}

		TEST_METHOD(FindContainsScope)
		{
			Scope s1, s2;
			Scope& child = s1.AppendScope("A");
			s1.AppendScope("B");
			Scope& anotherChild = child.AppendScope("C");
			Assert::IsNotNull(s1.FindContainedScope(&child).first);
			Assert::IsNull(s1.FindContainedScope(&anotherChild).first);
			const Scope& constScope = s1;
			Assert::IsNotNull(constScope.FindContainedScope(&child).first);
			Assert::IsNull(constScope.FindContainedScope(&anotherChild).first);
		}
		TEST_METHOD(Orphan)
		{
			Scope* s1 = new Scope();
			Scope* s2 = new Scope();
			s1->Orphan();
			Assert::IsNull(s1->GetParent());
			s1->Adopt(*s2, "A");
			Assert::AreEqual(s2->GetParent(), s1);
			s2->Orphan();
			Assert::IsNull(s2->GetParent());
			delete s1;
			delete s2;
		}


	private:
		static _CrtMemState _startMemState;

	};
	_CrtMemState ScopeTests::_startMemState;
}