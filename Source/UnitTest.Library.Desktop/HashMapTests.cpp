#include "pch.h"
#include "HashMap.h"
#include "Foo.h"
#include "ToStringOverload.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine;
namespace UnitTestLibraryDesktop
{
	TEST_CLASS(HashMapTests)
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
			HashMap<Foo, Foo> h1(10, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);

		}
		TEST_METHOD(CopyConstructor)
		{
			HashMap<Foo, Foo> h1(10, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 21 };
			const Foo f2{ 100 };
			HashMap<Foo, Foo> h2 = h1;
			Assert::IsTrue(std::equal(h1.begin(), h1.end(), h2.end()));
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreNotEqual(h1.begin(), h2.begin());
			Assert::AreEqual(h1.begin().operator*(), std::pair<const Foo,Foo>(f1, f2));
		}

		TEST_METHOD(MoveConstructor)
		{
			HashMap<Foo, Foo> h1(10, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 37 };
			const Foo f2{ 100 };
			HashMap<Foo, Foo> h2(10, FooHash{});
			h2 = h1;
			Assert::IsTrue(std::equal(h1.begin(), h1.end(), h2.end()));
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreNotEqual(h1.begin(), h2.begin());
			Assert::AreEqual(h1.begin().operator*(), std::pair<const Foo, Foo>(f1, f2));
		}
		struct  FooHash
		{
			std::size_t operator()(const Foo& value)
			{
				return abs(value.Data());
			}
		};
		TEST_METHOD(Insert)
		{
			HashMap<Foo, Foo> h1(10, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 27 };
			const Foo f2{ 13 };
			const Foo f3{ 71 };
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreEqual(h1.Size(), (size_t)1);
			Assert::AreEqual(h1.begin().operator*(), std::pair<const Foo, Foo>(f1, f2));
			Assert::AreEqual(h1.Insert(std::make_pair(f1, f3)).second, false);
		}

		TEST_METHOD(OperatorBracket)
		{
			HashMap<Foo, Foo> h1(10, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 79 };
			const Foo f2{ 0 };
			h1.operator[](f1);
			Assert::AreEqual(h1.Size(), (size_t)1);
			Assert::AreEqual(h1.begin().operator*(), std::pair<const Foo, Foo>(f1, f2));
		}


		TEST_METHOD(At)
		{
			HashMap<Foo, Foo> h1(10, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 52 };
			const Foo f2{ 73 };
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreEqual(h1.Size(), (size_t)1);
			Assert::AreEqual(h1.At(f1), f2);
			Assert::ExpectException<std::runtime_error>([&h1, &f2] {h1.At(f2); });
			const HashMap<Foo, Foo> h2 = h1;
			Assert::AreEqual(h2.Size(), (size_t)1);
			h2.At(f1);
			Assert::AreEqual(h2.At(f1), f2);
			Assert::ExpectException<std::runtime_error>([&h2, &f2] {h2.At(f2); });


		}

		TEST_METHOD(ContainsKey)
		{
			HashMap<Foo, Foo> h1(10, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			Foo f1{ 52 };
			Foo f2{ 73 };
			const Foo f3{ 11 };
			Foo* f4 = nullptr;
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreEqual(h1.Size(), (size_t)1);
			Assert::AreEqual(h1.ContainsKey(f1), true);
			Assert::AreEqual(h1.ContainsKey(f3), false);
			h1.Insert(std::make_pair(f3, f1));
			h1.ContainsKey(f3, f4);
			*f4 = f2;
			Assert::AreEqual(h1.At(f3), f2);

		}

		TEST_METHOD(Size)
		{
			HashMap<Foo, Foo> h1(11, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 52 };
			const Foo f2{ 73 };
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreEqual(h1.Size(), (size_t)1);
			h1.Insert(std::make_pair(f2, f1));
			Assert::AreEqual(h1.Size(), (size_t)2);
			h1.Remove(f1);
			Assert::AreEqual(h1.Size(), (size_t)1);
		}
		TEST_METHOD(Remove)
		{
			HashMap<Foo, Foo> h1(11, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 52 };
			const Foo f2{ 73 };
			const Foo f3{ 87 };
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreEqual(h1.Size(), (size_t)1);
			h1.Insert(std::make_pair(f2, f1));
			Assert::AreEqual(h1.Size(), (size_t)2);
			Assert::AreEqual(h1.Remove(f1), true);
			Assert::AreEqual(h1.Size(), (size_t)1);
			Assert::AreEqual(h1.Remove(f3), false);
			Assert::AreEqual(h1.Size(), (size_t)1);
		}
		TEST_METHOD(Clear)
		{
			HashMap<Foo, Foo> h1(11, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 52 };
			const Foo f2{ 73 };
			const Foo f3{ 87 };
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreEqual(h1.Size(), (size_t)1);
			h1.Insert(std::make_pair(f2, f1));
			Assert::AreEqual(h1.Size(), (size_t)2);
			h1.Clear();
			Assert::AreEqual(h1.Size(), (size_t)0);

		}
		TEST_METHOD(Find)
		{
			HashMap<Foo, Foo> h1(11, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 52 };
			const Foo f2{ 73 };
			const Foo f3{ 87 };
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreEqual(h1.Size(), (size_t)1);
			h1.Insert(std::make_pair(f2, f1));
			Assert::AreEqual(h1.Size(), (size_t)2);
			Assert::AreEqual(h1.Find(f1).second, true);
			Assert::AreEqual(h1.Find(f2).second, true);
			Assert::AreEqual(h1.Find(f3).second, false);
			const HashMap<Foo, Foo> h2 = h1;
			Assert::AreEqual(h2.Size(), (size_t)2);
			Assert::AreEqual(h2.Find(f1).second, true);
			Assert::AreEqual(h2.Find(f2).second, true);
			Assert::AreEqual(h2.Find(f3).second, false);

		}

		TEST_METHOD(BeginAndEnd)
		{
			HashMap<Foo, Foo>h1(10, FooHash{});
			Assert::AreEqual(h1.begin(), h1.end());
			const Foo f1{ 27 };
			const Foo f2{ 13 };
			h1.Insert(std::make_pair(f1, f2));
			Assert::AreEqual(h1.begin().operator*(), std::pair<const Foo, Foo>(f1, f2));
			const HashMap<Foo, Foo>h2 = h1;
			Assert::AreEqual(h2.begin().operator*(), std::pair<const Foo, Foo>(f1, f2));
			Assert::AreEqual(h2.cbegin().operator*(), std::pair<const Foo, Foo>(f1, f2));
			const HashMap<Foo, Foo>h3;
			Assert::AreEqual(h3.begin(), h3.end());
			Assert::AreEqual(h3.begin(), h3.cend());

		}

		TEST_METHOD(DeReferenceOperators)
		{
			HashMap<Foo, Foo>h1(10, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 29 };
			const Foo f2{ 17 };
			h1.Insert(std::pair<const Foo,Foo>(f1, f2));
			HashMap<Foo, Foo>::Iterator it1 = h1.Find(f1).first;
			Assert::AreEqual(it1.operator*(), std::pair<const Foo, Foo>(f1, f2));
			h1.Insert(std::pair<const Foo, Foo>(f2, f1));
			HashMap<Foo, Foo>::Iterator it2 = h1.Find(f2).first;
			Assert::AreEqual(*it2.operator->(), std::pair<const Foo, Foo>(f2, f1));
			HashMap<Foo, Foo>::ConstIterator cit2 = h1.Find(f2).first;
			Assert::AreEqual(*cit2.operator->(), std::pair<const Foo, Foo>(f2, f1));
		}

		TEST_METHOD(IteratorIncrement)
		{
			HashMap<Foo, Foo>h1(10, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 21 };
			const Foo f2{ 17 };
			h1.Insert(std::make_pair(f1, f2));
			h1.Insert(std::make_pair(f2, f1));
			HashMap<Foo, Foo>::Iterator it1 = h1.Find(f1).first;
			Assert::AreEqual(it1.operator*(), std::pair<const Foo, Foo>(f1, f2));
			++it1;
			Assert::AreEqual(it1.operator*(), std::pair<const Foo, Foo>(f2, f1));
			HashMap<Foo, Foo>::Iterator it2 = h1.begin();
			HashMap<Foo, Foo>::Iterator it3 = it2++;
			Assert::AreNotEqual(it2, it3);
			Assert::AreEqual(*it3, std::pair<const Foo, Foo>(f1, f2));
			Assert::AreEqual(*it2, std::pair<const Foo, Foo>(f2, f1));
			const HashMap<Foo, Foo>h2 = h1;
			HashMap<Foo, Foo>::ConstIterator cit1 = h2.Find(f1).first;
			Assert::AreEqual(cit1.operator*(), std::pair<const Foo, Foo>(f1, f2));
			++cit1;
			Assert::AreEqual(cit1.operator*(), std::pair<const Foo, Foo>(f2, f1));
			HashMap<Foo, Foo>::ConstIterator cit2 = h1.begin();
			HashMap<Foo, Foo>::ConstIterator cit3 = cit2++;
			Assert::AreNotEqual(cit2, cit3);
			Assert::AreEqual(*cit3, std::pair<const Foo, Foo>(f1, f2));
			Assert::AreEqual(*cit2, std::pair<const Foo, Foo>(f2, f1));
		}
		TEST_METHOD(ReHash)
		{
			HashMap<Foo, Foo> h1(2, FooHash{});
			Assert::AreEqual(h1.Size(), (size_t)0);
			const Foo f1{ 21 };
			const Foo f2{ 17 };
			const Foo f3{ 38 };
			const Foo f4{ 19 };
			const Foo f5{ 83 };
			const Foo f6{ 22 };
			h1.Insert(std::make_pair(f1, f2));
			h1.Insert(std::make_pair(f3, f4));
			h1.Insert(std::make_pair(f5, f6));
			h1.Insert(std::make_pair(f2, f5));
			h1.Insert(std::make_pair(f4, f1));
			h1.Insert(std::make_pair(f6, f5));
			h1.ReHash(10);
			Assert::AreEqual((size_t)6, h1.Size());
			h1.ReHash(7);
			Assert::AreEqual((size_t)6, h1.Size());



		}


	private:
		static _CrtMemState _startMemState;

	};
	_CrtMemState HashMapTests::_startMemState;


}




