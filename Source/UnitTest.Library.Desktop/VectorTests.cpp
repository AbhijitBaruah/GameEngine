#include "pch.h"
#include "Vector.h"
#include "Foo.h"
#include "ToStringOverload.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(VectorTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemStatev);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemStatev, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}
		TEST_METHOD(Constructor)
		{
			Vector<Foo> vector;
			Assert::AreEqual((size_t)0, vector.Size());
			Assert::AreEqual((size_t)0, vector.Capacity());
			Vector<Foo> vector1(15);
			Assert::AreEqual((size_t)15, vector1.Capacity());
		}

		TEST_METHOD(CopyConstructor)
		{
			Vector<Foo> vector;
			const Foo f1{ 10 };
			const Foo f2{ 109 };
			Vector<Foo> vector1 = vector;
			Assert::IsTrue(std::equal(vector.begin(), vector.end(), vector1.end()));
			vector.PushBack(f1);
			vector.PushBack(f1);
			vector.PushBack(f1);
			Assert::AreNotEqual(vector.begin(), vector1.begin());
		}
		TEST_METHOD(MoveConstructor)
		{
			Vector<Foo> vector;
			const Foo f1{ 10 };
			const Foo f2{ 109 };
			Vector<Foo> vector1 = std::move(vector);
			Assert::IsTrue(std::equal(vector.begin(), vector.end(), vector1.end()));
			vector1.PushBack(f1);
			vector1.PushBack(f1);
			vector1.PushBack(f1);
			Assert::AreNotEqual(vector.begin(), vector1.begin());
		}

		TEST_METHOD(AssingmentOperator)
		{
			Vector<Foo> vector;
			Vector<Foo> vector1;
			const Foo f1{ 10 };
			vector1 = vector;
			Assert::IsTrue(std::equal(vector.begin(), vector.end(), vector1.end()));
			vector.PushBack(f1);
			vector.PushBack(f1);
			vector.PushBack(f1);
			Assert::AreNotEqual(vector.begin(), vector1.begin());
		}

		TEST_METHOD(MoveAssignment)
		{
			Vector<Foo> vector;
			const Foo f1{ 10 };
			const Foo f2{ 109 };
			Vector<Foo> vector1;
			vector1 = std::move(vector);
			Assert::IsTrue(std::equal(vector.begin(), vector.end(), vector1.end()));
			vector1.PushBack(f1);
			vector1.PushBack(f1);
			vector1.PushBack(f1);
			Assert::AreNotEqual(vector.begin(), vector1.begin());
		}

		TEST_METHOD(OperatorBracket)
		{
			Vector<Foo> vector;
			const Foo f1{ 10 };
			const Foo f2{ 109 };
			vector.PushBack(f1);
			vector.PushBack(f2);
			Assert::AreEqual(vector.operator[](0), f1);
			const Vector<Foo> vector1 = vector;
			Assert::AreEqual(vector.operator[](1), f2);
		}

		TEST_METHOD(Front)
		{
			Vector<Foo> vector;
			Foo f1{ 10 };
			vector.PushBack(f1);
			Assert::AreEqual((size_t)1, vector.Size());
			Assert::AreEqual(vector.Front(), f1);
			vector.Clear();
			Assert::AreEqual((size_t)0, vector.Size());
			const Vector<Foo> vector1 = vector;
			vector.PushBack(f1);
			const Vector<Foo> vector2 = vector;
			Assert::AreEqual(vector2.Front(), f1);
		}

		TEST_METHOD(Back)
		{
			Vector<Foo> vector;
			Foo f1{ 10 };
			vector.PushBack(f1);
			Assert::AreEqual((size_t)1, vector.Size());
			Assert::AreEqual(vector.Back(), f1);
			vector.Clear();
			Assert::AreEqual((size_t)0, vector.Size());
			const Vector<Foo> vector1 = vector;
			vector.PushBack(f1);
			const Vector<Foo> vector2 = vector;
			Assert::AreEqual(vector2.Back(), f1);

		}

		TEST_METHOD(PushBack)
		{
			Vector<Foo> vector;
			const Foo f1{ 10 };
			const Foo f2{ 100 };
			vector.PushBack(f1);
			Assert::AreEqual((size_t)1, vector.Size());
			vector.PushBack(f2);
			Assert::AreEqual((size_t)2, vector.Size());
			Assert::AreEqual(vector.Back(), f2);
		}

		TEST_METHOD(PopBack)
		{
			Vector<Foo> vector;
			const Foo f1{ 10 };
			const Foo f2{ 100 };
			const Foo f3{ 1000 };
			vector.PushBack(f1);
			vector.PushBack(f2);
			vector.PushBack(f3);
			vector.PopBack();
			Assert::AreEqual((size_t)2, vector.Size());
			vector.PopBack();
			Assert::AreEqual((size_t)1, vector.Size());


		}

		TEST_METHOD(IsEmpty)
		{
			Vector<Foo> vector;
			Assert::IsTrue(vector.isEmpty());
			const Foo f1{ 10 };
			vector.PushBack(f1);
			Assert::IsFalse(vector.isEmpty());
		}

		TEST_METHOD(Clear)
		{
			Vector<Foo> vector;
			vector.Clear();
			Assert::AreEqual((size_t)0, vector.Size());
			const Foo f1{ 10 };
			vector.PushBack(f1);
			vector.Clear();
			Assert::AreEqual((size_t)0, vector.Size());
		}
		TEST_METHOD(Size)
		{
			Vector<Foo> vector;
			Assert::AreEqual((size_t)0, vector.Size());
			const Foo f1{ 10 };
			const Foo f2{ 100 };
			vector.PushBack(f1);
			vector.PushBack(f2);
			Assert::AreEqual((size_t)2, vector.Size());
			vector.PopBack();
			Assert::AreEqual((size_t)1, vector.Size());
		}

		TEST_METHOD(IteratorConstructor)
		{
			Vector<Foo> vector;
			Foo f1{ 10 };
			Vector<Foo>::Iterator it1;
			it1 = vector.PushBack(f1);
			Assert::AreEqual(*it1, f1);
			Vector<Foo>::Iterator it2 = vector.begin();
			Assert::AreEqual(it1, it2);
		}

		TEST_METHOD(Begin)
		{
			Vector<Foo> vector;
			Foo f1{ 10 };
			Foo f2{ 20 };
			Vector<Foo>::Iterator it1 = vector.PushBack(f1);
			Assert::AreEqual(vector.begin(), it1);
			Vector<Foo>::Iterator it2 = vector.PushBack(f2);
			Assert::AreNotEqual(vector.begin(), it2);
			Vector<Foo> vector1;
			Assert::AreEqual(vector1.cend(), vector1.cbegin());

		}



		TEST_METHOD(Find)
		{
			Vector<Foo> vector;
			Foo f1{ 10 };
			Foo f2{ 20 };
			Foo f3{ 30 };
			Foo f6{ 300 };
			vector.PushBack(f1);
			vector.PushBack(f2);
			vector.PushBack(f3);
			//std::function<bool(const Foo&, const Foo&)> func = [](const Foo& lhs, const Foo& rhs) {return lhs.Data() == rhs.Data(); };
			Vector<Foo>::Iterator it1 = vector.Find(f2);
			Assert::AreEqual(*it1, f2);
			const Vector<Foo> vector1 = vector;
			Vector<Foo>::ConstIterator it2 = vector1.Find(f1);
			Assert::AreEqual(*it2, f1);
			Vector<Foo>::Iterator it3 = vector.Find(f6);
			Assert::AreEqual(vector.end(), it3);
		}

		TEST_METHOD(PreIncrement)
		{
			Vector<Foo> vector;
			Foo f1{ 10 };
			Foo f2{ 20 };
			Foo f3{ 30 };
			vector.PushBack(f1);
			vector.PushBack(f2);
			vector.PushBack(f3);
			Vector<Foo>::Iterator it1 = vector.begin();
			++it1;
			Assert::AreEqual(*it1, f2);
			vector.Clear();
			Vector<Foo>::Iterator it;
			Assert::ExpectException<std::runtime_error>([&it] { ++it; });
		}

		TEST_METHOD(PostIncrement)
		{
			Vector<Foo> vector;
			Foo f1{ 10 };
			Foo f2{ 20 };
			Foo f3{ 30 };
			vector.PushBack(f1);
			vector.PushBack(f2);
			vector.PushBack(f3);
			Vector<Foo>::Iterator it1 = vector.begin();
			Assert::AreEqual(*it1, f1);
			Vector<Foo>::Iterator it2 = it1++;
			Assert::AreNotEqual(*it2, *it1);
			Assert::AreEqual(*it1, f2);
			vector.Clear();
			Vector<Foo>::Iterator it;
			Assert::ExpectException<std::runtime_error>([&it] { it++; });
			vector.PushBack(f1);
			vector.PushBack(f2);
			vector.PushBack(f3);
			Vector<Foo>::ConstIterator itr1 = vector.begin();
			++itr1;
			Assert::AreEqual(*itr1, f2);
			itr1++;
			Assert::AreEqual(*itr1, f3);
		}

		TEST_METHOD(Remove)
		{
			Vector<Foo> vector;
			const Foo f1{ 10 };
			const Foo f2{ 20 };
			const Foo f3{ 30 };
			const Foo f4{ 40 };
			const Foo f5{ 50 };
			const Foo f6{ 60 };
			vector.PushBack(f1);
			vector.PushBack(f2);
			vector.PushBack(f3);
			Assert::AreEqual(*(vector.begin()), f1);
			vector.Remove(f1);
			Vector<Foo>::Iterator it1 = vector.begin();
			Assert::AreEqual(*it1, f2);
			vector.PushBack(f1);
			vector.PushBack(f4);
			vector.PushBack(f5);
			vector.PushBack(f6);
			Assert::AreEqual((size_t)6, vector.Size());
			Vector<Foo>::Iterator it2 = vector.Find(f1);
			Vector<Foo>::Iterator it3 = vector.Find(f6);
			vector.Remove(it2, it3);
			Assert::AreEqual((size_t)3, vector.Size());
		}

		TEST_METHOD(At)
		{
			Vector<Foo> vector;
			const Foo f1{ 10 };
			const Foo f2{ 20 };
			const Foo f3{ 30 };
			vector.PushBack(f1);
			vector.PushBack(f2);
			vector.PushBack(f3);
			Assert::AreEqual(f2, vector.At(1));
			const Vector<Foo> vector1 = vector;
			Assert::AreEqual(f1, vector1.At(0));
		}

		TEST_METHOD(Reserve)
		{
			Vector<Foo> vector;
			vector.Reserve(100);
			Assert::AreEqual(vector.Capacity(), (size_t)100);
			Assert::ExpectException<std::runtime_error>([&vector] { vector.Reserve(20); });
		}


	private:
		static _CrtMemState _startMemStatev;

	};
	_CrtMemState VectorTests::_startMemStatev;
}


