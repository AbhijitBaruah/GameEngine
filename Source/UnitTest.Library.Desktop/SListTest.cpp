#include "pch.h"
#include "SList.h"
#include "Foo.h"
#include "ToStringOverload.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListTests)
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
			SList<Foo> list;
			Assert::AreEqual((size_t)0, list.Size());
		}

		TEST_METHOD(CopyConstructor)
		{
			SList<Foo> list;
			const Foo f1{ 10 };
			const Foo f2{ 109 };
			SList<Foo> list1 = list;
			Assert::AreEqual(list, list1);
			list.PushFront(f1);
			list.PushFront(f1);
			list1.PushFront(f1);
			list1.PushFront(f2);
			Assert::AreNotEqual(list, list1);
			list1.PushFront(f2);
			Assert::AreNotEqual(list, list1);
			SList<Foo> list2 = list;
			Assert::AreEqual(list2, list);
		}

		TEST_METHOD(AssingmentOperator)
		{
			SList<Foo> list;
			SList<Foo> list1;
			const Foo f1{ 10 };
			list1 = list;
			Assert::AreEqual(list, list1);
			list.PushFront(f1);
			list.PushFront(f1);
			list.PushFront(f1);
			Assert::AreNotEqual(list, list1);
			SList<Foo> list2;
			list2 = list;
			Assert::AreEqual(list2, list);
		}
		TEST_METHOD(Front)
		{
			SList<Foo> list;
			auto obj = [&] {list.Front(); };
			Assert::AreEqual((size_t)0, list.Size());
			Assert::ExpectException<std::runtime_error>(obj);
			Foo f1{ 10 };
			list.PushFront(f1);
			Assert::AreEqual((size_t)1, list.Size());
			Assert::AreEqual(list.Front(), f1);
			list.Clear();
			Assert::AreEqual((size_t)0, list.Size());
			const SList<Foo> list1 = list;
			auto obj1 = [&] {list1.Front(); };
			Assert::ExpectException<std::runtime_error>(obj1);
			list.PushFront(f1);
			const SList<Foo> list2 = list;
			Assert::AreEqual(list2.Front(), f1);
		}

		TEST_METHOD(Back)
		{
			SList<Foo> list;
			auto obj = [&] {list.Back(); };
			Assert::AreEqual((size_t)0, list.Size());
			Assert::ExpectException<std::runtime_error>(obj);
			Foo f1{ 10 };
			list.PushFront(f1);
			Assert::AreEqual((size_t)1, list.Size());
			Assert::AreEqual(list.Back(), f1);
			list.Clear();
			Assert::AreEqual((size_t)0, list.Size());
			const SList<Foo> list1 = list;
			auto obj1 = [&] {list1.Back(); };
			Assert::ExpectException<std::runtime_error>(obj1);
			list.PushFront(f1);
			const SList<Foo> list2 = list;
			Assert::AreEqual(list2.Back(), f1);
			

		}
		TEST_METHOD(PushFront)
		{
			SList<Foo> list;
			Assert::AreEqual((size_t)0, list.Size());
			const Foo f1{ 10 };
			const Foo f2{ 100 };
			list.PushFront(f1);
			Assert::AreEqual(list.Front(), f1);
			Assert::AreEqual((size_t)1, list.Size());
			list.PushFront(f2);
			Assert::AreEqual((size_t)2, list.Size());
			Assert::AreEqual(list.Front(), f2);
		}

		TEST_METHOD(PushBack)
		{
			SList<Foo> list;
			const Foo f1{ 10 };
			const Foo f2{ 100 };
			Assert::AreEqual((size_t)0, list.Size());
			list.PushBack(f1);
			Assert::AreEqual(list.Back(), f1);
			Assert::AreEqual((size_t)1, list.Size());
			list.PushBack(f2);
			Assert::AreEqual((size_t)2, list.Size());
			Assert::AreEqual(list.Back(), f2);
		}
		TEST_METHOD(PopFront)
		{
			SList<Foo> list;
			const Foo f1{ 10 };
			const Foo f2{ 100 };
			const Foo f3{ 1000 };
			list.PushFront(f1);
			list.PushFront(f2);
			list.PushBack(f3);
			list.PopFront();
			Assert::AreEqual((size_t)2, list.Size());
			list.PopFront();
			list.PopFront();
		}
		TEST_METHOD(PopBack)
		{
			SList<Foo> list;
			const Foo f1{ 10 };
			const Foo f2{ 100 };
			const Foo f3{ 1000 };
			list.PushFront(f1);
			list.PushFront(f2);
			list.PushBack(f3);
			list.PopFront();
			Assert::AreEqual((size_t)2, list.Size());
			list.PopFront();
			Assert::AreEqual((size_t)1, list.Size());
			list.PopBack();

		}

		TEST_METHOD(IsEmpty)
		{
			SList<Foo> list;
			Assert::IsTrue(list.IsEmpty());
			const Foo f1{ 10 };
			list.PushFront(f1);
			Assert::IsFalse(list.IsEmpty());
		}

		TEST_METHOD(Clear)
		{
			SList<Foo> list;
			list.Clear();
			Assert::AreEqual((size_t)0, list.Size());
			const Foo f1{ 10 };
			list.PushFront(f1);
			list.Clear();
			Assert::AreEqual((size_t)0, list.Size());
		}
		TEST_METHOD(Size)
		{
			SList<Foo> list;
			Assert::AreEqual((size_t)0, list.Size());
			const Foo f1{ 10 };
			const Foo f2{ 100 };
			list.PushFront(f1);
			list.PushFront(f2);
			Assert::AreEqual((size_t)2, list.Size());
			list.PopBack();
			Assert::AreEqual((size_t)1, list.Size());
		}

		TEST_METHOD(IteratorConstructor)
		{
			SList<Foo> list;
			Foo f1{ 10 };
			SList<Foo>::Iterator it1;
			it1 = list.PushFront(f1);
			Assert::AreEqual(*it1, f1);
			SList<Foo>::Iterator it2 = list.begin();
			Assert::AreEqual(it1, it2);
		}

		TEST_METHOD(Begin)
		{
			SList<Foo> list;
			Foo f1{ 10 };
			Foo f2{ 20 };
			SList<Foo>::Iterator it1 = list.PushFront(f1);
			Assert::AreEqual(list.begin(), it1);
			list.PushFront(f2);
			Assert::AreNotEqual(list.begin(), it1);
			SList<Foo> list1;
			Assert::AreEqual(list1.cend(), list1.cbegin());
		
		}

		TEST_METHOD(CBegin)
		{
			SList<Foo> list;
			Foo f1{ 10 };
			Foo f2{ 20 };
			SList<Foo>::ConstIterator it1;
			list.PushFront(f1);
			it1 = list.cbegin();
			const SList<Foo> list1 = list;
			Assert::AreEqual(list.cbegin(), it1);
			it1 = list1.begin();
			Assert::AreEqual(list1.begin(), it1);
		}

		TEST_METHOD(Find)
		{
			SList<Foo> list;
			Foo f1{ 10 };
			Foo f2{ 20 };
			Foo f3{ 30 };
			Foo f6{ 300 };
			list.PushFront(f1);
			list.PushFront(f2);
			list.PushFront(f3);
			std::function<bool(const Foo&, const Foo&)> func = [](const Foo& lhs, const Foo& rhs) {return lhs.Data() == rhs.Data(); };
			SList<Foo>::Iterator it1 = list.Find(f2);
			Assert::AreEqual(*it1, f2);
			const SList<Foo> list2 = list;
			SList<Foo>::ConstIterator it2 = list2.Find(f1);
			Assert::AreEqual(*it2, f1);
			SList<Foo>::Iterator it3 = list.Find(f6);
			Assert::AreEqual(list.end(), it3);



		}

		TEST_METHOD(PreIncrement)
		{
			SList<Foo> list;
			Foo f1{ 10 };
			Foo f2{ 20 };
			Foo f3{ 30 };
			list.PushFront(f1);
			list.PushFront(f2);
			list.PushFront(f3);
			SList<Foo>::Iterator it1 = list.begin();
			++it1;
			Assert::AreEqual(*it1, f2);
			list.Clear();
			SList<Foo>::Iterator it;
			Assert::ExpectException<std::runtime_error>([&it] { ++it; });
			SList<Foo>::Iterator it2 = list.begin();
			Assert::ExpectException<std::runtime_error>([&it2] { ++it2; });
		}
		TEST_METHOD(PostIncrement)
		{
			SList<Foo> list;
			Foo f1{ 10 };
			Foo f2{ 20 };
			Foo f3{ 30 };
			list.PushFront(f1);
			list.PushFront(f2);
			list.PushFront(f3);
			SList<Foo>::Iterator it1 = list.begin();
			Assert::AreEqual(*it1, f3);
			SList<Foo>::Iterator it2 = it1++;
			Assert::AreNotEqual(*it2, *it1);
			Assert::AreEqual(*it1, f2);
			list.Clear();
			SList<Foo>::Iterator it;
			Assert::ExpectException<std::runtime_error>([&it] { it++; });
			SList<Foo>::Iterator it3 = list.begin();
			Assert::ExpectException<std::runtime_error>([&it3] { it3++; });
			list.PushFront(f1);
			list.PushFront(f2);
			list.PushFront(f3);
			SList<Foo>::ConstIterator itr1 = list.begin();
			++itr1;
			Assert::AreEqual(*itr1, f2);
			itr1++;
			Assert::AreEqual(*itr1, f1
			);


		}


		TEST_METHOD(InsertAfter)
		{
			SList<Foo> list;
			Foo f1{ 10 };
			Foo f2{ 20 };
			Foo f3{ 30 };
			list.PushFront(f1);
			list.PushFront(f2);
			list.PushFront(f3);
			SList<Foo>::Iterator it1 = list.Find(f1);
			Assert::AreEqual(*it1, f1);
			Foo f4{ 40 };
			list.InsertAfter(it1, f4);
			Assert::AreEqual(*it1, f1);
			++it1;
			Assert::AreEqual(*it1, f4);
			SList<Foo> list1;
			Foo f1again{ 10 };
			Foo f2again{ 20 };
			Foo f3again{ 30 };
			list1.PushFront(f1again);
			list1.PushFront(f2again);
			list1.PushFront(f3again);
			SList<Foo>::Iterator it2 = list1.begin();
			Assert::ExpectException<std::runtime_error>([&list, &it2, &f4] { list.InsertAfter(it2, f4); });
			SList<Foo> list2;
			SList<Foo>::Iterator it3 = list2.end();
			Foo f5{ 200 };
			list2.InsertAfter(it3, f5);


		}
		TEST_METHOD(Remove)
		{
			SList<Foo> list;
			Foo f1{ 10 };
			Foo f2{ 20 };
			Foo f3{ 30 };
			list.PushFront(f1);
			list.PushFront(f2);
			list.PushFront(f3);
			Assert::AreEqual(*(list.begin()), f3);
			list.Remove(f3);
			SList<Foo>::Iterator it1 = list.begin();
			Assert::AreEqual(*it1, f2);
			Foo f4{ 40 };
			list.PushBack(f4);
			list.Remove(f1);
			++it1;
			Assert::AreEqual(*it1, f4);
		}


	private:
		static _CrtMemState _startMemState;

	};
	_CrtMemState SListTests::_startMemState;
}




